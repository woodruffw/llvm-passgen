#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
struct {{ pass_name }} : public LoopPass {
  static char ID;

  {{ pass_name }}() : LoopPass(ID) {}

  bool doInitialization(Loop *L, LPPassManager &LPM) override {
    // Change this to true if your pass modifies any loops!
    return false;
  }

  bool runOnLoop(Loop *L, LPPassManager &LPM) override {
    errs() << "loop pass: " << L << '\n';

    // Change this to true if your pass modifies the loop!
    return false;
  }

  bool doFinalization() override {
    // Change this to true if your pass modifies any loops!
    return false;
  }
};
} // namespace

char {{ pass_name }}::ID = 0;
static RegisterPass<{{ pass_name }}> X("{{ pass_name }}", "{{ pass_name }} pass", true, false);
