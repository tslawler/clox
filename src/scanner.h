#ifndef CLOX_SCANNER_H
#define CLOX_SCANNER_H

#include "common.h"

namespace clox {

enum class TokenType {
  // Single-character tokens.
  kLeftParen, kRightParen,
  kLeftBrace, kRightBrace,
  kComma, kDot, kMinus, kPlus,
  kSemicolon, kSlash, kStar,
  // One or two character tokens.
  kBang, kBangEqual,
  kEqual, kEqualEqual,
  kGreater, kGreaterEqual,
  kLess, kLessEqual,
  // Literals.
  kIdentifier, kString, kNumber,
  // Keywords.
  kAnd, kClass, kElse, kFalse,
  kFor, kFun, kIf, kNil, kOr,
  kPrint, kReturn, kSuper, kThis,
  kTrue, kVar, kWhile,

  kError, kEOF
};

struct Token {
  TokenType type;
  const char* start;
  size_t length;
  int line;
};

class Scanner {
  public:
    Scanner(const char* source);
    virtual ~Scanner();
    Token scanToken();
  private:
    bool isAtEnd() { return *current_ == '\0'; }
    char advance() { return *current_++; }
    char peek() { return *current_; }
    char peekNext() { 
      if (isAtEnd()) return '\0';
      return current_[1];
    }

    Token makeToken(TokenType type);
    Token makeError(const char* error);
    bool match(char expected);
    void skipWhitespace();

    // Helper methods for scanning larger lexemes.
    Token number();
    Token string();
    Token identifier();
    TokenType identifierType();
    TokenType checkKeyword(int start, int len, const char* str, TokenType type);
  
    const char* start_;
    const char* current_;
    int line_;
};

}  // namespace clox
#endif  // CLOX_SCANNER_H