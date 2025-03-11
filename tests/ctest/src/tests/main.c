/***********************************************************************************************************************
 *
 * @file        main.c
 * @brief       Testing platform start-up file to test CALC-CRC component.
 * @author      Blaz Baskovc
 * @copyright   Copyright 2025 Blaz Baskovc
 * @date        2025-03-01
 *
 **********************************************************************************************************************/

// --- Includes --------------------------------------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "calc_crc/calc_crc.h"
#include "calc_crc/calc_crc_gtypes.h"
#include "calc_crc/calc_crc_ptypes.h"

// --- Private Defines -------------------------------------------------------------------------------------------------

/**
 * @brief   Add all tests to run to the list (define it before enable and include of ctest).
 */
#define TESTS                                                                                                          \
    ADD(calc_crc_init_null_handle)                                                                                     \
    ADD(calc_crc_init_valid)                                                                                           \
    ADD(calc_crc_calculate_null_handle)                                                                                \
    ADD(calc_crc_calculate_8bit_valid)                                                                                 \
    ADD(calc_crc_calculate_16bit_valid)                                                                                \
    ADD(calc_crc_calculate_32bit_valid)                                                                                \
    ADD(calc_crc_calculate_64bit_valid)                                                                                \
    ADD(calc_crc_calculate_valid)                                                                                      \
    ADD(calc_crc_update_null_handle)                                                                                   \
    ADD(calc_crc_update_8bit_valid)                                                                                    \
    ADD(calc_crc_update_16bit_valid)                                                                                   \
    ADD(calc_crc_update_32bit_valid)                                                                                   \
    ADD(calc_crc_update_64bit_valid)                                                                                   \
    ADD(calc_crc_finalize_null_handle)                                                                                 \
    ADD(calc_crc_finalize_valid)

// --- CTest Configurations --------------------------------------------------------------------------------------------

/**
 * @brief   Enable ctest implementation.
 */
#define CTEST_IMPLEMENTATION

/**
 * @brief   Include ctest implementation
 */
#include "ctest/ctest.h"

// --- Application start-up --------------------------------------------------------------------------------------------

int32_t main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    // Disable stdout buffering (needed to print even if one character is in buffer)
    setvbuf(stdout, NULL, _IONBF, 0);

    // Run ctest tests
    return ctest__run_tests() ? EXIT_SUCCESS : EXIT_FAILURE;
}

// --- Private Functions Definitions -----------------------------------------------------------------------------------

