#ifndef __ARG_H_
#define __ARG_H_
#include "llvm/Support/YAMLTraits.h"
#include <string>
namespace ir2yaml {
struct Arg {
  Arg(std::string type, std::string value):type(type), value(value){}
  Arg(){}
  std::string type;
  std::string value;
};
}
template <> struct llvm::yaml::MappingTraits<ir2yaml::Arg> {
  static void mapping(IO &IO, ir2yaml::Arg & arg);
};
LLVM_YAML_IS_SEQUENCE_VECTOR(ir2yaml::Arg)
#endif //__ARG_H_
