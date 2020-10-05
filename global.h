#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include <string>
#include "llvm/IR/GlobalVariable.h"
#include "llvm/Support/YAMLTraits.h"


namespace ir2yaml {
struct Global {
  Global(std::string name, bool constant, std::string type, std::string init):
    name(name), constant(constant), type(type), init(init){}
  Global(llvm::GlobalVariable * g);
  Global(){}
  std::string name;
  bool constant;
  std::string type;
  std::string init;
};
}
template <> struct llvm::yaml::MappingTraits<ir2yaml::Global> {
  static void mapping(IO &IO, ir2yaml::Global & global);
};
LLVM_YAML_IS_SEQUENCE_VECTOR(ir2yaml::Global)
#endif //__GLOBAL_H_