static int32_t test_calc_crc_init_null_handle(void)
{
    int32_t failed_assertions = 0;

    calc_crc_status_e result;
    calc_crc_t crc;

    calc_crc_8bit_t conf = {
        .polynomial = CALC_CRC_8BIT_POLYNOMIAL,
        .initial_value = UINT8_MAX,
        .final_value = UINT8_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(NULL, &conf, CALC_CRC_TYPE_8BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_ERROR_INPUT_ARGS, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", NULL,
                  &conf, CALC_CRC_STATUS_OK, result);

    result = CALC_CRC_Init(&crc, NULL, CALC_CRC_TYPE_8BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_ERROR_INPUT_ARGS, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", NULL,
                  &conf, CALC_CRC_STATUS_ERROR_INPUT_ARGS, result);

    return failed_assertions;
}

static int32_t test_calc_crc_init_valid(void)
{
    int32_t failed_assertions = 0;

    calc_crc_status_e result;
    calc_crc_t crc;

    calc_crc_8bit_t conf = {
        .polynomial = CALC_CRC_8BIT_POLYNOMIAL,
        .initial_value = UINT8_MAX,
        .final_value = UINT8_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(&crc, &conf, CALC_CRC_TYPE_8BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", NULL, &conf,
                  CALC_CRC_STATUS_OK, result);
    ASSERT_EQ_MSG(false, crc.update_in_progress, "Expected %d, but got %d.", false, crc.update_in_progress);
    ASSERT_EQ_MSG(0, crc.update_chunk, "Expected %d, but got %d.", 0, crc.update_chunk);
    ASSERT_EQ_MSG(0, crc.update_crc, "Expected %d, but got %d.", 0, crc.update_crc);
    ASSERT_EQ_MSG(0, crc.update_crc_final, "Expected %d, but got %d.", 0, crc.update_crc_final);
    ASSERT_EQ_MSG(&conf, crc.conf, "Expected %d, but got %d.", &conf, crc.conf);

    return failed_assertions;
}

static int32_t test_calc_crc_calculate_null_handle(void)
{
    int32_t failed_assertions = 0;

    calc_crc_status_e result;
    calc_crc_t crc;
    uint32_t crc_result;
    uint8_t data[10] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
    };
    calc_crc_8bit_t conf = {
        .polynomial = CALC_CRC_8BIT_POLYNOMIAL,
        .initial_value = UINT8_MAX,
        .final_value = UINT8_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(&crc, &conf, CALC_CRC_TYPE_8BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", &crc, &conf,
                  CALC_CRC_STATUS_OK, result);

    // Test NULL CRC handle
    result = CALC_CRC_Calculate(NULL, data, sizeof(data), &crc_result);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_ERROR_INPUT_ARGS, result,
                  "CALC_CRC_Calculate(%p, %p, %zu, %p) -> Expected %d, but got %d.", NULL, data, sizeof(data),
                  &crc_result, CALC_CRC_STATUS_ERROR_INPUT_ARGS, result);

    // Test NULL data pointer
    result = CALC_CRC_Calculate(&crc, NULL, sizeof(data), &crc_result);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_ERROR_INPUT_ARGS, result,
                  "CALC_CRC_Calculate(%p, %p, %zu, %p) -> Expected %d, but got %d.", &crc, NULL, sizeof(data),
                  &crc_result, CALC_CRC_STATUS_ERROR_INPUT_ARGS, result);

    // Test NULL result pointer
    result = CALC_CRC_Calculate(&crc, data, sizeof(data), NULL);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_ERROR_INPUT_ARGS, result,
                  "CALC_CRC_Calculate(%p, %p, %zu, %p) -> Expected %d, but got %d.", &crc, data, sizeof(data), NULL,
                  CALC_CRC_STATUS_ERROR_INPUT_ARGS, result);

    return failed_assertions;
}

