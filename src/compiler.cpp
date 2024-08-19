#include "compiler.h"

#include <stdio.h>

#include "common.h"
#include "scanner.h"

namespace clox {

void compile(const char* source) {
  Scanner scanner{source};
  int line = 0;
  for (;;) {
    Token token = scanner.scanToken();
    if (token.line != line) {
      printf("%4d ", token.line);
      line = token.line;
    } else {
      printf("   | ");
    }

    printf("%2d '%.*s'\n", token.type, token.length, token.start);

    if (token.type == TokenType::kEOF) break;
  }
}

}  // namespace clox