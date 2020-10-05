#ifndef __BLOCK_H_
#define __BLOCK_H_
#include "llvm/Support/YAMLTraits.h"
#include "llvm/IR/BasicBlock.h"
#include <string>
#include "instruction.h"
namespace ir2yaml {
struct Block {
  Block(std::string name, std::vector<ir2yaml::Instruction> ins):name(name), ins(ins){}
  Block(llvm::BasicBlock *bb); 
  Block(){}
  std::string name;
  std::vector<ir2yaml::Instruction> ins;
};
}
template <> struct llvm::yaml::MappingTraits<ir2yaml::Block> {
  static void mapping(IO &IO, ir2yaml::Block & block);
};
LLVM_YAML_IS_SEQUENCE_VECTOR(ir2yaml::Block)
#endif //__BLOCK_H_
