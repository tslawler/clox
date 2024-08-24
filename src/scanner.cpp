#include "scanner.h"

#include <cstring>

#include "common.h"

namespace clox {

namespace {
bool isDigit(char c) {
  return '0' <= c && c <= '9';
}

bool isValidIdentStart(char c) {
  return
      ('a' <= c && c <= 'z') ||
      ('A' <= c && c <= 'Z') ||
      c == '_';
}

bool isValidIdent(char c) {
  return isValidIdentStart(c) || isDigit(c);
}
}  // namespace

Scanner::Scanner(const char* source) {
  start_ = source;
  current_ = source;
  line_ = 1;
}

Scanner::~Scanner() {}

Token Scanner::makeToken(TokenType type) {
  return Token {
    .type = type,
    .start = start_,
    .length = static_cast<size_t>(current_ - start_),
    .line = line_
  };
}

Token Scanner::makeError(const char* error) {
  return Token {
    .type = TOKEN_TYPE_Error,
    .start = error,
    .length = std::strlen(error),
    .line = line_
  };
}

Token Scanner::scanToken() {
  skipWhitespace();
  start_ = current_;
  if (isAtEnd()) return makeToken(TOKEN_TYPE_EOF);
  char c = advance();

  if (isDigit(c)) return number();
  if (isValidIdentStart(c)) return identifier();
  switch (c) {
    case '(': return makeToken(TOKEN_TYPE_LeftParen);
    case ')': return makeToken(TOKEN_TYPE_RightParen);
    case '{': return makeToken(TOKEN_TYPE_LeftBrace);
    case '}': return makeToken(TOKEN_TYPE_RightBrace);
    case ',': return makeToken(TOKEN_TYPE_Comma);
    case '.': return makeToken(TOKEN_TYPE_Dot);
    case '-': return makeToken(TOKEN_TYPE_Minus);
    case '+': return makeToken(TOKEN_TYPE_Plus);
    case ';': return makeToken(TOKEN_TYPE_Semicolon);
    case '/': return makeToken(TOKEN_TYPE_Slash);
    case '*': return makeToken(TOKEN_TYPE_Star);

    case '!':
      return makeToken(
          match('=') ? TOKEN_TYPE_BangEqual: TOKEN_TYPE_Bang);
    case '=':
      return makeToken(
          match('=') ? TOKEN_TYPE_EqualEqual: TOKEN_TYPE_Equal);
    case '<':
      return makeToken(
          match('=') ? TOKEN_TYPE_LessEqual: TOKEN_TYPE_Less);
    case '>':
      return makeToken(
          match('=') ? TOKEN_TYPE_GreaterEqual: TOKEN_TYPE_Greater);
    
    case '"': return string();
  }
  return makeError("Unexpected character.");
}

void Scanner::skipWhitespace() {
  for (;;) {
    char c = peek();
    switch (c) {
      case '\n':
        ++line_;
        // intentional fallthrough
      case ' ':
      case '\r':
      case '\t':
        advance();
        break;
      case '/':
        if (peekNext() == '/') {
          while (peek() != '\n' && !isAtEnd()) advance();
        } else return;
        break;
      default:
        return;
    }
  }
}

bool Scanner::match(char expected) {
  if (isAtEnd()) return false;
  if (*current_ != expected) return false;
  ++current_;
  return true;
}

Token Scanner::string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') { ++line_; }
    advance();
  }
  if (isAtEnd()) {
    return makeError("Unterminated string.");
  }
  // Closing quote
  advance();
  return makeToken(TOKEN_TYPE_String);
}

Token Scanner::number() {
  while (isDigit(peek())) advance();

  if (peek() == '.' && isDigit(peekNext())) {
    advance();
    while (isDigit(peek())) advance();
  }

  return makeToken(TOKEN_TYPE_Number);
}

Token Scanner::identifier() {
  while (isValidIdent(peek())) advance();
  return makeToken(identifierType());
}

TokenType Scanner::identifierType() {
  switch (*start_) {
    case 'a': return checkKeyword(1, 2, "nd", TOKEN_TYPE_And);
    case 'c': return checkKeyword(1, 4, "lass", TOKEN_TYPE_Class);
    case 'e': return checkKeyword(1, 3, "lse", TOKEN_TYPE_Else);
    case 'i': return checkKeyword(1, 1, "f", TOKEN_TYPE_If);
    case 'n': return checkKeyword(1, 2, "il", TOKEN_TYPE_Nil);
    case 'o': return checkKeyword(1, 1, "r", TOKEN_TYPE_Or);
    case 'p': return checkKeyword(1, 4, "rint", TOKEN_TYPE_Print);
    case 'r': return checkKeyword(1, 5, "eturn", TOKEN_TYPE_Return);
    case 's': return checkKeyword(1, 4, "uper", TOKEN_TYPE_Super);
    case 'v': return checkKeyword(1, 2, "ar", TOKEN_TYPE_Var);
    case 'w': return checkKeyword(1, 4, "hile", TOKEN_TYPE_While);
    // 2-letter lookahead
    case 'f': switch (start_[1]) {
      case 'a': return checkKeyword(2, 3, "lse", TOKEN_TYPE_False);
      case 'o': return checkKeyword(2, 1, "r", TOKEN_TYPE_For);
      case 'u': return checkKeyword(2, 1, "n", TOKEN_TYPE_Fun);
      default: return TOKEN_TYPE_Identifier;
    }
    case 't': switch (start_[1]) {
      case 'h': return checkKeyword(2, 2, "is", TOKEN_TYPE_This);
      case 'r': return checkKeyword(2, 2, "ue", TOKEN_TYPE_True);
      default: return TOKEN_TYPE_Identifier;
    }
    default: return TOKEN_TYPE_Identifier;
  }
}

TokenType Scanner::checkKeyword(int start, int len, const char* str, TokenType type) {
  if (current_ - start_ == start + len &&
      memcmp(str, start_ + start, len) == 0) {
    return type;
  }
  return TOKEN_TYPE_Identifier;
}

}  // namespace clox
