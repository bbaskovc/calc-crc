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

### Build the Project

Use CMake to configure and build your project. Open a terminal, navigate to your project directory, and run the following commands.

```bash
mkdir build && cd build
cmake ..
make
```

### Run the Example

After building the project, you can run the example to see the CRC calculations in action.

```bash
./calc_crc_example_simple
```