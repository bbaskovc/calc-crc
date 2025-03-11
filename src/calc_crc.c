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

// --- Includes --------------------------------------------------------------------------------------------------------

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#if __has_include("calc_crc_conf.h")
#include "calc_crc_conf.h"
#endif /* __has_include("calc_crc_conf.h") */

#ifdef CALC_CRC_CONF_FREERTOS_USE
#if (true == CALC_CRC_CONF_FREERTOS_USE)

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#endif /* (true == CALC_CRC_CONF_FREERTOS_USE) */
#endif /* CALC_CRC_CONF_FREERTOS_USE */

#include "calc_crc/calc_crc_ptypes.h"
#include "calc_crc/calc_crc_gtypes.h"
#include "calc_crc/calc_crc.h"

// --- Private Functions Prototypes ------------------------------------------------------------------------------------

/**
 * @brief   Calculate a CRC-8 lookup table using the specified polynomial.
 * @param   table       Pointer to the table to store the CRC values.
 * @param   polynomial  Polynomial value for the CRC-8 calculation.
 */
static void _calc_table_crc8(uint8_t *table, uint8_t polynomial);

/**
 * @brief   Calculate a CRC-16 lookup table using the specified polynomial.
 * @param   table       Pointer to the table to store the CRC values.
 * @param   polynomial  Polynomial value for the CRC-16 calculation.
 */
static void _calc_table_crc16(uint16_t *table, uint16_t polynomial);

/**
 * @brief   Calculate a CRC-32 lookup table using the specified polynomial.
 * @param   table       Pointer to the table to store the CRC values.
 * @param   polynomial  Polynomial value for the CRC-32 calculation.
 */
static void _calc_table_crc32(uint32_t *table, uint32_t polynomial);

/**
 * @brief   Calculate a CRC-64 lookup table using the specified polynomial.
 * @param   table       Pointer to the table to store the CRC values.
 * @param   polynomial  Polynomial value for the CRC-64 calculation.
 */
static void _calc_table_crc64(uint64_t *table, uint64_t polynomial);

/**
 * @brief   Calculate the CRC-8 value for the given data.
 * @param   crc         Pointer to the CRC instance.
 * @param   conf        Pointer to the CRC-8 configuration.
 * @param   data        Pointer to the data buffer.
 * @param   length      Length of the data buffer.
 * @return  Calculated CRC-8 value.
 */
static uint8_t _calc_crc8(calc_crc_t *crc, calc_crc_8bit_t *conf, const uint8_t *data, size_t length);

/**
 * @brief   Calculate the CRC-16 value for the given data.
 * @param   crc         Pointer to the CRC instance.
 * @param   conf        Pointer to the CRC-16 configuration.
 * @param   data        Pointer to the data buffer.
 * @param   length      Length of the data buffer.
 * @return  Calculated CRC-16 value.
 */
static uint16_t _calc_crc16(calc_crc_t *crc, calc_crc_16bit_t *conf, const uint8_t *data, size_t length);

/**
 * @brief   Calculate the CRC-32 value for the given data.
 * @param   crc         Pointer to the CRC instance.
 * @param   conf        Pointer to the CRC-32 configuration.
 * @param   data        Pointer to the data buffer.
 * @param   length      Length of the data buffer.
 * @return  Calculated CRC-32 value.
 */
static uint32_t _calc_crc32(calc_crc_t *crc, calc_crc_32bit_t *conf, const uint8_t *data, size_t length);

/**
 * @brief   Calculate the CRC-64 value for the given data.
 * @param   crc         Pointer to the CRC instance.
 * @param   conf        Pointer to the CRC-64 configuration.
 * @param   data        Pointer to the data buffer.
 * @param   length      Length of the data buffer.
 * @return  Calculated CRC-64 value.
 */
static uint64_t _calc_crc64(calc_crc_t *crc, calc_crc_64bit_t *conf, const uint8_t *data, size_t length);

/**
 * @brief   Reflect the bits in an 8-bit value.
 * @param   data        The 8-bit value to reflect.
 * @return  Reflected 8-bit value.
 */
static uint8_t _reflect_crc8(uint8_t data);

/**
 * @brief   Reflect the bits in a 16-bit value.
 * @param   data        The 16-bit value to reflect.
 * @return  Reflected 16-bit value.
 */
static uint16_t _reflect_crc16(uint16_t data);

/**
 * @brief   Reflect the bits in a 32-bit value.
 * @param   data        The 32-bit value to reflect.
 * @return  Reflected 32-bit value.
 */
static uint32_t _reflect_crc32(uint32_t data);

