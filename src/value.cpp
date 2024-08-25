#include "value.h"

#include <string>

namespace clox {

void printValue(Value val) {
  switch (val.type) {
    case ValueType::kNumber: printf("%g", asNumber(val)); return;
    case ValueType::kBool: printf("%s", asBool(val) ? "true" : "false"); return;
    case ValueType::kNil: printf("nil"); return;
  }
}

bool valuesEqual(Value a, Value b) {
  if (a.type != b.type) return false;
  switch(a.type) {
    case ValueType::kNil: return true;
    case ValueType::kBool: return asBool(a) == asBool(b);
    case ValueType::kNumber: return asNumber(a) == asNumber(b);
  }
}

}  // namespace clox