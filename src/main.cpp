#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "value.h"
#include "vm.h"

namespace clox {

void repl(VM vm) {
  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    vm.interpret(line);
  }
}

char* readFile(const char* path) {
  FILE* file = fopen(path, "rb");

  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(fileSize + 1);
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
}

void runFile(VM vm, const char* path) {
  char* source = readFile(path);
  InterpretResult result = vm.interpret(source);
  free(source); 

  if (result == InterpretResult::kCompileError) exit(65);
  if (result == InterpretResult::kRuntimeError) exit(70);
}

}  // namespace clox

int main(int argc, const char* argv[]) {
  clox::VM vm{};

  if (argc == 1) {
    clox::repl(std::move(vm));
  } else if (argc == 2) {
    clox::runFile(std::move(vm), argv[1]);
  } else {
    fprintf(stderr, "Usage: clox [path]\n");
    exit(64);
  }

  return 0;
}