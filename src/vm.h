#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"
#include "opcode.h"

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
    
    InterpretResult interpret(const char* filename, const char* source);
    // Stack manipulation. These are not memory safe!
    void push(Value value);
    Value pop();
    const Value& peek(ptrdiff_t offset);
  private:
    // Read byte and increment
    uint8_t readByte() { return chunk_->byteAt(instr_++); }
    void resetStack() { stack_size_ = 0; }
    Value readConstant() {
      return chunk_->getConstant(readByte());
    }
    // Bulk of the interpreter.
    InterpretResult run();
    // Prints a runtime error.
    InterpretResult runtimeError(const char* format, ...);
    Chunk* chunk_;
    // Instruction pointer
    size_t instr_;
    // Temporary value stack
    Value stack_[STACK_MAX];
    size_t stack_size_;
};

}  // namespace clox
#endif  // CLOX_VM_H