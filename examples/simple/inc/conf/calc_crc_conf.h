/***********************************************************************************************************************
 *
 * @file        calc_crc_conf.h
 * @brief       Component CALC-CRC configurations.
 * @author      Blaz Baskovc
 * @copyright   Copyright 2025 Blaz Baskovc
 * @date        2025-03-01
 *
 **********************************************************************************************************************/

#ifndef CALC_CRC_CONF_H
#define CALC_CRC_CONF_H

// C++ wrapper - Start
#ifdef __cplusplus
extern "C" {
#endif

// --- Data Logger Configurations --------------------------------------------------------------------------------------

#define CALC_CRC_CONF_FREERTOS_USE false           /// Set to true to enable thread-safety mechanisms.
#define CALC_CRC_CONF_TRACE_USE    true            /// Set to true to enable logging of buffer actions using TRACE.
#define CALC_CRC_CONF_TRACE_LEVEL  TRACE_LEVEL_VER /// Configure trace level (if tracing is used).

// C++ wrapper - End
#ifdef __cplusplus
}
#endif

#endif /* CALC_CRC_CONF_H */

// --- EOF -------------------------------------------------------------------------------------------------------------
