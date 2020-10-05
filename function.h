#ifndef __FUNCTION_H_
#define __FUNCTION_H_
#include "llvm/Support/YAMLTraits.h"
#include "llvm/IR/Function.h"
#include <string>
#include "arg.h"
#include "block.h"


namespace ir2yaml {
struct Function {
  Function(std::string name,
	   std::vector<ir2yaml::Arg> args,
	   std::string retType,
	   std::vector<ir2yaml::Block> blocks,
	   std::vector<std::string> attrs):name(name),
					   args(args),
					   retType(retType),
					   blocks(blocks),
					   attrs(attrs){}
  Function(llvm::Function *);
  Function(){}
  std::string name;
  
  std::vector<ir2yaml::Arg> args;
  std::string retType;
  std::string linkage;
  std::string visibility;
  std::string cconv;
  std::string dllstorage;
  std::vector<ir2yaml::Block> blocks;
  std::vector<std::string> attrs;
  
};
}
template <> struct llvm::yaml::MappingTraits<ir2yaml::Function> {
  static void mapping(IO &IO, ir2yaml::Function & function);
};
LLVM_YAML_IS_SEQUENCE_VECTOR(ir2yaml::Function)
#endif //__FUNCTION_H_
