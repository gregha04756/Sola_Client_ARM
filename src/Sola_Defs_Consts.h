/*
 * Sola_Defs_Consts.h
 *
 *  Created on: Nov. 25, 2019
 *      Author: greg
 */

#ifndef SOLA_DEFS_CONSTS_H_
#define SOLA_DEFS_CONSTS_H_

#include <stdint.h>


#define Sola_Register_Count 1370
#define ZERO 0
#define CELSIUSUNITS 1
#define FAHRENHEITUNITS 0



extern const uint16_t UT_BITS_NB;
extern const uint8_t ui8_MAX_SLAVE_ID;
extern const char *Local_Host_IP;
extern const uint16_t ui16_Alerts_Reg_Cnt;
extern const uint16_t ui16_Alerts_Base_Addr;
extern const uint16_t ui16_Lockouts_Base_Addr;
extern const uint16_t ui16_Lockouts_Blk_Reg_Cnt;
extern const uint16_t ui16_Lockouts_Blk_Cnt;
extern const uint8_t g_unit_id;
extern const int ui16_bit_count;

extern const uint16_t UNCONFIGUREDSENSOR1;
extern const uint16_t UNCONFIGUREDSENSOR2;
extern const uint16_t UNCONFIGUREDTEMP;
extern const uint16_t SHORTEDSENSOR;
extern const uint16_t OPENSENSOR;
extern const uint16_t OUTSIDEHIGHRANGE;
extern const uint16_t OUTSIDELOWRANGE;
extern const uint16_t UNRELIABLESENSOR;



#endif /* SOLA_DEFS_CONSTS_H_ */
