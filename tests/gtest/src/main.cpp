/***********************************************************************************************************************
 *
 * @file        main.cpp
 * @brief       Testing platform start-up file to test CALC-CRC component with googletest.
 * @author      Blaz Baskovc
 * @copyright   Copyright 2025 Blaz Baskovc
 * @date        2025-03-11
 *
 **********************************************************************************************************************/

// --- Includes --------------------------------------------------------------------------------------------------------

#include <stdint.h>
#include <gtest/gtest.h>

// --- Application Start-Up function -----------------------------------------------------------------------------------

int32_t main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

// --- EOF -------------------------------------------------------------------------------------------------------------
