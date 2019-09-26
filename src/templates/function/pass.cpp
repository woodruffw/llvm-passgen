#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
struct {{ pass_name }} : public FunctionPass {
  static char ID;

  {{ pass_name }}() : FunctionPass(ID) {}

  bool doInitialization(Module &M) override {
    // Change this to true if your pass modifies the function!
    return false;
  }

  bool runOnFunction(Function &F) override {
    errs() << "function pass: " << F.getName() << '\n';

    // Change this to true if your pass modifies the function!
    return false;
  }

  bool doFinalization(Module &M) override {
    // Change this to true if your pass modifies the function!
    return false;
  }
};
} // namespace

char {{ pass_name }}::ID = 0;
static RegisterPass<{{ pass_name }}> X("{{ pass_name }}", "{{ pass_name }} pass", true, false);
