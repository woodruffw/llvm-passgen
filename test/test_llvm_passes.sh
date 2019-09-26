#!/usr/bin/env bash

kinds=(module function block)

for kind in "${kinds[@]}"; do
  dir=$(mktemp -d)
  llvm-passgen --dest "${dir}" --kind "${kind}" Test
  cd "${dir}/Test/build" || { >&2 echo "Couldn't cd to pass build dir: ${dir}/build"; exit 1; }
  cmake ..
  make
done
