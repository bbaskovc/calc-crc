/***********************************************************************************************************************
 *
 * @file        calc_crc_ptypes.h
 * @brief       The component CALC-CRC private types (do not use it outside of component).
 * @author      Blaz Baskovc
 * @copyright   Copyright 2025 Blaz Baskovc
 * @date        2025-03-01
 *
 **********************************************************************************************************************/

#ifndef CALC_CRC_PTYPES_H
#define CALC_CRC_PTYPES_H

// C++ wrapper - Start
#ifdef __cplusplus
extern "C" {
#endif

// --- Includes --------------------------------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

// --- Private Types Prototypes ----------------------------------------------------------------------------------------

// --- Private Macros --------------------------------------------------------------------------------------------------

/**
 * @brief   Macro to check for a NULL pointer and execute an action if the pointer is NULL.
 * @param   ptr Pointer to be checked for NULL.
 * @param   action Action to be executed if the pointer is NULL.
 */
#define CHECK_ARGS_NULL_PTR(ptr, action)                                                                               \
    if (NULL == ptr)                                                                                                   \
    {                                                                                                                  \
        return action;                                                                                                 \
    }

/**
 * @brief   Macro to check for a NULL pointer and execute an action if the pointer is NULL.
 * @param   value Value of size_t to be checked for 0.
 * @param   action Action to be executed if the size is 0.
 */
#define CHECK_ARGS_SIZE(value, check, action)                                                                          \
    if (check == value)                                                                                                \
    {                                                                                                                  \
        return action;                                                                                                 \
    }

/**
 * @brief   Set destination memory buffer to byte value.
 * @param   dst Destination buffer.
 * @param   val Overwrite value.
 * @param   len Buffer length.
 */
#define MEMSET(dst, val, len)                                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        uint8_t *_dstp = (uint8_t *)(dst);                                                                             \
        if (_dstp != NULL)                                                                                             \
        {                                                                                                              \
            for (size_t _i = 0; _i < (len); _i++)                                                                      \
            {                                                                                                          \
                _dstp[_i] = (uint8_t)(val);                                                                            \
            }                                                                                                          \
        }                                                                                                              \
    } while (0)

/**
 * @brief   Macro to check for a NULL pointer and execute an action if the pointer is NULL.
 * @param   ptr Pointer to be checked for NULL.
 * @param   action Action to be executed if the pointer is NULL.
 */
#define CHECK_ARGS_NULL_PTR(ptr, action)                                                                               \
    if (NULL == ptr)                                                                                                   \
    {                                                                                                                  \
        return action;                                                                                                 \
    }

/**
 * @brief   Macro to update the intermediate CRC value.
 */
#define UPDATE_CRC() crc->update_crc = (uint64_t)result;

/**
 * @brief   Macro to update the final CRC value.
 */
#define UPDATE_FINAL() crc->update_crc_final = (uint64_t)result;

/**
 * @brief   Macro to start or continue a CRC update process.
 *          If an update is in progress, it processes the next chunk of data.
 */
#define UPDATE_START()                                                                                                 \
    if (true == crc->update_in_progress)                                                                               \
    {                                                                                                                  \
        if (0 != crc->update_chunk)                                                                                    \
        {                                                                                                              \
            result = (uint8_t)crc->update_crc;                                                                         \
        }                                                                                                              \
        crc->update_chunk++;                                                                                           \
    }

// C++ wrapper - End
#ifdef __cplusplus
}
#endif

#endif /* CALC_CRC_PTYPES_H */

// --- EOF -------------------------------------------------------------------------------------------------------------
