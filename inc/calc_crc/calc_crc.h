/***********************************************************************************************************************
 *
 * @file        calc_crc.h
 * @brief       The Component CALC-CRC provides a flexible and efficient solution for calculating various CRC (Cyclic
 *              Redundancy Check) values and checksums. This component supports CRC-8, CRC-16, CRC-32, CRC-64, and
 *              checksum calculations, making it ideal for data integrity verification in embedded systems and data
 *              transmission applications.
 * @author      Blaz Baskovc
 * @copyright   Copyright 2025 Blaz Baskovc
 * @date        2025-03-06
 * @version     1.0.0
 *
 *  Author          Date        Version     Comments on that revision
 * ---------------------------------------------------------------------------------------------------------------------
 *  Blaz Baskovc    2025-03-11  1.0.0       First release.
 *
 **********************************************************************************************************************/

#ifndef CALC_CRC_H
#define CALC_CRC_H

// C++ wrapper - Start
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

// --- Includes --------------------------------------------------------------------------------------------------------

#include <stdbool.h>
#include <stddef.h>

#if __has_include("calc_crc_conf.h")
#include "calc_crc_conf.h" // IWYU pragma: keep
#endif                     /* __has_include("calc_crc_conf.h") */

#include "calc_crc/calc_crc_gtypes.h"

// --- Public Defines --------------------------------------------------------------------------------------------------

/**
 * @brief   Component version.
 */
#define CALC_CRC_NAME    "CALC-CRC"    //< Component name as string.
#define CALC_CRC_VERSION (0x01000000U) //< Component version as uint32_t (major.minor.patch.fix).

// --- Public Functions Prototypes -------------------------------------------------------------------------------------

/**
 * @brief   Initialize a CRC instance with the specified configuration.
 * @param   crc         Pointer to the CRC instance to initialize.
 * @param   conf        Pointer to the CRC configuration.
 * @param   type        Type of CRC calculation (e.g., CRC-8, CRC-16).
 * @return  Status code indicating success or failure.
 */
calc_crc_status_e CALC_CRC_Init(calc_crc_t *crc, void *conf, calc_crc_type_e type);

/**
 * @brief   Calculate the CRC value for the given data.
 * @param   crc         Pointer to the CRC instance.
 * @param   data        Pointer to the data buffer.
 * @param   length      Length of the data buffer.
 * @param   result      Pointer to store the calculated CRC value.
 * @return  Status code indicating success or failure.
 */
calc_crc_status_e CALC_CRC_Calculate(calc_crc_t *crc, const void *data, size_t length, void *result);

/**
 * @brief   Update the CRC value with a new chunk of data.
 * @param   crc         Pointer to the CRC instance.
 * @param   data        Pointer to the new data chunk.
 * @param   length      Length of the new data chunk.
 * @return  Status code indicating success or failure.
 */
calc_crc_status_e CALC_CRC_Update(calc_crc_t *crc, const void *data, size_t length);

/**
 * @brief   Finalize the CRC computation and retrieve the result.
 * @param   crc         Pointer to the CRC instance.
 * @param   result      Pointer to store the final CRC value.
 * @return  Status code indicating success or failure.
 */
calc_crc_status_e CALC_CRC_Finalize(calc_crc_t *crc, void *result);

// C++ wrapper - End
#ifdef __cplusplus
}
#endif

#endif /* CALC_CRC_H */

// --- EOF -------------------------------------------------------------------------------------------------------------
