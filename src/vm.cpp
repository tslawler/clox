#include "vm.h"

#include <stdio.h>

#include "chunk.h"
#include "compiler.h"
#include "value.h"

#ifdef DEBUG_TRACE_EXECUTION
#include "debug.h"
#endif // DEBUG_TRACE_EXECUTION

namespace clox {

VM::VM() {
  stack_top_ = stack_;
}

VM::~VM() {

}

void VM::push(Value value) {
  *stack_top_++ = value;
}

Value VM::pop() {
  return *--stack_top_;
}

InterpretResult VM::run() {
  uint8_t instruction;
  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("          ");
    for (Value* slot = stack_; slot < stack_top_; slot++) {
      printf("[ ");
      printValue(*slot);
      printf(" ]");
    }
    printf("\n");
    disassembleInstruction(*chunk_, (ip_ - chunk_->at(0)));
#endif // DEBUG_TRACE_EXECUTION
    switch (instruction = readByte()) {
      case OpCode::kConstant: { push(readConstant()); break; }
      case OpCode::kNegate: { push(-pop()); break; }
      case OpCode::kAdd: { Value a = pop(); Value b = pop(); push(b + a); break; }
      case OpCode::kSub: { Value a = pop(); Value b = pop(); push(b - a); break; }
      case OpCode::kMul: { Value a = pop(); Value b = pop(); push(b * a); break; }
      case OpCode::kDiv: { Value a = pop(); Value b = pop(); push(b / a); break; }
      case OpCode::kReturn:
        printValue(pop());
        printf("\n");
        return InterpretResult::kOk;
    }
  }
}

InterpretResult VM::interpret(const char* source) {
  compile(source);
  // return run();
  return InterpretResult::kOk;
}

}  // namespace clox