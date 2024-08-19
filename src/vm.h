#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"

#define STACK_MAX 256

namespace clox {

enum class InterpretResult {
  kOk,
  kCompileError,
  kRuntimeError
};

class VM {
  public:
    VM();
    virtual ~VM();
    
    InterpretResult interpret(const char* source);
    // Stack manipulation. These are not memory safe!
    void push(Value value);
    Value pop();
  private:
    // Read byte and increment
    uint8_t readByte() { return *ip_++; }
    Value readConstant() {
      return chunk_->getConstant(readByte());
    }
    // Bulk of the interpreter.
    InterpretResult run();
    Chunk* chunk_;
    // Instruction pointer
    uint8_t* ip_;
    // Temporary value stack
    Value stack_[STACK_MAX];
    Value* stack_top_;
};

}  // namespace clox
#endif  // CLOX_VM_H