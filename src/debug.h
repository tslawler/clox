#ifndef CLOX_DEBUG_H
#define CLOX_DEBUG_H

#include "chunk.h"
#include "common.h"

namespace clox {

void disassembleChunk(const Chunk& chunk, const char* name);
size_t disassembleInstruction(const Chunk& chunk, size_t offset);

}  // namespace clox
#endif  // CLOX_DEBUG_H