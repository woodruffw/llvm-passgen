#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
struct {{ pass_name }} : public ModulePass {
  static char ID;

  {{ pass_name }}() : ModulePass(ID) {}

  bool runOnModule(Module &M) override {
    errs() << "module pass: " << M.getName() << '\n';

    // Change this to true if your pass modifies the module!
    return false;
  }
};
} // namespace

char {{ pass_name }}::ID = 0;
static RegisterPass<{{ pass_name }}> X("{{ pass_name }}", "{{ pass_name }} pass", true, false);
