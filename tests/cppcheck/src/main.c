/***********************************************************************************************************************
 *
 * @file        main.c
 * @brief       Windows / Linux platform start-up file to test CALC-CRC component.
 * @author      Blaz Baskovc
 * @copyright   Copyright 2025 Blaž Basškovč
 * @date        2025-02-17
 *
 **********************************************************************************************************************/

// --- Includes --------------------------------------------------------------------------------------------------------

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// --- Application Start-Up function -----------------------------------------------------------------------------------

int32_t main(int32_t argc, uint8_t *argv[])
{
    (void)argc;
    (void)argv;

    // Disable stdout buffering (needed to print even if one character is in buffer)
    setvbuf(stdout, NULL, _IONBF, 0);

    // Return execute results
    return EXIT_SUCCESS;
}

// --- EOF -------------------------------------------------------------------------------------------------------------
