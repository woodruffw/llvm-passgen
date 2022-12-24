#!/usr/bin/env bash

set -eo pipefail

if [[ "$(uname)" = "Darwin" ]]; then
  LLVM_DIR=$(find $(brew --prefix)/Cellar/llvm -name AddLLVM.cmake -print0 -quit | xargs -0 dirname)
else
  LLVM_DIR=$(find /usr -name AddLLVM.cmake -printf '%h\n' -quit)
fi
[[ -d "${LLVM_DIR}" ]] || { >&2 echo "Couldn't infer LLVM_DIR"; exit 1; }
export LLVM_DIR

llvm-passgen() {
  cargo run --bin llvm-passgen -- "${@}"
}

kinds=(module function loop)

for kind in "${kinds[@]}"; do
  dir=$(mktemp -d)
  llvm-passgen --dest "${dir}" --kind "${kind}" Test
  pushd "${dir}/Test/build" || { >&2 echo "Couldn't chdir to pass build dir: ${dir}/build"; exit 1; }
  cmake ..
  make
  popd
done
