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
    .length = current_ - start_,
    .line = line_
  };
}

Token Scanner::makeError(const char* error) {
  return Token {
    .type = TokenType::kError,
    .start = error,
    .length = std::strlen(error),
    .line = line_
  };
}

Token Scanner::scanToken() {
  skipWhitespace();
  start_ = current_;
  if (isAtEnd()) return makeToken(TokenType::kEOF);
  char c = advance();

  if (isDigit(c)) return number();
  if (isValidIdentStart(c)) return identifier();
  switch (c) {
    case '(': return makeToken(TokenType::kLeftParen);
    case ')': return makeToken(TokenType::kRightParen);
    case '{': return makeToken(TokenType::kLeftBrace);
    case '}': return makeToken(TokenType::kRightBrace);
    case ',': return makeToken(TokenType::kComma);
    case '.': return makeToken(TokenType::kDot);
    case '-': return makeToken(TokenType::kMinus);
    case '+': return makeToken(TokenType::kPlus);
    case ';': return makeToken(TokenType::kSemicolon);
    case '/': return makeToken(TokenType::kSlash);
    case '*': return makeToken(TokenType::kStar);

    case '!':
      return makeToken(
          match('=') ? TokenType::kBangEqual: TokenType::kBang);
    case '=':
      return makeToken(
          match('=') ? TokenType::kEqualEqual: TokenType::kEqual);
    case '<':
      return makeToken(
          match('=') ? TokenType::kLessEqual: TokenType::kLess);
    case '>':
      return makeToken(
          match('=') ? TokenType::kGreaterEqual: TokenType::kGreater);
    
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
  return makeToken(TokenType::kString);
}

Token Scanner::number() {
  while (isDigit(peek())) advance();

  if (peek() == '.' && isDigit(peekNext())) {
    advance();
    while (isDigit(peek())) advance();
  }

  return makeToken(TokenType::kNumber);
}

Token Scanner::identifier() {
  while (isValidIdent(peek())) advance();
  return makeToken(identifierType());
}

TokenType Scanner::identifierType() {
  switch (*start_) {
    case 'a': return checkKeyword(1, 2, "nd", TokenType::kAnd);
    case 'c': return checkKeyword(1, 4, "lass", TokenType::kClass);
    case 'e': return checkKeyword(1, 3, "lse", TokenType::kElse);
    case 'i': return checkKeyword(1, 1, "f", TokenType::kIf);
    case 'n': return checkKeyword(1, 2, "il", TokenType::kNil);
    case 'o': return checkKeyword(1, 1, "r", TokenType::kOr);
    case 'p': return checkKeyword(1, 4, "rint", TokenType::kPrint);
    case 'r': return checkKeyword(1, 5, "eturn", TokenType::kReturn);
    case 's': return checkKeyword(1, 4, "uper", TokenType::kSuper);
    case 'v': return checkKeyword(1, 2, "ar", TokenType::kVar);
    case 'w': return checkKeyword(1, 4, "hile", TokenType::kWhile);
    // 2-letter lookahead
    case 'f': switch (start_[1]) {
      case 'a': return checkKeyword(2, 3, "lse", TokenType::kFalse);
      case 'o': return checkKeyword(2, 1, "r", TokenType::kFor);
      case 'u': return checkKeyword(2, 1, "n", TokenType::kFun);
      default: return TokenType::kIdentifier;
    }
    case 't': switch (start_[1]) {
      case 'h': return checkKeyword(2, 2, "is", TokenType::kThis);
      case 'r': return checkKeyword(2, 2, "ue", TokenType::kTrue);
      default: return TokenType::kIdentifier;
    }
    default: return TokenType::kIdentifier;
  }
}

TokenType Scanner::checkKeyword(int start, int len, const char* str, TokenType type) {
  if (current_ - start_ == start + len &&
      memcmp(str, start_ + start, len) == 0) {
    return type;
  }
  return TokenType::kIdentifier;
}

}  // namespace clox
