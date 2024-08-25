#ifndef CLOX_OPCODE_H
#define CLOX_OPCODE_H

#include "common.h"

namespace clox {

enum OpCode : uint8_t {
    kReturn,
    kConstant,
    kNegate, kAdd, kSub, kMul, kDiv,
    kTrue, kFalse, kNil,
    kNot,
    kEqual, kGreater, kLess,
};

}  // namespace
#endif  // CLOX_OPCODE_H