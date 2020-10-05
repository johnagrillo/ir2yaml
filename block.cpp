#include "block.h"
#include "tostring.h"

ir2yaml::Block::Block(llvm::BasicBlock *bb) {
  name = toStringOperand(bb, false);
  for (auto &i : bb->getInstList()) {
    ins.push_back(ir2yaml::Instruction(&i));
  }
}

void llvm::yaml::MappingTraits<ir2yaml::Block>::mapping(IO &IO,
                                                        ir2yaml::Block &block) {
  IO.mapRequired("name", block.name);
  IO.mapRequired("ins", block.ins);
}

