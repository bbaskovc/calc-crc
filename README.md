# CALC-CRC 

The Component CALC-CRC provides a flexible and efficient solution for calculating various CRC (Cyclic Redundancy Check) values and checksums. This component supports CRC-8, CRC-16, CRC-32, CRC-64, and checksum calculations, making it ideal for data integrity verification in embedded systems and data transmission applications.

<p align="center">
    <a href="https://github.com/bbaskovc/calc-crc/blob/main/LICENSE.md"><img src="https://img.shields.io/github/license/bbaskovc/calc-crc.svg" alt="GitHub License"></a>
    <a href="http://ansicolortags.readthedocs.io/?badge=latest"><img src="https://readthedocs.org/projects/ansicolortags/badge/?version=latest" alt="Documentation Status"></a>
    <a href="https://github.com/bbaskovc/calc-crc/issues"><img src="https://img.shields.io/github/issues/bbaskovc/calc-crc.svg" alt="GitHub Issues"></a>
    <a href="https://github.com/bbaskovc/calc-crc/releases/"><img src="https://img.shields.io/github/release/bbaskovc/calc-crc.svg" alt="GitHub Release"></a>
    <br/>
    <a href="https://github.com/bbaskovc/calc-crc/stargazers/"><img src="https://img.shields.io/github/stars/bbaskovc/calc-crc.svg?style=social&label=Star" alt="GitHub Stars"></a>
    <a href="https://github.com/bbaskovc/calc-crc/network/"><img src="https://img.shields.io/github/forks/bbaskovc/calc-crc.svg?style=social&label=Fork" alt="GitHub Forks"></a>
</p>

## Table of Contents

- [Features](#features)
- [Dependencies](#dependencies)
    - [Software](#software)
    - [Components](#components)
- [Folder & File Structure](#folder--file-structure)
- [Exposed Functions](#exposed-functions)
- [Using the CALC-CRC](#using-the-calc-crc)
- [Examples](#examples)
- [Integrating CALC-CRC into Your Project](#integrating-calc-crc-into-your-project)
    - [Prerequisites](#prerequisites)
    - [Adding CALC-CRC to Your Project](#adding-calc-crc-to-your-project)

## Features

* **Multi-CRC Support:** Calculate CRC-8, CRC-16, CRC-32, and CRC-64 values.
* **Checksum Calculation:** Calculate simple checksums for data verification.
* **Configurable Polynomial:** Customizable polynomial values for CRC calculations.
* **Multiple Instances:** Supports multiple CRC instances, each with its own configuration.
* **Low Latency:** Fast calculation with minimal processing overhead.
* **Efficient Memory Usage:** Memory-efficient implementations suitable for embedded systems.
* **~~Thread-Safe~~:** Ensures thread-safe operations for multi-threaded environments (if needed).
* **~~Tracing Support~~:** Integrated tracing for debugging.
* **~~Hardware Acceleration~~:** Support for hardware-based CRC calculation when available, improving performance.

## Dependencies

### Software

- [GCC](https://gcc.gnu.org/)
- [CMake](https://www.mingw-w64.org/)

### Components

No dependencies on other components except standard ones.

## Folder & File Structure

```bash
calc-crc/
├── .devcontainer/      # Configuration for development container (e.g., VS Code dev container).
├── .github/            # GitHub configuration directory (e.g., Actions, workflows).
├── examples/           # Sample applications demonstrating how to use the CRC component.
├── inc/                # Public headers for the CRC calculation interface.
├── src/                # Source files implementing CRC functionality.
├── tests/              # Unit tests and validation for the component.
├── .clang-format       # Configuration file for code formatting with Clang.
├── .gitignore          # Specifies files and directories to be ignored by Git.
├── .gitmodules         # Git submodule configuration.
├── CMakeLists.txt      # CMake configuration for building the component.
├── LICENSE.md          # License terms for the component.
└── README.md           # Documentation and usage instructions.
```

## Configurations 

All available customization to component functionality can be found below (add it to file [calc_crc_conf.h](examples/simple/inc/conf/calc_crc_conf.h)).

```c
// Currently, there are no configurations available for this component.
```

## Exposed Functions

```c
// Initialize the CRC instance with the given configuration.
calc_crc_status_e CALC_CRC_Init(calc_crc_t *crc, void *conf, calc_crc_type_e type);

// Unified CRC calculation function that uses the configuration set during initialization.
calc_crc_status_e CALC_CRC_Calculate(calc_crc_t *crc, void *data, size_t length, void *result);

// Update the CRC value with a new data chunk.
calc_crc_status_e CALC_CRC_Update(calc_crc_t *crc, void *data, size_t length);

// Finalize the CRC computation and retrieve the result.
calc_crc_status_e CALC_CRC_Finalize(calc_crc_t *crc, void *result);
```

## Using the CALC-CRC

This example demonstrates how to initialize and use the CALC-CRC component to calculate various CRC values and a checksum.

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "calc_crc/calc_crc.h"

int main(void)
{
    // Define a data buffer to be checked
    uint8_t data[] = "Hello, world!";
    uint32_t crc32_result;
    uint32_t checksum_result;

    // Create a CRC handle
    calc_crc_t crc;

    // Create configurations
    calc_crc_8bit_t crc_conf = {
        .polynomial = CALC_CRC_32BIT_POLYNOMIAL,
        .initial_value = UINT32_MAX,
        .final_value = UINT32_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    // Initialize the CRC instance with default settings
    CALC_CRC_Init(&crc, &crc_conf);

    // Calculate CRC-32 for the given data
    CALC_CRC_Calculate(data, strlen((char *)data), &crc32_result);
    printf("CRC-32: %u\n", crc32_result);

    return 0;
}
```

## Examples

Here are some examples of different types of entries you might check before use.

- [simple](examples/simple/) Example to show how to use CALC-CRC functionality.

## Integrating `CALC-CRC` into Your project  

### Prerequisites  

Ensure you have CMake installed and a compatible toolchain for your target platform.  

### Adding `CALC-CRC` to Your Project  

To include `CALC-CRC` in your project, follow these steps:  

1. **Clone the repository** (or add it as a submodule):  
    Clone repository:
    ```bash
    git clone https://github.com/bbaskovc/calc-crc components/calc-crc
    ```

    Add submodule:
    ```bash
    git submodule add https://github.com/your-repo/calc-crc.git components/calc-crc
    ```

2. **Modify** your project's CMakeLists.txt to include the component:
    ```cmake
    # Minimum required version of CMake
    cmake_minimum_required(VERSION 3.16)

    # Set the project name and version
    project(my_project)

    # Add project source files
    set(SRC_FILES
        src/main.c
    )

    # Add project include directories
    set(INC_DIRS
        inc/ 
    )

    # Add project libraries for linking
    set(REQ_LIBS
        calc-crc
    )

    # Configure the CALC-CRC component
    set(CALC_CRC_CONF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc/conf CACHE STRING "Directory for configuration files")

    # Add the CALC-CRC component
    add_subdirectory(components/calc-crc)

    # Create the executable 
    add_executable(${PROJECT_NAME} ${SRC_FILES})  

    # Include the directories
    target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIRS})

    # Link the required libraries
    target_link_libraries(${PROJECT_NAME} ${REQ_LIBS})
    ```

3. **Build the project:**
    ```bash
    mkdir build && cd build
    cmake ..
    make
    ```