/**
 * @brief   Reflect the bits in a 64-bit value.
 * @param   data        The 64-bit value to reflect.
 * @return  Reflected 64-bit value.
 */
static uint64_t _reflect_crc64(uint64_t data);

// --- Public Functions Definitions ------------------------------------------------------------------------------------

calc_crc_status_e CALC_CRC_Init(calc_crc_t *crc, void *conf, calc_crc_type_e type)
{
    CHECK_ARGS_NULL_PTR(crc, CALC_CRC_STATUS_ERROR_INPUT_ARGS);
    CHECK_ARGS_NULL_PTR(conf, CALC_CRC_STATUS_ERROR_INPUT_ARGS);

    if (CALC_CRC_TYPE_MAX <= type)
    {
        return CALC_CRC_STATUS_ERROR_INVALID_TYPE;
    }

    MEMSET(crc, 0, sizeof(calc_crc_t));

    crc->type = type;
    crc->conf = conf;

    switch (type)
    {
        case CALC_CRC_TYPE_8BIT: //
        {
            calc_crc_8bit_t *ptr = (calc_crc_8bit_t *)crc->conf;
            _calc_table_crc8(ptr->table, ptr->polynomial);
            break;
        }
        case CALC_CRC_TYPE_16BIT: //
        {
            calc_crc_16bit_t *ptr = (calc_crc_16bit_t *)crc->conf;
            _calc_table_crc16(ptr->table, ptr->polynomial);
            break;
        }
        case CALC_CRC_TYPE_32BIT: //
        {
            calc_crc_32bit_t *ptr = (calc_crc_32bit_t *)crc->conf;
            _calc_table_crc32(ptr->table, ptr->polynomial);
            break;
        }
        case CALC_CRC_TYPE_64BIT: //
        {
            calc_crc_64bit_t *ptr = (calc_crc_64bit_t *)crc->conf;
            _calc_table_crc64(ptr->table, ptr->polynomial);
            break;
        }
        default:
            break;
    }

    return CALC_CRC_STATUS_OK;
}

calc_crc_status_e CALC_CRC_Calculate(calc_crc_t *crc, const void *data, size_t length, void *result)
{
    CHECK_ARGS_NULL_PTR(crc, CALC_CRC_STATUS_ERROR_INPUT_ARGS);
    CHECK_ARGS_NULL_PTR(data, CALC_CRC_STATUS_ERROR_INPUT_ARGS);
    CHECK_ARGS_NULL_PTR(result, CALC_CRC_STATUS_ERROR_INPUT_ARGS);
    CHECK_ARGS_SIZE(length, 0, CALC_CRC_STATUS_ERROR_INPUT_ARGS);

    if (CALC_CRC_TYPE_MAX <= crc->type)
    {
        return CALC_CRC_STATUS_ERROR_INVALID_TYPE;
    }

    switch (crc->type)
    {
        case CALC_CRC_TYPE_8BIT: // ---- 8-bit calculator
        {
            calc_crc_8bit_t *conf = (calc_crc_8bit_t *)crc->conf;
            uint8_t *calc = (uint8_t *)result;
            *calc = _calc_crc8(crc, conf, data, length);
            break;
        }
        case CALC_CRC_TYPE_16BIT: // --- 16-bit calculator
        {
            calc_crc_16bit_t *conf = (calc_crc_16bit_t *)crc->conf;
            uint16_t *calc = (uint16_t *)result;
            *calc = _calc_crc16(crc, conf, data, length);
            break;
        }
        case CALC_CRC_TYPE_32BIT: // --- 32-bit calculator
        {
            calc_crc_32bit_t *conf = (calc_crc_32bit_t *)crc->conf;
            uint32_t *calc = (uint32_t *)result;
            *calc = _calc_crc32(crc, conf, data, length);
            break;
        }
        case CALC_CRC_TYPE_64BIT: // --- 64-bit calculator
        {
            calc_crc_64bit_t *conf = (calc_crc_64bit_t *)crc->conf;
            uint64_t *calc = (uint64_t *)result;
            *calc = _calc_crc64(crc, conf, data, length);
            break;
        }
        default: // -------------------- Default exit (should not come to here)
        {
            break;
        }
    }

    return CALC_CRC_STATUS_OK;
}

