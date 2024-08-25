#include "debug.h"

#include <string>
#include <vector>

#include "chunk.h"
#include "common.h"
#include "opcode.h"
#include "value.h"

namespace clox {

static size_t simpleInstruction(const char* name, size_t offset) {
  printf("%s\n", name);
  return offset + 1;
}

static size_t constantInstruction(const char* name, const Chunk& chunk, size_t offset) {
  size_t constant = chunk.byteAt(offset + 1);
  printf("%-16s %4ld := ", name, constant);
  printValue(chunk.getConstant(constant));
  printf("\n");
  return offset + 2;
}

void disassembleChunk(const Chunk& chunk, const char* name) {
  printf("== %s ==\n", name);

  for (size_t offset = 0; offset < chunk.size();) {
    offset = disassembleInstruction(chunk, offset);
  }
}

size_t disassembleInstruction(const Chunk& chunk, size_t offset) {
  printf("%04ld ", offset);
  if (offset > 0 && chunk.lineAt(offset) == chunk.lineAt(offset - 1)) {
    printf("   | ");
  } else {
    printf("%4d ", chunk.lineAt(offset));
  }
  uint8_t instruction = chunk.byteAt(offset);
  switch (instruction) {
    case OpCode::kReturn:
      return simpleInstruction("OP_RETURN", offset);
    case OpCode::kNegate:
      return simpleInstruction("OP_NEGATE", offset);
    case OpCode::kAdd:
      return simpleInstruction("OP_ADD", offset);
    case OpCode::kSub:
      return simpleInstruction("OP_SUB", offset);
    case OpCode::kMul:
      return simpleInstruction("OP_MUL", offset);
    case OpCode::kDiv:
      return simpleInstruction("OP_DIV", offset);
    case OpCode::kConstant:
      return constantInstruction("OP_CONSTANT", chunk, offset);
    case OpCode::kTrue:
      return simpleInstruction("OP_TRUE", offset);
    case OpCode::kFalse:
      return simpleInstruction("OP_FALSE", offset);
    case OpCode::kNil:
      return simpleInstruction("OP_NIL", offset);
    case OpCode::kNot:
      return simpleInstruction("OP_NOT", offset);
    case OpCode::kEqual:
      return simpleInstruction("OP_EQUAL", offset);
    case OpCode::kLess:
      return simpleInstruction("OP_LESS", offset);
    case OpCode::kGreater:
      return simpleInstruction("OP_GREATER", offset);
    default:
      printf("Unknown opcode %d\n", instruction);
      return offset + 1;
  }
}

}  // namespace clox