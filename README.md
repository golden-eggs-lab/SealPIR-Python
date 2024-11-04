# Seal-PIR for Python

Microsoft SEAL is an easy-to-use open-source (MIT licensed) homomorphic encryption library developed by the Cryptography Research group at Microsoft.

SealPIR allows a client to download an element from a database stored by a server without revealing to the server which element was downloaded.

pybind11 is a lightweight header-only library that exposes C++ types in Python and vice versa, mainly to create Python bindings of existing C++ code.

Seal-PIR for Python creates bindings for the Microsoft Seal-PIR library using pybind11.

## Contents
* Setup
* Build bindings

## Setup
Ensure Microsoft SEAL, Microsoft SEAL python bindings, SEAL-PIR, and pybind11 are correctly built and installed.

## Version
This is version v1.0.0 of SealPIR-Python bindings.

## Build
Recommended: Clang++ (>==10.0) or GNU G++ (>=9.4), CMake (>=3.16)

```bash
# Clone repo
$ git clone https://github.com/golden-eggs-lab/SealPIR-Python
$ cd SealPIR-Python

# Initialize submodules
$ git submodule update --init --recursive

# Build SEAL
$ cd src/SealPIR/SEAL
$ cmake -S . -B build -DSEAL_USE_MSGSL=OFF -DSEAL_USE_ZLIB=OFF -DSEAL_USE_ZSTD=OFF
$ cmake --build build

# Build SealPIR
$ cd ..
$ cmake .
$ make

# Build bindings
$ cd ../..
$ python setup.py build_ext -i

# Test
$ cp seal.*.so ./test
$ cp sealpir.*.so ./test
$ python ./test/test.py
```

## Note
To run the tests and use the SealPIR bindings, the SEAL-Python bindings must be generated: they can be built with [SEAL-Python](https://github.com/Huelse/SEAL-Python).

## Acknowlegement and License
SealPIR-Python uses [Microsoft SEAL](https://github.com/microsoft/SEAL) and [Seal-PIR](https://github.com/microsoft/SealPIR). Python bindings for Microsoft SEAL are also required and can be built with [SEAL-Python](https://github.com/Huelse/SEAL-Python).

Minor modifications were made to the SealPIR library to use data types that are compatiblie with pybind11 and python.

[MIT License](/LICENSE)