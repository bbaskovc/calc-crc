# Test - gtest

Welcome to the `gtest` project! This document provides an overview of the project structure and instructions for building and running the tests.

## Dependencies

### Software

- [GCC](https://gcc.gnu.org/)
- [CMake](https://cmake.org/)

### Components

- [googletest](https://github.com/google/googletest/)

## Project Structure

The project is organized as follows:

```bash
tests/gtest/
├── inc/                        # Header files for the test suite.
│   └── conf/                   # Configuration-specific headers.
│       └── calc_crc_conf.h     # Configuration settings for the calc-crc library.
├── src/                        # Source files related to testing.
│   └── tests/                  # Test implementations.
│       └── performance.cpp     # Performance tests for calc-crc.
└── CMakeLists.txt              # CMake configuration for building the test suite.
```

## Building the Project

To build the project, follow these steps:

1. Navigate to the project directory:
   ```bash
   cd /workspaces/calc-crc
   ```

3. Run CMake to configure the build:
   ```bash
   cmake -B build -S tests/gtest
   ```

4. Build the project using make:
   ```bash
   make -C build
   ```

## Running the Tests

After building the project, you can run the tests using the following command:
```bash
./build/calc_crc_gtest_test_performance
```