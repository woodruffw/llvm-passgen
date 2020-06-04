llvm-passgen
============

![license](https://raster.shields.io/badge/license-MIT%20with%20restrictions-green.png)
[![Build Status](https://img.shields.io/github/workflow/status/woodruffw/llvm-passgen/CI/master)](https://github.com/woodruffw/llvm-passgen/actions?query=workflow%3ACI)

A tool for rapidly creating LLVM pass skeletons.

## Overview

```bash
cargo install llvm-passgen
# or, build locally with `cargo build`
```

## Usage

```bash
llvm-passgen --kind module Foo
cd Foo/build
cmake ..
make
```

If `cmake ..` fails, you may need to set `LLVM_DIR` to the LLVM CMake configuration:

```bash
LLVM_DIR=/path/to/llvm/lib/cmake cmake ..
```

See `llvm-passgen --help` for a full list of options.