static int32_t test_calc_crc_calculate_valid(void)
{
    int32_t failed_assertions = 0;

    calc_crc_status_e result;
    uint8_t data[] = "123456789";
    uint16_t data_length = sizeof(data) - 1;
    calc_crc_t crc;
    uint8_t result_8bit;
    calc_crc_8bit_t conf_8bit = {
        .polynomial = CALC_CRC_8BIT_POLYNOMIAL,
        .initial_value = UINT8_MAX,
        .final_value = UINT8_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(&crc, &conf_8bit, CALC_CRC_TYPE_8BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", &crc, &conf_8bit,
                  CALC_CRC_STATUS_OK, result);

    result = CALC_CRC_Calculate(&crc, data, data_length, &result_8bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_8bit);
    ASSERT_EQ_MSG(0x4, result_8bit, "Expected %08X, but got %02X.", 0x4, result_8bit);

    uint16_t result_16bit;
    calc_crc_16bit_t conf_16bit = {
        .polynomial = CALC_CRC_16BIT_POLYNOMIAL,
        .initial_value = UINT16_MAX,
        .final_value = UINT16_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(&crc, &conf_16bit, CALC_CRC_TYPE_16BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", &crc, &conf_16bit,
                  CALC_CRC_STATUS_OK, result);

    result = CALC_CRC_Calculate(&crc, data, data_length, &result_16bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_16bit);
    ASSERT_EQ_MSG(0xD64E, result_16bit, "Expected %08X, but got %04X.", 0xD64E, result_16bit);

    uint32_t result_32bit;
    calc_crc_32bit_t conf_32bit = {
        .polynomial = CALC_CRC_32BIT_POLYNOMIAL,
        .initial_value = UINT32_MAX,
        .final_value = UINT32_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(&crc, &conf_32bit, CALC_CRC_TYPE_32BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", &crc, &conf_32bit,
                  CALC_CRC_STATUS_OK, result);

    result = CALC_CRC_Calculate(&crc, data, data_length, &result_32bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_32bit);
    ASSERT_EQ_MSG(0xFC891918, result_32bit, "Expected %08X, but got %08X.", 0xFC891918, result_32bit);

    uint64_t result_64bit;
    calc_crc_64bit_t conf_64bit = {
        .polynomial = CALC_CRC_64BIT_POLYNOMIAL,
        .initial_value = UINT64_MAX,
        .final_value = UINT64_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(&crc, &conf_64bit, CALC_CRC_TYPE_64BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", &crc, &conf_64bit,
                  CALC_CRC_STATUS_OK, result);

    result = CALC_CRC_Calculate(&crc, data, data_length, &result_64bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_64bit);
    ASSERT_EQ_MSG(0x62EC59E3F1A4F00A, result_64bit, "Expected %08X, but got %04X.", 0x62EC59E3F1A4F00A, result_64bit);

    return failed_assertions;
}

static int32_t test_calc_crc_calculate_8bit_valid(void)
{
    int32_t failed_assertions = 0;

    calc_crc_status_e result;
    calc_crc_t crc;
    uint8_t data[] = "123456789";
    uint16_t data_length = sizeof(data) - 1;

    uint8_t result_8bit;
    calc_crc_8bit_t conf_8bit = {
        .polynomial = CALC_CRC_8BIT_POLYNOMIAL,
        .initial_value = UINT8_MAX,
        .final_value = UINT8_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(&crc, &conf_8bit, CALC_CRC_TYPE_8BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", &crc, &conf_8bit,
                  CALC_CRC_STATUS_OK, result);

    result = CALC_CRC_Calculate(&crc, data, data_length, &result_8bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_8bit);
    ASSERT_EQ_MSG(0x4, result_8bit, "Expected %08X, but got %02X.", 0x4, result_8bit);

    conf_8bit.initial_value = 0;
    conf_8bit.final_value = 0;
    result = CALC_CRC_Calculate(&crc, data, data_length, &result_8bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_8bit);
    ASSERT_EQ_MSG(0xF4, result_8bit, "Expected %02X, but got %02X.", 0xF4, result_8bit);

    conf_8bit.input_reflected = true;
    conf_8bit.output_reflected = true;
    result = CALC_CRC_Calculate(&crc, data, data_length, &result_8bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_8bit);
    ASSERT_EQ_MSG(0x20, result_8bit, "Expected %02X, but got %02X.", 0x20, result_8bit);

    conf_8bit.input_reflected = false;
    conf_8bit.output_reflected = true;
    result = CALC_CRC_Calculate(&crc, data, data_length, &result_8bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_8bit);
    ASSERT_EQ_MSG(0x2F, result_8bit, "Expected %02X, but got %02X.", 0x2F, result_8bit);

    return failed_assertions;
}

static int32_t test_calc_crc_calculate_16bit_valid(void)
{
    int32_t failed_assertions = 0;

    calc_crc_status_e result;
    calc_crc_t crc;
    uint8_t data[] = "123456789";
    uint16_t data_length = sizeof(data) - 1;

    uint16_t result_16bit;
    calc_crc_16bit_t conf_16bit = {
        .polynomial = CALC_CRC_16BIT_POLYNOMIAL,
        .initial_value = UINT16_MAX,
        .final_value = UINT16_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(&crc, &conf_16bit, CALC_CRC_TYPE_16BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", &crc, &conf_16bit,
                  CALC_CRC_STATUS_OK, result);

    result = CALC_CRC_Calculate(&crc, data, data_length, &result_16bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_16bit);
    ASSERT_EQ_MSG(0xD64E, result_16bit, "Expected %08X, but got %04X.", 0xD64E, result_16bit);

    conf_16bit.initial_value = 0;
    conf_16bit.final_value = 0;
    result = CALC_CRC_Calculate(&crc, data, data_length, &result_16bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_16bit);
    ASSERT_EQ_MSG(0x31C3, result_16bit, "Expected %08X, but got %04X.", 0x31C3, result_16bit);

    conf_16bit.input_reflected = true;
    conf_16bit.output_reflected = true;
    result = CALC_CRC_Calculate(&crc, data, data_length, &result_16bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_16bit);
    ASSERT_EQ_MSG(0x2189, result_16bit, "Expected %08X, but got %04X.", 0x2189, result_16bit);

    conf_16bit.input_reflected = false;
    conf_16bit.output_reflected = true;
    result = CALC_CRC_Calculate(&crc, data, data_length, &result_16bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_16bit);
    ASSERT_EQ_MSG(0xC38C, result_16bit, "Expected %08X, but got %04X.", 0xC38C, result_16bit);

    return failed_assertions;
}

static int32_t test_calc_crc_calculate_32bit_valid(void)
{
    int32_t failed_assertions = 0;

    calc_crc_status_e result;
    calc_crc_t crc;
    uint8_t data[] = "123456789";
    uint16_t data_length = sizeof(data) - 1;

    uint32_t result_32bit;
    calc_crc_32bit_t conf_32bit = {
        .polynomial = CALC_CRC_32BIT_POLYNOMIAL,
        .initial_value = UINT32_MAX,
        .final_value = UINT32_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(&crc, &conf_32bit, CALC_CRC_TYPE_32BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", &crc, &conf_32bit,
                  CALC_CRC_STATUS_OK, result);

    result = CALC_CRC_Calculate(&crc, data, data_length, &result_32bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_32bit);
    ASSERT_EQ_MSG(0xFC891918, result_32bit, "Expected %08X, but got %08X.", 0xFC891918, result_32bit);

    conf_32bit.initial_value = 0;
    conf_32bit.final_value = 0;
    result = CALC_CRC_Calculate(&crc, data, data_length, &result_32bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_32bit);
    ASSERT_EQ_MSG(0x89A1897F, result_32bit, "Expected %08X, but got %08X.", 0x89A1897F, result_32bit);

    conf_32bit.input_reflected = true;
    conf_32bit.output_reflected = true;
    result = CALC_CRC_Calculate(&crc, data, data_length, &result_32bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_32bit);
    ASSERT_EQ_MSG(0x2DFD2D88, result_32bit, "Expected %08X, but got %08X.", 0x2DFD2D88, result_32bit);

    conf_32bit.input_reflected = false;
    conf_32bit.output_reflected = true;
    result = CALC_CRC_Calculate(&crc, data, data_length, &result_32bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_32bit);
    ASSERT_EQ_MSG(0xFE918591, result_32bit, "Expected %08X, but got %08X.", 0xFE918591, result_32bit);

    return failed_assertions;
}

static int32_t test_calc_crc_calculate_64bit_valid(void)
{
    int32_t failed_assertions = 0;

    calc_crc_status_e result;
    calc_crc_t crc;
    uint8_t data[] = "123456789";
    uint16_t data_length = sizeof(data) - 1;

    uint64_t result_64bit;
    calc_crc_64bit_t conf_64bit = {
        .polynomial = CALC_CRC_64BIT_POLYNOMIAL,
        .initial_value = UINT64_MAX,
        .final_value = UINT64_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(&crc, &conf_64bit, CALC_CRC_TYPE_64BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", &crc, &conf_64bit,
                  CALC_CRC_STATUS_OK, result);

    result = CALC_CRC_Calculate(&crc, data, data_length, &result_64bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_64bit);
    ASSERT_EQ_MSG(0x62EC59E3F1A4F00A, result_64bit, "Expected %08X, but got %04X.", 0x62EC59E3F1A4F00A, result_64bit);

    conf_64bit.initial_value = 0;
    conf_64bit.final_value = 0;
    result = CALC_CRC_Calculate(&crc, data, data_length, &result_64bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_64bit);
    ASSERT_EQ_MSG(0x6C40DF5F0B497347, result_64bit, "Expected %08X, but got %04X.", 0x6C40DF5F0B497347, result_64bit);

    conf_64bit.input_reflected = true;
    conf_64bit.output_reflected = true;
    result = CALC_CRC_Calculate(&crc, data, data_length, &result_64bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_64bit);
    ASSERT_EQ_MSG(0x2B9C7EE4E2780C8A, result_64bit, "Expected %08X, but got %04X.", 0x2B9C7EE4E2780C8A, result_64bit);

    conf_64bit.input_reflected = false;
    conf_64bit.output_reflected = true;
    result = CALC_CRC_Calculate(&crc, data, data_length, &result_64bit);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result_64bit);
    ASSERT_EQ_MSG(0xE2CE92D0FAFB0236, result_64bit, "Expected %08X, but got %04X.", 0xE2CE92D0FAFB0236, result_64bit);

    return failed_assertions;
}

static int32_t test_calc_crc_update_8bit_valid(void)
{
    int32_t failed_assertions = 0;

    calc_crc_status_e result;
    calc_crc_t crc;
    uint8_t data[] = "123456789";
    uint16_t data_length = sizeof(data) - 1;

    uint8_t output;
    calc_crc_8bit_t conf = {
        .polynomial = CALC_CRC_8BIT_POLYNOMIAL,
        .initial_value = UINT8_MAX,
        .final_value = UINT8_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(&crc, &conf, CALC_CRC_TYPE_8BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", &crc, &conf,
                  CALC_CRC_STATUS_OK, result);
    ASSERT_EQ_MSG(false, crc.update_in_progress, "Expected %d, but got %d.", false, crc.update_in_progress);
    ASSERT_EQ_MSG(0, crc.update_chunk, "Expected %d, but got %d.", 0, crc.update_chunk);
    ASSERT_EQ_MSG(0, crc.update_crc, "Expected %d, but got %d.", 0, crc.update_crc);
    ASSERT_EQ_MSG(0, crc.update_crc_final, "Expected %d, but got %d.", 0, crc.update_crc_final);
    ASSERT_EQ_MSG(&conf, crc.conf, "Expected %d, but got %d.", &conf, crc.conf);

    result = CALC_CRC_Calculate(&crc, data, data_length, &output);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result);
    ASSERT_EQ_MSG(0x4, output, "Expected %02X, but got %02X.", 0x4, output);
    ASSERT_EQ_MSG(0, crc.update_chunk, "Expected %d, but got %d.", 0, crc.update_chunk);
    ASSERT_EQ_MSG(false, crc.update_in_progress, "Expected %d, but got %d.", false, crc.update_in_progress);
    ASSERT_EQ_MSG(&conf, crc.conf, "Expected %d, but got %d.", &conf, crc.conf);

    result = CALC_CRC_Update(&crc, data, data_length - 4);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Update(%p, %p, %d) -> Expected %d, but got %d.", &crc, data,
                  data_length);
    ASSERT_EQ_MSG(true, crc.update_in_progress, "Expected %d, but got %d.", true, crc.update_in_progress);
    ASSERT_EQ_MSG(1, crc.update_chunk, "Expected %d, but got %d.", 1, crc.update_chunk);
    ASSERT_EQ_MSG(&conf, crc.conf, "Expected %d, but got %d.", &conf, crc.conf);

    result = CALC_CRC_Update(&crc, data + (data_length - 4), 4);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Update(%p, %p, %d) -> Expected %d, but got %d.", &crc, data,
                  data_length);
    ASSERT_EQ_MSG(2, crc.update_chunk, "Expected %d, but got %d.", 2, crc.update_chunk);
    ASSERT_EQ_MSG(&conf, crc.conf, "Expected %d, but got %d.", &conf, crc.conf);

    result = CALC_CRC_Finalize(&crc, &output);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Finalize(%p, %p) -> Expected %d, but got %d.", &crc, result);
    ASSERT_EQ_MSG(false, crc.update_in_progress, "Expected %d, but got %d.", false, crc.update_in_progress);
    ASSERT_EQ_MSG(0x4, output, "Expected %02X, but got %02X.", 0x4, output);
    ASSERT_EQ_MSG(2, crc.update_chunk, "Expected %d, but got %d.", 2, crc.update_chunk);
    ASSERT_EQ_MSG(&conf, crc.conf, "Expected %d, but got %d.", &conf, crc.conf);

    return failed_assertions;
}

static int32_t test_calc_crc_update_16bit_valid(void)
{
    int32_t failed_assertions = 0;

    calc_crc_status_e result;
    calc_crc_t crc;
    uint8_t data[] = "123456789";
    uint16_t data_length = sizeof(data) - 1;

    uint16_t output;
    calc_crc_16bit_t conf = {
        .polynomial = CALC_CRC_16BIT_POLYNOMIAL,
        .initial_value = UINT16_MAX,
        .final_value = UINT16_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(&crc, &conf, CALC_CRC_TYPE_16BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", &crc, &conf,
                  CALC_CRC_STATUS_OK, result);

    result = CALC_CRC_Calculate(&crc, data, data_length, &output);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result);
    ASSERT_EQ_MSG(0xD64E, output, "Expected %04X, but got %04X.", 0xD64E, output);

    result = CALC_CRC_Update(&crc, data, data_length - 4);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Update(%p, %p, %d) -> Expected %d, but got %d.", &crc, data,
                  data_length);

    result = CALC_CRC_Update(&crc, data + (data_length - 4), 4);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Update(%p, %p, %d) -> Expected %d, but got %d.", &crc, data,
                  data_length);

    result = CALC_CRC_Finalize(&crc, &output);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Finalize(%p, %p) -> Expected %d, but got %d.", &crc, result);
    ASSERT_EQ_MSG(0xD64E, output, "Expected %04X, but got %04X.", 0xD64E, output);

    return failed_assertions;
}

static int32_t test_calc_crc_update_32bit_valid(void)
{
    int32_t failed_assertions = 0;

    calc_crc_status_e result;
    calc_crc_t crc;
    uint8_t data[] = "123456789";
    uint16_t data_length = sizeof(data) - 1;

    uint32_t output;
    calc_crc_32bit_t conf = {
        .polynomial = CALC_CRC_32BIT_POLYNOMIAL,
        .initial_value = UINT32_MAX,
        .final_value = UINT32_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(&crc, &conf, CALC_CRC_TYPE_32BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", &crc, &conf,
                  CALC_CRC_STATUS_OK, result);

    result = CALC_CRC_Calculate(&crc, data, data_length, &output);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result);
    ASSERT_EQ_MSG(0xFC891918, output, "Expected %08X, but got %08X.", 0xFC891918, output);

    result = CALC_CRC_Update(&crc, data, data_length - 4);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Update(%p, %p, %d) -> Expected %d, but got %d.", &crc, data,
                  data_length);

    result = CALC_CRC_Update(&crc, data + (data_length - 4), 4);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Update(%p, %p, %d) -> Expected %d, but got %d.", &crc, data,
                  data_length);

    result = CALC_CRC_Finalize(&crc, &output);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Finalize(%p, %p) -> Expected %d, but got %d.", &crc, result);
    ASSERT_EQ_MSG(0xFC891918, output, "Expected %08X, but got %08X.", 0xFC891918, output);

    return failed_assertions;
}

static int32_t test_calc_crc_update_64bit_valid(void)
{
    int32_t failed_assertions = 0;

    calc_crc_status_e result;
    calc_crc_t crc;
    uint8_t data[] = "123456789";
    uint16_t data_length = sizeof(data) - 1;

    uint64_t output;
    calc_crc_64bit_t conf = {
        .polynomial = CALC_CRC_64BIT_POLYNOMIAL,
        .initial_value = UINT64_MAX,
        .final_value = UINT64_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(&crc, &conf, CALC_CRC_TYPE_64BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", &crc, &conf,
                  CALC_CRC_STATUS_OK, result);

    result = CALC_CRC_Calculate(&crc, data, data_length, &output);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result);
    ASSERT_EQ_MSG(0x62EC59E3F1A4F00A, output, "Expected %013X, but got %016X.", 0x62EC59E3F1A4F00A, output);

    result = CALC_CRC_Update(&crc, data, data_length - 4);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Update(%p, %p, %d) -> Expected %d, but got %d.", &crc, data,
                  data_length);

    result = CALC_CRC_Update(&crc, data + (data_length - 4), 4);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Update(%p, %p, %d) -> Expected %d, but got %d.", &crc, data,
                  data_length);

    result = CALC_CRC_Finalize(&crc, &output);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Finalize(%p, %p) -> Expected %d, but got %d.", &crc, result);
    ASSERT_EQ_MSG(0x62EC59E3F1A4F00A, output, "Expected %016X, but got %016X.", 0x62EC59E3F1A4F00A, output);

    return failed_assertions;
}

