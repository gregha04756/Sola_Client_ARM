/*
 * Sola_Defs_Consts.c
 *
 *  Created on: Nov. 25, 2019
 *      Author: greg
 */

#include "Sola_Defs_Consts.h"

const uint16_t UT_BITS_NB = 0x2B;
const uint8_t ui8_MAX_SLAVE_ID = 0xF7;
const char *Local_Host_IP = "127.0.0.1";
const uint16_t ui16_Alerts_Reg_Cnt = 90;
const uint16_t ui16_Alerts_Base_Addr = 1120;
const uint16_t ui16_Lockouts_Base_Addr = 864;
const uint16_t ui16_Lockouts_Blk_Reg_Cnt = 51;
const uint16_t ui16_Lockouts_Blk_Cnt = 5;
const uint8_t g_unit_id = 1;
const int ui16_bit_count = 8*sizeof(uint16_t);

/* Special codes or values to indicate sensor status */
const uint16_t UNCONFIGUREDSENSOR1 = 0x7FFF;
const uint16_t UNCONFIGUREDSENSOR2 = 0x8200;
const uint16_t UNCONFIGUREDTEMP = 0x8FFF;
const uint16_t SHORTEDSENSOR = 0x8000;
const uint16_t OPENSENSOR = 0x8100;
const uint16_t OUTSIDEHIGHRANGE = 0x8300;
const uint16_t OUTSIDELOWRANGE = 0x8400;
const uint16_t UNRELIABLESENSOR = 0x8500;
