#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "value.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
  VM vm{};
  Chunk chunk{};
  // (- (/ (+ 1.2 3.4) 5.6))
  chunk.write(OpCode::kConstant, 123);
  chunk.write(chunk.addConstant(1.2), 123);

  chunk.write(OpCode::kConstant, 123);
  chunk.write(chunk.addConstant(3.4), 123);

  chunk.write(OpCode::kAdd, 123);

  chunk.write(OpCode::kConstant, 123);
  chunk.write(chunk.addConstant(5.6), 123);

  chunk.write(OpCode::kDiv, 123);
  chunk.write(OpCode::kNegate, 123);
  chunk.write(OpCode::kReturn, 123);
  vm.interpret(&chunk);
  return 0;
}