/*
 * Generated with the FPGA Interface C API Generator 12.0.0
 * for NI-RIO 12.0.0 or later.
 */

#ifndef __NiFpga_Math_Pid_h__
#define __NiFpga_Math_Pid_h__

#ifndef NiFpga_Version
   #define NiFpga_Version 1200
#endif

#include "NiFpga.h"

/**
 * The filename of the FPGA bitfile.
 *
 * This is a #define to allow for string literal concatenation. For example:
 *
 *    static const char* const Bitfile = "C:\\" NiFpga_Math_Pid_Bitfile;
 */
#define NiFpga_Math_Pid_Bitfile "NiFpga_Math_Pid.lvbitx"

/**
 * The signature of the FPGA bitfile.
 */
static const char* const NiFpga_Math_Pid_Signature = "009AF097469E74A7DEAAE20B2ACB2E99";
// Uses DIO0 and DIO1 for encoder, PWM on DIO2 and direction bit DIO3
typedef enum
{
   NiFpga_RealError = 0x8114,
} NiFpga_Math_Pid_IndicatorI32;

typedef enum
{
   NiFpga_Error = 0x810C,
} NiFpga_Math_Pid_IndicatorU32;

typedef enum
{
   NiFpga_Encoder_Reset = 0x811A,
} NiFpga_Math_Pid_ControlBool;

typedef enum
{
   NiFpga_Accuracy = 0x8110,
   NiFpga_Desired = 0x811C,
   NiFpga_Kd = 0x8120,
   NiFpga_Ki = 0x8128,
   NiFpga_Kp = 0x8124,
} NiFpga_Math_Pid_ControlI32;

#endif
