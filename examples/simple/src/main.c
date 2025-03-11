// --- Includes --------------------------------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "calc_crc/calc_crc.h"

// --- Application Start-Up --------------------------------------------------------------------------------------------

int main(void)
{
    // Define a data buffer to be checked
    uint8_t data[] = "Hello, world!";
    uint8_t crc8_result;
    uint16_t crc16_result;
    uint32_t crc32_result;
    uint64_t crc64_result;

    // Create a CRC handle
    calc_crc_t crc;

    // Configure CRC-8
    calc_crc_8bit_t crc8_conf = {
        .polynomial = CALC_CRC_8BIT_POLYNOMIAL,
        .initial_value = 0xFF,
        .final_value = 0xFF,
        .input_reflected = false,
        .output_reflected = false,
    };

    // Initialize and calculate CRC-8
    CALC_CRC_Init(&crc, &crc8_conf, CALC_CRC_TYPE_8BIT);
    CALC_CRC_Calculate(&crc, data, strlen((char *)data), &crc8_result);
    printf("CRC-8:  0x%02X\n", crc8_result);

    // Configure CRC-16
    calc_crc_16bit_t crc16_conf = {
        .polynomial = CALC_CRC_16BIT_POLYNOMIAL,
        .initial_value = 0xFFFF,
        .final_value = 0xFFFF,
        .input_reflected = false,
        .output_reflected = false,
    };

    // Initialize and calculate CRC-16
    CALC_CRC_Init(&crc, &crc16_conf, CALC_CRC_TYPE_16BIT);
    CALC_CRC_Calculate(&crc, data, strlen((char *)data), &crc16_result);
    printf("CRC-16: 0x%04X\n", crc16_result);

    // Configure CRC-32
    calc_crc_32bit_t crc32_conf = {
        .polynomial = CALC_CRC_32BIT_POLYNOMIAL,
        .initial_value = 0xFFFFFFFF,
        .final_value = 0xFFFFFFFF,
        .input_reflected = false,
        .output_reflected = false,
    };

    // Initialize and calculate CRC-32
    CALC_CRC_Init(&crc, &crc32_conf, CALC_CRC_TYPE_32BIT);
    CALC_CRC_Calculate(&crc, data, strlen((char *)data), &crc32_result);
    printf("CRC-32: 0x%08X\n", crc32_result);

    // Configure CRC-64
    calc_crc_64bit_t crc64_conf = {
        .polynomial = CALC_CRC_64BIT_POLYNOMIAL,
        .initial_value = 0xFFFFFFFFFFFFFFFF,
        .final_value = 0xFFFFFFFFFFFFFFFF,
        .input_reflected = false,
        .output_reflected = false,
    };

    // Initialize and calculate CRC-64
    CALC_CRC_Init(&crc, &crc64_conf, CALC_CRC_TYPE_64BIT);
    CALC_CRC_Calculate(&crc, data, strlen((char *)data), &crc64_result);
    printf("CRC-64: 0x%08X%08X\n", (uint32_t)(crc64_result >> 32), (uint32_t)crc64_result);

    return 0;
}

// --- EOF -------------------------------------------------------------------------------------------------------------
