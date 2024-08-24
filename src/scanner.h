#ifndef CLOX_SCANNER_H
#define CLOX_SCANNER_H

#include "common.h"

namespace clox {

enum TokenType {
  // Single-character tokens.
  TOKEN_TYPE_LeftParen, TOKEN_TYPE_RightParen,
  TOKEN_TYPE_LeftBrace, TOKEN_TYPE_RightBrace,
  TOKEN_TYPE_Comma, TOKEN_TYPE_Dot, TOKEN_TYPE_Minus, TOKEN_TYPE_Plus,
  TOKEN_TYPE_Semicolon, TOKEN_TYPE_Slash, TOKEN_TYPE_Star,
  // One or two character tokens.
  TOKEN_TYPE_Bang, TOKEN_TYPE_BangEqual,
  TOKEN_TYPE_Equal, TOKEN_TYPE_EqualEqual,
  TOKEN_TYPE_Greater, TOKEN_TYPE_GreaterEqual,
  TOKEN_TYPE_Less, TOKEN_TYPE_LessEqual,
  // Literals.
  TOKEN_TYPE_Identifier, TOKEN_TYPE_String, TOKEN_TYPE_Number,
  // Keywords.
  TOKEN_TYPE_And, TOKEN_TYPE_Class, TOKEN_TYPE_Else, TOKEN_TYPE_False,
  TOKEN_TYPE_For, TOKEN_TYPE_Fun, TOKEN_TYPE_If, TOKEN_TYPE_Nil, TOKEN_TYPE_Or,
  TOKEN_TYPE_Print, TOKEN_TYPE_Return, TOKEN_TYPE_Super, TOKEN_TYPE_This,
  TOKEN_TYPE_True, TOKEN_TYPE_Var, TOKEN_TYPE_While,

  TOKEN_TYPE_Error, TOKEN_TYPE_EOF,
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