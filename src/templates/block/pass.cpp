#include "llvm/IR/BasicBlock.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
struct {{ pass_name }} : public BasicBlockPass {
  static char ID;

  {{ pass_name }}() : BasicBlockPass(ID) {}

  bool doInitialization(Function &F) override {
    // Change this to true if your pass modifies the function!
    return false;
  }

  bool runOnBasicBlock(BasicBlock &BB) override {
    errs() << "basic block pass: " << BB << '\n';

    // Change this to true if your pass modifies the basic block!
    return false;
  }

  bool doFinalization(Function &F) override {
    // Change this to true if your pass modifies the function!
    return false;
  }
};
} // namespace

char {{ pass_name }}::ID = 0;
static RegisterPass<{{ pass_name }}> X("{{ pass_name }}", "{{ pass_name }} pass", true, false);
