#ifndef CLOX_COMPILER_H
#define CLOX_COMPILER_H

#include "scanner.h"
#include "vm.h"

namespace clox {

enum class Precedence {
  PREC_NONE,
  PREC_ASSIGN,  // =
  PREC_OR,      // or
  PREC_AND,     // and
  PREC_EQUALS,  // == !=
  PREC_COMPARE, // < <= > >=
  PREC_TERM,    // + -
  PREC_FACTOR,  // * /
  PREC_UNARY,   // ! -
  PREC_CALL,    // . ()
  PREC_PRIMARY
};

inline Precedence successor(Precedence x) {
  return (Precedence)((int)x + 1);
}

class Parser {
 public:
  explicit Parser(Scanner& scanner);
  virtual ~Parser() = default;

  // Consume a token, emitting errors if it fails.
  void advance();
  // Consume a token if it matches the type,
  // otherwise emit an error with the message.
  void consume(TokenType token, const char* message);
  // Emit an error at the given token, with a message.
  void errorAt(const Token& token, const char* message);
  // Error at the current token.
  void errorAtCurrent(const char* message) {
    errorAt(current_, message);
  }
  // Returns true if an error was raised.
  bool erred() { return erred_; }
  const Token& previous() { return previous_; }
  const Token& current() { return current_; }
 private:
  Scanner& scanner_;
  Token current_;
  Token previous_;
  bool erred_ = false;
  bool panicMode_ = false;
};

class Compiler {
 public:
  Compiler(Parser& parser, Chunk* chunk)
      : parser_(parser), compilingChunk_(chunk) {}
  virtual ~Compiler() = default;

  Chunk* currentChunk() { return compilingChunk_; }

  void expression();
  void emitByte(uint8_t byte);
  void emitBytes(uint8_t byte1, uint8_t byte2);
  void emitReturn();
  void emitConstant(Value value);
  uint8_t makeConstant(Value value);
  // Base parser functions
  void number();
  void literal();
  void grouping();
  void unary();
  void infixL();
  // Parse an expression of precedence `prec` or higher.
  void parsePrecedence(Precedence prec);
  // Error at the previous token.
  void error(const char* message) {
    parser_.errorAt(parser_.previous(), message);
  }
 private:
  Parser& parser_;
  Chunk* compilingChunk_;
};

struct ParseRule {
  void (Compiler::*prefix)() = nullptr;
  void (Compiler::*infix)() = nullptr;
  Precedence precedence = Precedence::PREC_NONE;
};

bool compile(const char* source, Chunk* chunk);

}  // namespace clox
#endif  // CLOX_COMPILER_H