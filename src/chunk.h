#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include <vector>

#include "common.h"
#include "value.h"

namespace clox {

enum OpCode : uint8_t {
    kReturn,
    kConstant,
    kNegate, kAdd, kSub, kMul, kDiv,
    kTrue, kFalse, kNil,
    kNot,
};

class Chunk {
  public:
    Chunk() = default;
    virtual ~Chunk() = default;

    void write(uint8_t byte, int32_t line);
    size_t addConstant(Value value);
    const Value getConstant(size_t index) const {
      return constants_[index];
    }
    const uint8_t byteAt(size_t offset) const {
      return code_[offset];
    }
    const int32_t lineAt(size_t offset) const {
      return lines_[offset];
    }
    const size_t size() const {
      return code_.size();
    }
    uint8_t* at(size_t offset) {
      return &code_[offset];
    }
  private:
    // constants_ contains the constant pool for this chunk.
    std::vector<Value> constants_;
    // code_ contains the bytecode for this chunk.
    std::vector<uint8_t> code_;
    // lines_ is a parallel array to code_,
    // for each element of code_ we have an element of lines_
    // to tell us which line of user code the corresponding byte
    // refers to.
    std::vector<int32_t> lines_;
};

}  // namespace clox
#endif  // CLOX_CHUNK_H