static int32_t test_calc_crc_update_null_handle(void)
{
    int32_t failed_assertions = 0;

    calc_crc_status_e result;
    calc_crc_t crc;
    uint8_t data[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};

    // Test NULL CRC handle
    result = CALC_CRC_Update(NULL, data, sizeof(data));
    ASSERT_EQ_MSG(CALC_CRC_STATUS_ERROR_INPUT_ARGS, result, "CALC_CRC_Update(%p, %p, %zu) -> Expected %d, but got %d.",
                  NULL, data, sizeof(data), CALC_CRC_STATUS_ERROR_INPUT_ARGS, result);

    // Test NULL data pointer
    result = CALC_CRC_Update(&crc, NULL, sizeof(data));
    ASSERT_EQ_MSG(CALC_CRC_STATUS_ERROR_INPUT_ARGS, result, "CALC_CRC_Update(%p, %p, %zu) -> Expected %d, but got %d.",
                  &crc, NULL, sizeof(data), CALC_CRC_STATUS_ERROR_INPUT_ARGS, result);

    // Test zero-length data
    result = CALC_CRC_Update(&crc, data, 0);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_ERROR_INPUT_ARGS, result, "CALC_CRC_Update(%p, %p, %zu) -> Expected %d, but got %d.",
                  &crc, data, (size_t)0, CALC_CRC_STATUS_ERROR_INPUT_ARGS, result);

    return failed_assertions;
}

