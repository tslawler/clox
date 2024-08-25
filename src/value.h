#ifndef CLOX_VALUE_H
#define CLOX_VALUE_H

#include "common.h"

namespace clox {

enum class ValueType {
  kNumber,
  kNil,
  kBool
};

struct Value {
  ValueType type;
  union {
    bool boolean;
    double number;
  } as;
};

inline bool isNumber(Value v) { return v.type == ValueType::kNumber; }
inline double asNumber(Value v) { return v.as.number; }
inline bool isBool(Value v) { return v.type == ValueType::kBool; }
inline bool asBool(Value v) { return v.as.boolean; }
inline bool isNil(Value v) { return v.type == ValueType::kNil; }

inline bool isTruthy(Value v) { 
  if (isNil(v)) return false;
  if (isBool(v) && !asBool(v)) return false;
  return true;
}

inline Value Number(double d) { return Value{.type = ValueType::kNumber, {.number = d}}; }
inline Value Bool(bool b) { return Value{.type = ValueType::kBool, {.boolean = b}}; }
inline Value Nil() { return Value{.type = ValueType::kNil}; }

void printValue(Value val);

}  // namespace clox
#endif  // CLOX_VALUE_H