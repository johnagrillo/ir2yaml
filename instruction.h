#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_
#include "llvm/Support/YAMLTraits.h"
#include "llvm/IR/Instruction.h"
#include <string>
#include "arg.h"


namespace ir2yaml {
struct Instruction {
  Instruction(std::string ir, std::string opcode, std::string reg, std::vector<ir2yaml::Arg> args, unsigned align):ir(ir), opcode(opcode), reg(reg), args(args), align(align){}
  Instruction(llvm::Instruction *);
  Instruction(){}
  std::string ir;
  std::string opcode;
  std::string reg;
  std::vector<ir2yaml::Arg> args;
  unsigned align;
};
}
template <> struct llvm::yaml::MappingTraits<ir2yaml::Instruction> {
  static void mapping(IO &IO, ir2yaml::Instruction & instruction);
};
LLVM_YAML_IS_SEQUENCE_VECTOR(ir2yaml::Instruction)
#endif //__INSTRUCTION_H_
