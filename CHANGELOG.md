# Changelog

All notable changes to this project will be documented in this file. See [standard-version](https://github.com/conventional-changelog/standard-version) for commit guidelines.

## [v1.0.1](https://github.com/bbaskovc/calc-crc/tree/v1.0.1) - 2025-03-13

- 🐛 Bug Fixes

- Fixed build problem in test ctest.

## [v1.0.0](https://github.com/bbaskovc/calc-crc/tree/v1.0.0) - 2025-03-11

### 🚀 Features

- **CRC Module**: Implemented a comprehensive CRC (Cyclic Redundancy Check) module with the following capabilities:
- **Initialization**: Added CALC_CRC_Init function to initialize a CRC instance with a specified configuration and type (e.g., CRC-8, CRC-16).
- **Calculation**: Added CALC_CRC_Calculate function to compute the CRC value for a given data buffer.
- **Update**: Added CALC_CRC_Update function to update the CRC value incrementally with new chunks of data.
- **Finalization**: Added CALC_CRC_Finalize function to finalize the CRC computation and retrieve the result.
- **Tests Integration**: Integrated CTest, Google Test (GTest), and CppCheck into the project to improve testing and code quality.
    - Added unit tests for the CRC module, covering initialization, calculation, update, and finalization functions.
    - Set up Google Test framework for unit test execution and reporting.
    - Configured CppCheck for static code analysis to identify potential issues and improve code quality.
- **Workflows**: Added GitHub Actions workflows for CI/CD automation.
    - Integrated CTest and GTest into the CI pipeline for automated testing.
    - Configured the workflow to run CppCheck for static code analysis during the build process.
- **DevContainer**: Added a devcontainer configuration to standardize the development environment and simplify setup for contributors.
    - Ensures consistent toolchains and dependencies for all contributors using VS Code's Remote Development feature.

### 📚 Documentation

- **API Docs**: Updated the API documentation to include test functions and how they integrate with the CRC module.
- **Development Setup**: Added documentation on setting up the development environment with DevContainer and running tests with CTest and GTest.

### 🧪 Tests

- Added unit tests for the CRC module using Google Test (GTest).
- Configured CTest to run the GTest tests automatically.

### ⚙️ CI

- Added a GitHub Actions workflow to automate the build, test, and static analysis process using CppCheck.

### 📊 Examples

- Updated example code snippets to include tests for CRC calculations and show how to run them in a CI/CD pipeline.