calc_crc_status_e CALC_CRC_Update(calc_crc_t *crc, const void *data, size_t length)
{
    CHECK_ARGS_NULL_PTR(crc, CALC_CRC_STATUS_ERROR_INPUT_ARGS);
    CHECK_ARGS_NULL_PTR(data, CALC_CRC_STATUS_ERROR_INPUT_ARGS);
    CHECK_ARGS_SIZE(length, 0, CALC_CRC_STATUS_ERROR_INPUT_ARGS);

    if (CALC_CRC_TYPE_MAX <= crc->type)
    {
        return CALC_CRC_STATUS_ERROR_INVALID_TYPE;
    }

    if (false == crc->update_in_progress)
    {
        crc->update_crc = (uint64_t)0u;
        crc->update_chunk = (size_t)0u;
        crc->update_in_progress = true;
    }

    uint64_t output = 0;
    calc_crc_status_e result = CALC_CRC_Calculate(crc, data, length, &output);

    if (CALC_CRC_STATUS_OK != result)
    {
        crc->update_in_progress = false;
    }

    return result;
}

calc_crc_status_e CALC_CRC_Finalize(calc_crc_t *crc, void *result)
{
    CHECK_ARGS_NULL_PTR(crc, CALC_CRC_STATUS_ERROR_INPUT_ARGS);
    CHECK_ARGS_NULL_PTR(result, CALC_CRC_STATUS_ERROR_INPUT_ARGS);

    if (false == crc->update_in_progress)
    {
        return CALC_CRC_STATUS_ERROR_UPDATE_NOT_STARTED;
    }

    switch (crc->type)
    {
        case CALC_CRC_TYPE_8BIT: // ---- 8-bit calculator
        {
            uint8_t *output = (uint8_t *)result;
            *output = (uint8_t)crc->update_crc_final;
            break;
        }
        case CALC_CRC_TYPE_16BIT: // --- 16-bit calculator
        {
            uint16_t *output = (uint16_t *)result;
            *output = (uint16_t)crc->update_crc_final;
            break;
        }
        case CALC_CRC_TYPE_32BIT: // --- 32-bit calculator
        {
            uint32_t *output = (uint32_t *)result;
            *output = (uint32_t)crc->update_crc_final;
            break;
        }
        case CALC_CRC_TYPE_64BIT: // --- 64-bit calculator
        {
            uint64_t *output = (uint64_t *)result;
            *output = (uint64_t)crc->update_crc_final;
            break;
        }
        default: // -------------------- Default exit (should not come to here)
        {
            break;
        }
    }

    crc->update_in_progress = false;

    return CALC_CRC_STATUS_OK;
}

// --- Private Functions Definitions -----------------------------------------------------------------------------------

static void _calc_table_crc8(uint8_t *table, uint8_t polynomial)
{
    for (size_t dividend = 0; dividend < 256; dividend++)
    {
        uint8_t cbyte = (uint8_t)dividend;

        for (uint8_t bit = 0; bit < 8; bit++)
        {
            if ((cbyte & 0x80) != 0)
            {
                cbyte <<= 1;
                cbyte ^= polynomial;
            }
            else
            {
                cbyte <<= 1;
            }
        }

        table[dividend] = cbyte;
    }
}

static void _calc_table_crc16(uint16_t *table, uint16_t polynomial)
{
    for (size_t dividend = 0; dividend < 256; dividend++)
    {
        uint16_t cbyte = (uint16_t)(dividend << 8);

        for (uint8_t bit = 0; bit < 8; bit++)
        {
            if ((cbyte & 0x8000) != 0)
            {
                cbyte <<= 1;
                cbyte ^= polynomial;
            }
            else
            {
                cbyte <<= 1;
            }
        }

        table[dividend] = cbyte;
    }
}

static void _calc_table_crc32(uint32_t *table, uint32_t polynomial)
{
    for (size_t dividend = 0; dividend < 256; dividend++)
    {
        uint32_t cbyte = (uint32_t)(dividend << 24);

        for (uint8_t bit = 0; bit < 8; bit++)
        {
            if ((cbyte & 0x80000000) != 0)
            {
                cbyte <<= 1;
                cbyte ^= polynomial;
            }
            else
            {
                cbyte <<= 1;
            }
        }

        table[dividend] = cbyte;
    }
}

static void _calc_table_crc64(uint64_t *table, uint64_t polynomial)
{
    for (size_t dividend = 0; dividend < 256; dividend++)
    {
        uint64_t cbyte = (uint64_t)(dividend << 56);

        for (uint8_t bit = 0; bit < 8; bit++)
        {
            if ((cbyte & 0x8000000000000000) != 0)
            {
                cbyte <<= 1;
                cbyte ^= polynomial;
            }
            else
            {
                cbyte <<= 1;
            }
        }

        table[dividend] = cbyte;
    }
}

