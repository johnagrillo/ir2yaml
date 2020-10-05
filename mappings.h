
#ifndef __MAPPINGS_H__
#define __MAPPINGS_H__
struct Global {
  std::string name;
  bool constant;
  std::string type;
  std::string ir;
};
template <> struct llvm::yaml::MappingTraits<Global> {
  static void mapping(IO &IO, Global &global) {
    IO.mapRequired("name", global.name);
    IO.mapRequired("constant", global.constant);
    IO.mapRequired("type", global.type);
    IO.mapRequired("ir", global.ir);
  };
};

struct Arg {
  Arg(std::string type, std::string value) : type(type), value(value){};
  Arg(){};
  std::string type;
  std::string value;
};

template <> struct llvm::yaml::MappingTraits<::Arg> {
  static void mapping(IO &IO, ::Arg &arg) {
    IO.mapRequired("type", arg.type);
    IO.mapRequired("value", arg.value);
  };
};

struct Instruction {
  std::string ir;
  std::string opcode;
  std::string reg;
  std::vector<Arg> args;
  unsigned align = 0;
};
template <> struct llvm::yaml::MappingTraits<::Instruction> {
  static void mapping(IO &IO, ::Instruction &ins) {
    IO.mapRequired("ir", ins.ir);
    IO.mapRequired("opcode", ins.opcode);
    IO.mapRequired("reg", ins.reg);
    IO.mapRequired("args", ins.args);
    if (ins.align > 0) {
      IO.mapOptional("align", ins.align);
    }
  };
};

struct Block {
  std::string name;
  std::vector<::Instruction> ins;
};

template <> struct llvm::yaml::MappingTraits<Block> {
  static void mapping(IO &IO, Block &block) {
    IO.mapRequired("name", block.name);
    IO.mapRequired("ins", block.ins);
  };
};

struct Function {
  std::string name;
  std::vector<Arg> args;
  std::string retType;
  std::vector<Block> blocks;
  std::vector<std::string> attrs;
};

template <> struct llvm::yaml::MappingTraits<::Function> {
  static void mapping(IO &IO, ::Function &func) {
    IO.mapRequired("name", func.name);
    IO.mapRequired("args", func.args);
    IO.mapRequired("retType", func.retType);
    if (func.attrs.size() > 0) {
      IO.mapOptional("attrs", func.attrs);
    }
    IO.mapRequired("blocks", func.blocks);
  }
};

struct Yaml {
  std::vector<Global> globals;
  std::vector<::Function> functions;
};

namespace llvm {
namespace yaml {

template <> struct MappingTraits<::Yaml> {
  static void mapping(IO &IO, ::Yaml &yaml) {
    IO.mapRequired("Globals", yaml.globals);
    IO.mapRequired("Functions", yaml.functions);
  }
};
} // namespace yaml
} // namespace llvm

LLVM_YAML_IS_SEQUENCE_VECTOR(Global)
LLVM_YAML_IS_SEQUENCE_VECTOR(::Function)
LLVM_YAML_IS_SEQUENCE_VECTOR(::Block)
LLVM_YAML_IS_SEQUENCE_VECTOR(::Instruction)
LLVM_YAML_IS_SEQUENCE_VECTOR(::Arg)

#endif
