#include "vm.h"

#include <stdio.h>
#include <cstdarg>

#include "chunk.h"
#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "value.h"

namespace clox {

VM::VM() {
  resetStack();
}

VM::~VM() {

}

void VM::push(Value value) {
  stack_[stack_size_] = value;
  stack_size_++;
}

Value VM::pop() {
  --stack_size_;
  return stack_[stack_size_];
}

const Value& VM::peek(ptrdiff_t offset) {
  return stack_[stack_size_ - offset - 1];
}

InterpretResult VM::runtimeError(const char* format, ...) {
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  fputs("\n", stderr);

  int line = chunk_->lineAt(instr_);
  fprintf(stderr, "[line %d] in script\n", line);
  resetStack();
  return InterpretResult::kRuntimeError;
}

InterpretResult VM::run() {
  #define BINOP(valueType, op) \
      do { \
        if (!isNumber(peek(0)) || !isNumber(peek(1))) { \
          return runtimeError("Operands must be numbers."); \
        } \
        double a = asNumber(pop()); double b = asNumber(pop()); \
        push(valueType(b op a)); \
      } while (false)

  uint8_t instruction;
  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    if (stack_size_ > 0) {
      printf("          ");
      for (size_t i = 0; i < stack_size_; ++i) {
        printf("[ ");
        printValue(peek(i));
        printf(" ]");
      }
      printf("\n");
    }
    disassembleInstruction(*chunk_, instr_);
#endif // DEBUG_TRACE_EXECUTION
    switch (instruction = readByte()) {
      case OpCode::kConstant: { push(readConstant()); break; }
      case OpCode::kTrue: { push(Bool(true)); break; }
      case OpCode::kFalse: { push(Bool(false)); break; }
      case OpCode::kNil: { push(Nil()); break; }
      case OpCode::kNot: { Value a = pop(); push(Bool(!isTruthy(a))); break; }
      case OpCode::kNegate: { 
        if (!isNumber(peek(0))) {
          return runtimeError("Operand must be a number.");
        } 
        push(Number(-asNumber(pop())));
        break;
      }
      case OpCode::kAdd: { BINOP(Number, +); break; }
      case OpCode::kSub: { BINOP(Number, -); break; }
      case OpCode::kMul: { BINOP(Number, *); break; }
      case OpCode::kDiv: { BINOP(Number, /); break; }
      case OpCode::kReturn:
        printValue(pop());
        printf("\n");
        return InterpretResult::kOk;
    }
  }
  #undef BINOP
}

InterpretResult VM::interpret(const char* source) {
  Chunk chunk{};
  if (!compile(source, &chunk)) {
    return InterpretResult::kCompileError;
  }
#ifdef DEBUG_TRACE_PARSING
  disassembleChunk(chunk, "script");
  printf("== end script ==\n");
#endif // DEBUG_TRACE_PARSING
  chunk_ = &chunk;
  instr_ = 0;
  return run();
}

}  // namespace clox