static uint8_t _calc_crc8(calc_crc_t *crc, calc_crc_8bit_t *conf, const uint8_t *data, size_t length)
{
    uint8_t result = conf->initial_value;

    if (true == crc->update_in_progress)
    {
        if (0 != crc->update_chunk)
        {
            result = (uint8_t)crc->update_crc;
        }
        crc->update_chunk++;
    }

    for (size_t i = 0; i < length; i++)
    {
        uint8_t byte = conf->input_reflected ? _reflect_crc8(data[i]) : data[i];
        result = conf->table[result ^ byte];
    }

    UPDATE_CRC();

    result = result ^ conf->final_value;

    if (conf->output_reflected)
    {
        result = _reflect_crc8(result);
    }

    UPDATE_FINAL();

    return result;
}

static uint16_t _calc_crc16(calc_crc_t *crc, calc_crc_16bit_t *conf, const uint8_t *data, size_t length)
{
    uint16_t result = conf->initial_value;

    if (true == crc->update_in_progress)
    {
        if (0 != crc->update_chunk)
        {
            result = (uint16_t)crc->update_crc;
        }
        crc->update_chunk++;
    }

    for (size_t i = 0; i < length; i++)
    {
        uint8_t byte = conf->input_reflected ? _reflect_crc8(data[i]) : data[i];
        uint8_t pos = (uint8_t)((result >> 8) ^ byte);
        result = (uint16_t)(result << 8) ^ conf->table[pos];
    }

    UPDATE_CRC();

    result = result ^ conf->final_value;

    if (conf->output_reflected)
    {
        result = _reflect_crc16(result);
    }

    UPDATE_FINAL();

    return result;
}

static uint32_t _calc_crc32(calc_crc_t *crc, calc_crc_32bit_t *conf, const uint8_t *data, size_t length)
{
    uint32_t result = conf->initial_value;

    if (true == crc->update_in_progress)
    {
        if (0 != crc->update_chunk)
        {
            result = (uint32_t)crc->update_crc;
        }
        crc->update_chunk++;
    }

    for (size_t i = 0; i < length; i++)
    {
        uint8_t byte = conf->input_reflected ? _reflect_crc8(data[i]) : data[i];
        uint8_t pos = (uint8_t)((result ^ ((uint32_t)byte << 24)) >> 24);
        result = (result << 8) ^ conf->table[pos];
    }

    UPDATE_CRC();

    result = result ^ conf->final_value;

    if (conf->output_reflected)
    {
        result = _reflect_crc32(result);
    }

    UPDATE_FINAL();

    return result;
}

static uint64_t _calc_crc64(calc_crc_t *crc, calc_crc_64bit_t *conf, const uint8_t *data, size_t length)
{
    uint64_t result = conf->initial_value;

    if (true == crc->update_in_progress)
    {
        if (0 != crc->update_chunk)
        {
            result = (uint64_t)crc->update_crc;
        }
        crc->update_chunk++;
    }

    for (size_t i = 0; i < length; i++)
    {
        uint8_t byte = conf->input_reflected ? _reflect_crc8(data[i]) : data[i];
        uint8_t pos = (uint8_t)((result ^ ((uint64_t)byte << 56)) >> 56);
        result = (uint64_t)(result << 8) ^ conf->table[pos];
    }

    UPDATE_CRC();

    result = result ^ conf->final_value;

    if (conf->output_reflected)
    {
        result = _reflect_crc64(result);
    }

    UPDATE_FINAL();

    return result;
}

static uint8_t _reflect_crc8(uint8_t data)
{
    uint8_t reflection = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        if (data & (1 << i))
            reflection |= (1 << (7 - i));
    }
    return reflection;
}

static uint16_t _reflect_crc16(uint16_t data)
{
    uint16_t reflection = 0;
    for (uint8_t i = 0; i < 16; i++)
    {
        if (data & (1 << i))
            reflection |= (1 << (15 - i));
    }
    return reflection;
}

static uint32_t _reflect_crc32(uint32_t data)
{
    uint32_t reflection = 0;
    for (uint8_t i = 0; i < 32; i++)
    {
        if (data & (1U << i))
            reflection |= (1U << (31 - i));
    }
    return reflection;
}

static uint64_t _reflect_crc64(uint64_t data)
{
    uint64_t reflection = 0;
    for (uint8_t i = 0; i < 64; i++)
    {
        if (data & (1ULL << i))
            reflection |= (1ULL << (63 - i));
    }
    return reflection;
}

// --- EOF -------------------------------------------------------------------------------------------------------------
