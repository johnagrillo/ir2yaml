#include "arg.h"

using llvm::yaml::MappingTraits;
using llvm::yaml::IO;

void llvm::yaml::MappingTraits<ir2yaml::Arg>::mapping(IO &IO, ir2yaml::Arg & arg){
  IO.mapRequired("type", arg.type);
  IO.mapRequired("value", arg.value);
}
