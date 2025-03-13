/***********************************************************************************************************************
 *
 * @file        calc_crc_gtypes.h
 * @brief       Global types for the CALC-CRC component, separated from main files for easy inclusion.
 * @author      Blaz Baskovc
 * @copyright   Copyright 2025 Blaz Baskovc
 * @date        2025-03-01
 *
 **********************************************************************************************************************/

#ifndef CALC_CRC_GTYPES_H
#define CALC_CRC_GTYPES_H

// C++ wrapper - Start
#ifdef __cplusplus
extern "C" {
#endif

// --- Includes --------------------------------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

// --- Public Defines --------------------------------------------------------------------------------------------------

#define CALC_CRC_8BIT_POLYNOMIAL  ((uint8_t)0x07)                // Default polynomial for 8-bit CRC calculation.
#define CALC_CRC_16BIT_POLYNOMIAL ((uint16_t)0x1021)             // Default polynomial for 16-bit CRC calculation.
#define CALC_CRC_32BIT_POLYNOMIAL ((uint32_t)0x04C11DB7)         // Default polynomial for 32-bit CRC calculation.
#define CALC_CRC_64BIT_POLYNOMIAL ((uint64_t)0x42F0E1EBA9EA3693) // Default polynomial for 64-bit CRC calculation.

// --- Public Types Prototypes -----------------------------------------------------------------------------------------

/**
 * @brief   Enumeration representing the supported CRC calculation types.
 */
typedef enum
{
    CALC_CRC_TYPE_8BIT = 0u, // 8-bit CRC calculation.
    CALC_CRC_TYPE_16BIT,     // 16-bit CRC calculation.
    CALC_CRC_TYPE_32BIT,     // 32-bit CRC calculation.
    CALC_CRC_TYPE_64BIT,     // 64-bit CRC calculation.
    CALC_CRC_TYPE_MAX        // Maximum number of supported CRC types.
} calc_crc_type_e;

/**
 * @brief   Enumeration representing the response status of a function.
 */
typedef enum
{
    CALC_CRC_STATUS_OK = 0u,                  // Operation completed successfully.
    CALC_CRC_STATUS_ERROR,                    // General error occurred.
    CALC_CRC_STATUS_ERROR_INPUT_ARGS,         // Invalid input arguments provided.
    CALC_CRC_STATUS_ERROR_INVALID_TYPE,       // Invalid input arguments provided.
    CALC_CRC_STATUS_ERROR_UPDATE_NOT_STARTED, // Invalid input arguments provided.
    CALC_CRC_STATUS_MAX                       // Maximum number of status types.
} calc_crc_status_e;

/**
 * @brief   Structure representing an 8-bit CRC configuration.
 */
typedef struct
{
    uint8_t table[256];    // Precomputed CRC lookup table.
    uint8_t polynomial;    // CRC polynomial used for calculation.
    uint8_t initial_value; // Initial value for CRC computation.
    uint8_t final_value;   // Final XOR value for CRC computation.
    bool input_reflected;  // Reflect input data (true = enabled, false = disabled).
    bool output_reflected; // Reflect output CRC (true = enabled, false = disabled).
} calc_crc_8bit_t;

/**
 * @brief   Structure representing a CALC-CRC 16-bit configurations.
 */
typedef struct
{
    uint16_t table[256];
    uint16_t polynomial;
    uint16_t initial_value;
    uint16_t final_value;
    bool input_reflected;
    bool output_reflected;
} calc_crc_16bit_t;

/**
 * @brief   Structure representing a CALC-CRC 32-bit configurations.
 */
typedef struct
{
    uint32_t table[256];
    uint32_t polynomial;
    uint32_t initial_value;
    uint32_t final_value;
    bool input_reflected;
    bool output_reflected;
} calc_crc_32bit_t;

/**
 * @brief   Structure representing a CALC-CRC 64-bit configurations.
 */
typedef struct
{
    uint64_t table[256];
    uint64_t polynomial;
    uint64_t initial_value;
    uint64_t final_value;
    bool input_reflected;
    bool output_reflected;
} calc_crc_64bit_t;

/**
 * @brief   Structure representing a CRC computation object.
 */
typedef struct
{
    void *conf;                // Pointer to the CRC configuration settings.
    uint64_t update_crc;       // Intermediate CRC value during updates.
    uint64_t update_crc_final; // Final CRC value after all updates.
    size_t update_chunk;       // Size of the current data chunk being processed.
    calc_crc_type_e type;      // Type of CRC calculation (e.g., CRC-8, CRC-16).
    bool update_in_progress;   // Flag indicating if a CRC update is in progress.
} calc_crc_t;

// C++ wrapper - End
#ifdef __cplusplus
}
#endif

#endif /* CALC_CRC_GTYPES_H */

// --- EOF -------------------------------------------------------------------------------------------------------------
