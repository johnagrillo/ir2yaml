#include "utils.h"

unsigned getAlignment(llvm::Instruction *ins) {
  unsigned align = 0;
  if (llvm::AllocaInst *ai = llvm::dyn_cast<llvm::AllocaInst>(ins)) {
    align = ai->getAlignment();
  } else if (llvm::StoreInst *si = llvm::dyn_cast<llvm::StoreInst>(ins)) {
    align = si->getAlignment();
  } else if (llvm::LoadInst *li = llvm::dyn_cast<llvm::LoadInst>(ins)) {
    align = li->getAlignment();
  }
  //} else if (llvm::CallInst *ci = llvm::dyn_cast<llvm::CallInst>(&ins)) {
  //  align = 0; // return ci->getRetAlignment();
  //}
  return align;
}



  

