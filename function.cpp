#include "function.h"
#include "tostring.h"
#include "utils.h"
#include "block.h"

ir2yaml::Function::Function(llvm::Function * f)
{
  name = f->getName().str();
  linkage = linkageToString(f->getLinkage());
  visibility = visibilityToString(f->getVisibility());
  cconv =  callingConvToString(f->getCallingConv());
  retType = toString(f->getReturnType());
  dllstorage = storageToString(f->getDLLStorageClass());

  for (auto & arg : f->args())
  {
    args.push_back(ir2yaml::Arg(toString(arg.getType()),toStringOperand(&arg, false)));
  }
  
  for (llvm::AttributeSet attr : f->getAttributes())
  {
    attrs.push_back(attr.getAsString());
  }
  
  for (llvm::BasicBlock &bb : f->getBasicBlockList())
  {
    blocks.push_back(ir2yaml::Block(&bb));
  }
}
  
using llvm::yaml::MappingTraits;
using llvm::yaml::IO;
void llvm::yaml::MappingTraits<ir2yaml::Function>::mapping(IO &IO, ir2yaml::Function & function)
{
  IO.mapRequired("name", function.name);
  if (function.args.size()>0)
  {
    IO.mapOptional("args", function.args);
  }
  IO.mapRequired("retType", function.retType);
  IO.mapRequired("linkage", function.linkage);

  if (function.visibility != "")
  {
    IO.mapRequired("visibility", function.visibility);
  }
  
  IO.mapRequired("cconv", function.cconv);

  if (function.dllstorage != "")
  {
    IO.mapOptional("dllstorage", function.dllstorage);
  }
  if (function.blocks.size()>0)
  {
    IO.mapOptional("blocks", function.blocks);
  }
  if (function.attrs.size()>0)
  {
    IO.mapRequired("attrs", function.attrs);
  }
  
}
