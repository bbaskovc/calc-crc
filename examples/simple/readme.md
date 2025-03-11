# Example SIMPLE

The `CALC-CRC` component provides a flexible and efficient solution for calculating various CRC (Cyclic Redundancy Check) values and checksums. It supports CRC-8, CRC-16, CRC-32, CRC-64, and checksum calculations, making it ideal for data integrity verification in embedded systems and data transmission applications.

## Example Overview

The example provided in this repository demonstrates how to:

- Initialize a CRC instance with custom configurations.
- Calculate CRC-8, CRC-16, CRC-32, and CRC-64 values for a given data buffer.
- Calculate a simple checksum for data verification.
- Update the CRC value with new data chunks.
- Finalize the CRC computation and retrieve the result.

## Build Instructions

Follow these steps to build the CALC-CRC component and integrate it into your project.

1. Navigate to the project directory:
   ```bash
   cd /workspaces/calc-crc
   ```

2. Run CMake to configure the build:
   ```bash
   cmake -B build -S examples/simple
   ```

3. Build the project using make:
   ```bash
   make -C build
   ```

## Run the Example

After building the project, you can run the example to see the CRC calculations in action.

```bash
./build/calc_crc_example_simple
```