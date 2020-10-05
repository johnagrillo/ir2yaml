#include "global.h"
#include "tostring.h"

ir2yaml::Global::Global(llvm::GlobalVariable* g) 
{
  if (g->hasInitializer()) {
    init = toString(g->getInitializer());
  }
  name = g->getName().str();
  type = toString(g->getType());
}

void llvm::yaml::MappingTraits<ir2yaml::Global>::mapping(IO &IO, ir2yaml::Global &global) {
  IO.mapRequired("name", global.name);
  IO.mapRequired("constant", global.constant);
  IO.mapRequired("type", global.type);
  IO.mapRequired("init", global.init);
}
