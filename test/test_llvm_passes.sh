#!/usr/bin/env bash

set -eo pipefail

LLVM_DIR=$(find /usr -name AddLLVM.cmake -printf '%h\n' -quit)
[[ -d "${LLVM_DIR}" ]] || { >&2 echo "Couldn't infer LLVM_DIR"; exit 1; }
export LLVM_DIR

llvm-passgen() {
  cargo run --bin llvm-passgen -- "${@}"
}

kinds=(module function loop)

for kind in "${kinds[@]}"; do
  dir=$(mktemp -d)
  llvm-passgen --dest "${dir}" --kind "${kind}" Test
  cd "${dir}/Test/build" || { >&2 echo "Couldn't cd to pass build dir: ${dir}/build"; exit 1; }
  cmake ..
  make
done
