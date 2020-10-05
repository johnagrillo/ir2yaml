#ifndef __MODULE_H_
#define __MODULE_H_

#include "llvm/Support/YAMLTraits.h"
#include "function.h"
#include "global.h"



namespace ir2yaml {
struct Module {
  Module(std::vector<ir2yaml::Global> globals, std::vector<ir2yaml::Function> functions):globals(globals), functions(functions){}
  Module(){}
  std::vector<ir2yaml::Global> globals;
  std::vector<ir2yaml::Function> functions;
};
}
template <> struct llvm::yaml::MappingTraits<ir2yaml::Module> {
  static void mapping(IO &IO, ir2yaml::Module & module);
};
LLVM_YAML_IS_SEQUENCE_VECTOR(ir2yaml::Module)
#endif //__MODULE_H_
