# Changelog

All notable changes to this project will be documented in this file. See [standard-version](https://github.com/conventional-changelog/standard-version) for commit guidelines.

## [v1.0.0](https://github.com/bbaskovc/calc-crc/tree/v1.0.0) - 2025-03-06

### 🚀 Features

- **CRC Module**: Implemented a comprehensive CRC (Cyclic Redundancy Check) module with the following capabilities:
- **Initialization**: Added CALC_CRC_Init function to initialize a CRC instance with a specified configuration and type (e.g., CRC-8, CRC-16).
- **Calculation**: Added CALC_CRC_Calculate function to compute the CRC value for a given data buffer.
- **Update**: Added CALC_CRC_Update function to update the CRC value incrementally with new chunks of data.
- **Finalization**: Added CALC_CRC_Finalize function to finalize the CRC computation and retrieve the result.

### 📚 Documentation

API Documentation: Documented the CRC module's API, including function descriptions, parameters, and return values.

### 📊 Examples

- Provided example code snippets demonstrating how to initialize, update, and finalize CRC calculations.
