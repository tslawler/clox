#include "compiler.h"

#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"
#include "common.h"
#include "opcode.h"
#include "scanner.h"
#include "value.h"

namespace clox {

static const ParseRule& getRule(TokenType type) {
  static ParseRule rules[] {
    [TOKEN_TYPE_LeftParen] = { .prefix = &Compiler::grouping },
    [TOKEN_TYPE_RightParen] = {},
    [TOKEN_TYPE_LeftBrace] = {},
    [TOKEN_TYPE_RightBrace] = {},
    [TOKEN_TYPE_Comma] = {},
    [TOKEN_TYPE_Dot] = {},
    [TOKEN_TYPE_Minus] = {
        .prefix = &Compiler::unary,
        .infix = &Compiler::infixL,
        .precedence = Precedence::PREC_TERM },
    [TOKEN_TYPE_Plus] = { 
        .infix = &Compiler::infixL, 
        .precedence = Precedence::PREC_TERM },
    [TOKEN_TYPE_Semicolon] = {},
    [TOKEN_TYPE_Slash] = {
        .infix = &Compiler::infixL,
        .precedence = Precedence::PREC_FACTOR },
    [TOKEN_TYPE_Star] = {
        .infix = &Compiler::infixL,
        .precedence = Precedence::PREC_FACTOR },
    [TOKEN_TYPE_Bang] = { .prefix = &Compiler::unary },
    [TOKEN_TYPE_BangEqual] = { .infix = &Compiler::infixL, .precedence = Precedence::PREC_EQUALS },
    [TOKEN_TYPE_Equal] = {},
    [TOKEN_TYPE_EqualEqual] = { .infix = &Compiler::infixL, .precedence = Precedence::PREC_EQUALS },
    [TOKEN_TYPE_Greater] = { .infix = &Compiler::infixL, .precedence = Precedence::PREC_COMPARE },
    [TOKEN_TYPE_GreaterEqual] = { .infix = &Compiler::infixL, .precedence = Precedence::PREC_COMPARE },
    [TOKEN_TYPE_Less] = { .infix = &Compiler::infixL, .precedence = Precedence::PREC_COMPARE },
    [TOKEN_TYPE_LessEqual] = { .infix = &Compiler::infixL, .precedence = Precedence::PREC_COMPARE },
    [TOKEN_TYPE_Identifier] = {},
    [TOKEN_TYPE_String] = {},
    [TOKEN_TYPE_Number] = { .prefix = &Compiler::number },
    [TOKEN_TYPE_And] = {},
    [TOKEN_TYPE_Class] = {},
    [TOKEN_TYPE_Else] = {},
    [TOKEN_TYPE_False] = { .prefix = &Compiler::literal },
    [TOKEN_TYPE_For] = {},
    [TOKEN_TYPE_Fun] = {},
    [TOKEN_TYPE_If] = {},
    [TOKEN_TYPE_Nil] = { .prefix = &Compiler::literal },
    [TOKEN_TYPE_Or] = {},
    [TOKEN_TYPE_Print] = {},
    [TOKEN_TYPE_Return] = {},
    [TOKEN_TYPE_Super] = {},
    [TOKEN_TYPE_This] = {},
    [TOKEN_TYPE_True] = { .prefix = &Compiler::literal },
    [TOKEN_TYPE_Var] = {},
    [TOKEN_TYPE_While] = {},
    [TOKEN_TYPE_Error] = {},
    [TOKEN_TYPE_EOF] = {}
  };
  return rules[type];
}

Parser::Parser(Scanner& scanner) : scanner_(scanner) {
  current_ = scanner_.scanToken();
  previous_ = current_; // just for safety.
  if (current_.type == TOKEN_TYPE_Error) {
    errorAtCurrent(current_.start);
  }
}

void Parser::advance() {
  previous_ = current_;
  for (;;) {
    current_ = scanner_.scanToken();
    if (current_.type != TOKEN_TYPE_Error) break;
    errorAtCurrent(current_.start);
  }
}

void Parser::errorAt(const Token& token, const char* message) {
  if (panicMode_) return;
  erred_ = true;
  panicMode_ = true;
  fprintf(stderr, "[line %d] Error", token.line);
  if (token.type == TOKEN_TYPE_EOF) {
    fprintf(stderr, " at end");
  } else if (token.type != TOKEN_TYPE_Error) {
    fprintf(stderr, " at '%.*s'", (int)token.length, token.start);
  }
  fprintf(stderr, ": %s\n", message);
}

void Parser::consume(TokenType type, const char* message) {
  if (current_.type == type) {
    advance();
    return;
  }
  errorAtCurrent(message);
}

void Compiler::emitByte(uint8_t byte) {
#ifdef DEBUG_TRACE_PARSING
  printf("Emitting %d at line %d\n", byte, parser_.previous().line);
#endif // DEBUG_TRACE_PARSING
  currentChunk()->write(byte, parser_.previous().line);
}

void Compiler::emitReturn() {
  emitByte(OpCode::kReturn);
}

void Compiler::emitBytes(uint8_t byte1, uint8_t byte2) {
  emitByte(byte1);
  emitByte(byte2);
}

uint8_t Compiler::makeConstant(Value value) {
  size_t index = currentChunk()->addConstant(value);
  if (index > UINT8_MAX) {
    error("Too many constants in one chunk.");
    return 0;
  }
  return (uint8_t)index;
}

void Compiler::emitConstant(Value value) {
  emitBytes(OpCode::kConstant, makeConstant(value));
}

void Compiler::number() {
  double value = strtod(parser_.previous().start, nullptr);
  emitConstant(Number(value));
}

void Compiler::literal() {
  switch (parser_.previous().type) {
    case TOKEN_TYPE_True: emitByte(OpCode::kTrue); return;
    case TOKEN_TYPE_False: emitByte(OpCode::kFalse); return;
    case TOKEN_TYPE_Nil: emitByte(OpCode::kNil); return;
    default: return; // Unreachable
  }
}

void Compiler::grouping() {
  expression();
  parser_.consume(TOKEN_TYPE_RightParen, "Expected ')' after expression.");
}

void Compiler::unary() {
  TokenType operatorType = parser_.previous().type;

  parsePrecedence(Precedence::PREC_UNARY);

  switch (operatorType) {
    case TOKEN_TYPE_Minus: emitByte(OpCode::kNegate); return;
    case TOKEN_TYPE_Bang: emitByte(OpCode::kNot); return;
    default: return; // Unreachable
  }
}

void Compiler::infixL() {
  TokenType operatorType = parser_.previous().type;
  const Precedence prec = getRule(operatorType).precedence;
  parsePrecedence(successor(prec));

  switch (operatorType) {
    case TOKEN_TYPE_Plus: emitByte(OpCode::kAdd); return;
    case TOKEN_TYPE_Minus: emitByte(OpCode::kSub); return;
    case TOKEN_TYPE_Star: emitByte(OpCode::kMul); return;
    case TOKEN_TYPE_Slash: emitByte(OpCode::kDiv); return;
    case TOKEN_TYPE_EqualEqual: emitByte(OpCode::kEqual); return;
    case TOKEN_TYPE_BangEqual: emitBytes(OpCode::kEqual, OpCode::kNot); return;
    case TOKEN_TYPE_Less: emitByte(OpCode::kLess); return;
    case TOKEN_TYPE_GreaterEqual: emitBytes(OpCode::kLess, OpCode::kNot); return;
    case TOKEN_TYPE_Greater: emitByte(OpCode::kGreater); return;
    case TOKEN_TYPE_LessEqual: emitBytes(OpCode::kGreater, OpCode::kNot); return;
    default: return; // Unreachable
  }
}

void Compiler::expression() {
  parsePrecedence(Precedence::PREC_ASSIGN);
}

void Compiler::parsePrecedence(Precedence prec) {
  parser_.advance();
  const auto& rule = getRule(parser_.previous().type);
  if (rule.prefix == nullptr) {
    error("Expected expression.");
    return;
  }
  (this->*(rule.prefix))();

  while (prec <= getRule(parser_.current().type).precedence) {
    parser_.advance();
    const auto& rule = getRule(parser_.previous().type);
    if (rule.infix != nullptr) {
      (this->*(rule.infix))();
    }
  }
}

bool compile(const char* source, Chunk* chunk) {
  Scanner scanner{source};
  Parser parser{scanner};
  Compiler compiler{parser, chunk};
  compiler.expression();
  parser.consume(TOKEN_TYPE_EOF, "Expected end of expression.");
  compiler.emitReturn();
  return !parser.erred();
}

}  // namespace clox