static int32_t test_calc_crc_finalize_null_handle(void)
{
    int32_t failed_assertions = 0;

    calc_crc_status_e result;
    calc_crc_t crc;
    uint32_t crc_result;

    // Test NULL CRC handle
    result = CALC_CRC_Finalize(NULL, &crc_result);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_ERROR_INPUT_ARGS, result, "CALC_CRC_Finalize(%p, %p) -> Expected %d, but got %d.",
                  NULL, &crc_result, CALC_CRC_STATUS_ERROR_INPUT_ARGS, result);

    // Test NULL result pointer
    result = CALC_CRC_Finalize(&crc, NULL);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_ERROR_INPUT_ARGS, result, "CALC_CRC_Finalize(%p, %p) -> Expected %d, but got %d.",
                  &crc, NULL, CALC_CRC_STATUS_ERROR_INPUT_ARGS, result);

    return failed_assertions;
}

static int32_t test_calc_crc_finalize_valid(void)
{
    int32_t failed_assertions = 0;

    calc_crc_status_e result;
    calc_crc_t crc;
    uint8_t data[] = "123456789";
    uint16_t data_length = sizeof(data) - 1;

    uint64_t output;
    calc_crc_64bit_t conf = {
        .polynomial = CALC_CRC_64BIT_POLYNOMIAL,
        .initial_value = UINT64_MAX,
        .final_value = UINT64_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };

    result = CALC_CRC_Init(&crc, &conf, CALC_CRC_TYPE_64BIT);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Init(%p, %p) -> Expected %d, but got %d.", &crc, &conf,
                  CALC_CRC_STATUS_OK, result);

    result = CALC_CRC_Calculate(&crc, data, data_length, &output);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Calculate(%p, %p, %d, %p) -> Expected %d, but got %d.", &crc,
                  data, data_length, result);
    ASSERT_EQ_MSG(0x62EC59E3F1A4F00A, output, "Expected %013X, but got %016X.", 0x62EC59E3F1A4F00A, output);

    result = CALC_CRC_Update(&crc, data, data_length - 4);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Update(%p, %p, %d) -> Expected %d, but got %d.", &crc, data,
                  data_length);

    result = CALC_CRC_Update(&crc, data + (data_length - 4), 4);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Update(%p, %p, %d) -> Expected %d, but got %d.", &crc, data,
                  data_length);

    result = CALC_CRC_Finalize(&crc, &output);
    ASSERT_EQ_MSG(CALC_CRC_STATUS_OK, result, "CALC_CRC_Finalize(%p, %p) -> Expected %d, but got %d.", &crc, result);
    ASSERT_EQ_MSG(0x62EC59E3F1A4F00A, output, "Expected %016X, but got %016X.", 0x62EC59E3F1A4F00A, output);

    return failed_assertions;
}

// --- EOF -------------------------------------------------------------------------------------------------------------
