#include "module.h"

void llvm::yaml::MappingTraits<ir2yaml::Module>::mapping(IO &IO, ir2yaml::Module & module)
{
  IO.mapRequired("globals", module.globals);
  IO.mapRequired("functions", module.functions);
}


