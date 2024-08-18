#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "value.h"

int main(int argc, const char* argv[]) {
  Chunk chunk{};
  size_t index = chunk.addConstant(2.3);
  chunk.write(OpCode::kConstant, 123);
  chunk.write(index, 123);
  chunk.write(OpCode::kReturn, 123);
  disassembleChunk(chunk, "test chunk");
  return 0;
}