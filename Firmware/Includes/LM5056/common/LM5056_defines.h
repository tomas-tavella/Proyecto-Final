// Jorge Anderson LEICI $Revision: /main/1 $
// Checkin $Date: November 11, 2022   13:34:00 $
//###########################################################################
//
// FILE:	LM5056_defines.h
//
// TITLE:	LM5056 module Code Definitions.
//

//###########################################################################

#ifndef LM5056_DEFINES_H
#define LM5056_DEFINES_H

//
// Defines
//

#define LM5056_ADDR                 0x40     // see Table 42
/*****************************************/
/*                                       */
/*        Standard PMBus Commands        */
/*                                       */
/*****************************************/

#define CLEAR_FAULTS                0x03
#define CAPABILITY                  0x19
#define VOUT_UV_WARN_LIMIT          0x43
#define OT_FAULT_LIMIT              0x4F
#define OT_WARN_LIMIT               0x51
#define VIN_OV_WARN_LIMIT           0x57
#define VIN_UV_WARN_LIMIT           0x58
#define STATUS_BYTE                 0x78
#define STATUS_WORD                 0x79
#define STATUS_VOUT                 0x7A
#define STATUS_INPUT                0x7C
#define STATUS_TEMPERATURE          0x7D
#define STATUS_CML                  0x7E
#define STATUS_MFR_SPECIFIC         0x80
#define READ_VIN                    0x88
#define READ_VOUT                   0x8B
#define READ_TEMPERATURE_1          0x8D
#define MFR_ID                      0x99
#define MFR_MODEL                   0x9A
#define MFR_REVISION                0x9B

/*****************************************/
/*                                       */
/* Manufacturer Specific PMBus Commands  */
/*                                       */
/*****************************************/

#define MFR_READ_VAUX               0xD0
#define MFR_READ_IIN                0xD1
#define MFR_READ_PIN                0xD2
#define MFR_IIN_OC_WARN_LIMIT       0xD3
#define MFR_PIN_OP_WARN_LIMIT       0xD4
#define MFR_READ_PIN_PEAK           0xD5
#define MFR_CLEAR_PIN_PEAK          0xD6
#define MFR_ALERT_MASK              0xD8
#define MFR_DEVICE_SETUP            0xD9
#define MFR_BLOCK_READ              0xDA
#define MFR_SAMPLES_FOR_AVG         0xDB
#define MFR_READ_AVG_VIN            0xDC
#define MFR_READ_AVG_VOUT           0xDD
#define MFR_READ_AVG_IIN            0xDE
#define MFR_READ_AVG_PIN            0xDF
#define MFR_BLACK_BOX_READ          0xE0
#define MFR_DIAGNOSTIC_WORD_READ    0xE1
#define MFR_AVG_BLOCK_READ          0xE2

/*****************************************/
/*                                       */
/*       Conversion Coefficients         */
/*                                       */
/*****************************************/
#define CL              0      // CL = 0 => CL connected to GND

#define VIN_M           4612.0
#define VIN_B           -566.0
#define VIN_10_R        100.0

#define VIN_M_m         3859.41         // Calibración
#define VIN_B_m         4281.42         // Calibración

#define VOUT_M          4607.0
#define VOUT_B          179.0
#define VOUT_10_R       100.0

#define VAUX_M          13801.0
#define VAUX_B          11.0
#define VAUX_10_R       10.0

#if CL == 0
    #define IIN_M           7471.0
    #define IIN_B           1949.0
    #define IIN_10_R        100.0

    #define PIN_M           839.0
    #define PIN_B           9822.0
    #define PIN_10_R        1000.0
#else
    #define IIN_M           14985.0
    #define IIN_B           4271.0
    #define IIN_10_R        100.0

    #define PIN_M           1684.0
    #define PIN_B           22344.0
    #define PIN_10_R        1000.0
#endif

#define TEMPERATURE_M          1600.0
#define TEMPERATURE_B          0.0
#define TEMPERATURE_10_R       1000.0


struct LM5056_DIAGNOSTIC_WORD_BITS_msb {    // bits    description
    Uint16 not_support3:2;              // 8:9     Not supported, always 0
    Uint16 TEMPERATURE_OV:1;            // 10      Over-temperature warn
    Uint16 not_support4:1;              // 11      Not supported, always 1
    Uint16 VIN_OV:1;                    // 12      VIN over-voltage warn
    Uint16 VIN_UV:1;                    // 13      VIN under-votlage warn
    Uint16 CURRENT_POWER_OV:1;          // 14      Over-current warn or over-power warn
    Uint16 VOUT_UV:1;                   // 15      VOUT under-voltage warn
};


struct LM5056_DIAGNOSTIC_WORD_BITS_lsb {    // bits    description
    Uint16 not_support1:1;               // 0       Not supported, always 0
    Uint16 CML_FAULT:1;                 // 1       A communication fault has occurred
    Uint16 not_support2:5;              // 2:6     Not supported, always 0
    Uint16 CONFIG_PRESET:1;             // 7       Configuration preset, default 1
};

struct LM5056_DIAGNOSTIC_WORD_BITS {
    struct LM5056_DIAGNOSTIC_WORD_BITS_lsb lsb;
    struct LM5056_DIAGNOSTIC_WORD_BITS_msb msb;
};


struct LM5056_word
{
    Uint16 lsb;
    Uint16 msb;
};

union LM5056_DIAGNOSTIC_WORD
{
    struct LM5056_word                      all;
    struct LM5056_DIAGNOSTIC_WORD_BITS      bit;
};


struct LM5056_BLOCK_READ
{
    Uint16 byte_count;
    union LM5056_DIAGNOSTIC_WORD status;
    struct LM5056_word IIN;
    struct LM5056_word VOUT;
    struct LM5056_word VIN;
    struct LM5056_word PIN;
    struct LM5056_word TEMPERATURE;
};

struct LM5056_AVG_BLOCK_READ
{
    Uint16 byte_count;
    union LM5056_DIAGNOSTIC_WORD status;
    struct LM5056_word AVG_IIN;
    struct LM5056_word AVG_VOUT;
    struct LM5056_word AVG_VIN;
    struct LM5056_word AVG_PIN;
    struct LM5056_word TEMPERATURE;
};


#endif  // end of LM5056_DEFINES_H definition

//
// End of file
//

