#!/usr/bin/env bash

set -eo pipefail

LLVM_DIR=$(find /usr -name AddLLVM.cmake -printf '%h\n' -quit)
[[ -d "${LLVM_DIR}" ]] || { >&2 echo "Couldn't infer LLVM_DIR"; exit 1; }
export LLVM_DIR

kinds=(module function block)

for kind in "${kinds[@]}"; do
  dir=$(mktemp -d)
  llvm-passgen --dest "${dir}" --kind "${kind}" Test
  cd "${dir}/Test/build" || { >&2 echo "Couldn't cd to pass build dir: ${dir}/build"; exit 1; }
  cmake ..
  make
done
