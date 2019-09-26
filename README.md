llvm-passgen
============

[![Build Status](https://travis-ci.com/woodruffw/llvm-passgen.svg?branch=master)](https://travis-ci.com/woodruffw/llvm-passgen)

A tool for rapidly creating LLVM pass skeletons.

## Overview

```bash
cargo install llvm-passgen
# or, build locally with `cargo build`
```

## Usage

```bash
llvm-passgen --kind module Foo
cd Foo/Build
cmake ..
make
```

If `cmake ..` fails, you may need to set `LLVM_DIR` to the LLVM CMake configuration:

```bash
LLVM_DIR=/path/to/llvm/lib/cmake cmake ..
```

See `llvm-passgen --help` for a full list of options.
