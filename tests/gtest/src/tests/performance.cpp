/***********************************************************************************************************************
 *
 * @file        performance.cpp
 * @brief       Test to for testing component performance with googletest.
 * @author      Blaz Baskovc
 * @copyright   Copyright 2025 Blaz Baskovc
 * @date        2025-03-11
 *
 **********************************************************************************************************************/

// --- Includes --------------------------------------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>
#include <gtest/gtest.h>

#include "calc_crc/calc_crc.h"

// --- Performance Tests -----------------------------------------------------------------------------------------------

TEST(PerformanceTest, InsertPerformance_1k)
{
    calc_crc_t crc;
    calc_crc_16bit_t conf = {
        .polynomial = CALC_CRC_16BIT_POLYNOMIAL,
        .initial_value = UINT16_MAX,
        .final_value = UINT16_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };
    uint16_t output;
    uint8_t data[1024];

    CALC_CRC_Init(&crc, &conf, CALC_CRC_TYPE_16BIT);

    auto start = std::chrono::high_resolution_clock::now();

    CALC_CRC_Calculate(&crc, data, sizeof(data), &output);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    ASSERT_LT(elapsed.count(), 1.0);
}

TEST(PerformanceTest, InsertPerformance_1M)
{
    calc_crc_t crc;
    calc_crc_16bit_t conf = {
        .polynomial = CALC_CRC_16BIT_POLYNOMIAL,
        .initial_value = UINT16_MAX,
        .final_value = UINT16_MAX,
        .input_reflected = false,
        .output_reflected = false,
    };
    uint16_t output;
    uint8_t data[1024 * 1024];

    CALC_CRC_Init(&crc, &conf, CALC_CRC_TYPE_16BIT);

    auto start = std::chrono::high_resolution_clock::now();

    CALC_CRC_Calculate(&crc, data, sizeof(data), &output);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    ASSERT_LT(elapsed.count(), 10.0);
}

// --- EOF -------------------------------------------------------------------------------------------------------------
