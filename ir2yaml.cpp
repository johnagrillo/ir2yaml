//===-- ir2yaml.cpp - convertr ir to yaml --------------------===//
//
//===----------------------------------------------------------------------===//
//
// This utility may be invoked in the following manner:
//  ir2yaml [options]      - Read LLVM bitcode from stdin, write asm to stdout
//  ir2yaml [options] x.bc - Read LLVM bitcode from the x.bc file, write yaml
//                            to the x.yaml file.
//  Options:
//      --help   - Output information about command line switches
//
//===----------------------------------------------------------------------===//

#include "module.h"
#include "utils.h"
#include "yaml.h"
#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"

using llvm::yaml::IO;
using llvm::yaml::MappingTraits;

std::vector<ir2yaml::Function> getFunctions(std::unique_ptr<llvm::Module> &mod);

llvm::cl::opt<std::string> InputFilename(llvm::cl::Positional,
                                         llvm::cl::desc("<input file>"),
                                         llvm::cl::init("-"));

int main(int argc, char **argv) {

  llvm::InitLLVM X(argc, argv);
  llvm::cl::ParseCommandLineOptions(argc, argv);

  if (InputFilename != "-") {
    if (llvm::sys::fs::exists(InputFilename) == false) {
      llvm::errs() << "no such file " << InputFilename << "\n";
      return -1;
    }
  }
 
  ir2yaml::Module module;
  llvm::LLVMContext context;
  llvm::SMDiagnostic Err;
  std::unique_ptr<llvm::Module> mod = llvm::parseIRFile(InputFilename, Err, context);

  std::vector<ir2yaml::Global> globals;
  for (llvm::GlobalVariable &g : mod->getGlobalList()) 
  {
    module.globals.push_back(ir2yaml::Global(&g));    
  }

  std::vector<ir2yaml::Function> functions;
  for (llvm::Function &func : mod->getFunctionList()) 
  {
    module.functions.push_back(ir2yaml::Function(&func));    
  }


  llvm::yaml::Output yout(llvm::outs());
  yout << module;
  return 0;
}

/*
  llvm::Module mod("test", context);
  llvm::IRBuilder<> b(context);

  b.getDoubleTy();

  std::vector<Type *> fargs = {b.getInt32Ty(), b.getInt32Ty(),
  b.getInt32Ty()}; FunctionType *FT = FunctionType::get(b.getVoidTy(), fargs,
  false);

  // Create A Function

  llvm::Function *func =
  llvm::Function::Create(FT, Function::ExternalLinkage, "test", &mod);

  Function::arg_iterator args = func->arg_begin();
  Value *x = args++;
  x->setName("x");
  Value *y = args++;
  y->setName("y");
  Value *z = args++;
  z->setName("z");

  // llvm::errs() << mod << "\n";
  */
//  return 0;
//}

/*

  void traverse_ca(llvm::Constant *ca, std::string indent = "") {
  // handle zero init

  if (llvm::ConstantAggregateZero *caz =
  llvm::dyn_cast<llvm::ConstantAggregateZero>(ca)) {
  for (uint32_t elem = 0; elem < caz->getNumElements(); elem++) {
  llvm::Constant *cons = caz->getElementValue(elem);
  llvm::errs() << indent << *cons << "\n";

  if (cons->getType()->isAggregateType()) {
  traverse_ca(cons, indent + "  ");
  }
  }
  }
  // CSD has no operands
  else if (llvm::ConstantDataSequential *cds =
  llvm::dyn_cast<llvm::ConstantDataSequential>(ca)) {
  for (unsigned elem = 0; elem < cds->getNumElements(); elem++) {
  llvm::errs() << (indent + " ") << *cds->getElementAsConstant(elem)
  << "\n";
  }
  }
  // CA have operands
  else {
  for (auto &op : ca->operands()) {
  traverse_ca(llvm::dyn_cast<llvm::Constant>(op), indent + "  ");
  }
  }
  }
*/


