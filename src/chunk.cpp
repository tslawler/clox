#include "chunk.h"

#include <vector>

#include "value.h"

namespace clox {

void Chunk::write(uint8_t byte, int32_t line) {
  code_.push_back(byte);
  lines_.push_back(line);
}

size_t Chunk::addConstant(Value value) {
  size_t loc = constants_.size();
  constants_.push_back(value);
  return loc;
}

}  // namespace clox