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

}  // namespace clox