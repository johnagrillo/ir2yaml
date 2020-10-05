#include "instruction.h"
#include "tostring.h"
#include "utils.h"

ir2yaml::Instruction::Instruction(llvm::Instruction * ins)
{
  align = getAlignment(ins);

  /*
    if (llvm::CallInst *ci = llvm::dyn_cast<llvm::CallInst>(&ins)) {
    if (ci->hasOperandBundles()) {
    for (unsigned i = ci->getBundleOperandsStartIndex();
    i < ci->getBundleOperandsEndIndex(); i++) {
    auto &b = ci->getBundleOpInfoForOperand(i);
    auto tag = b.Tag;
    }
    }
    }
    */
  
  opcode = ins->getOpcodeName();
  if ((opcode != "store") && (opcode != "ret") && (opcode != "br")) {
    reg = toStringOperand(ins);
  }
  
  for (auto arg_iter = ins->op_begin(); arg_iter != ins->op_end(); arg_iter++) {
    args.push_back(ir2yaml::Arg(toString(arg_iter->get()->getType()),
    				toStringOperand(arg_iter->get())));
  }
  ir = toString(ins);
}

void llvm::yaml::MappingTraits<ir2yaml::Instruction>::mapping(IO &IO, ir2yaml::Instruction & instruction)
{
  IO.mapRequired("ir", instruction.ir);
  IO.mapRequired("opcode", instruction.opcode);
  IO.mapRequired("reg", instruction.reg);
  IO.mapRequired("args", instruction.args);
  IO.mapRequired("align", instruction.align);
}
