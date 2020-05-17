/*
 * Check_Status_Change.c
 *
 *  Created on: Dec. 2, 2019
 *      Author: greg
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <math.h>
#include <ctype.h>

#include "modbus.h"
#include "Reg_Groups.h"

extern long read_reg_group(modbus_t * ctx,const SOLAREGGROUP_T * lp_group);
extern volatile uint8_t g_connected_unit_ID;
extern uint16_t Sola_Data[];
extern volatile int die;
extern pthread_mutex_t poll_mutex;

bool Check_Status_Change(modbus_t * ctx)
{
	bool b_r = false;
	bool b_Status_Change = false;
	int i;
	long l_r;
	uint16_t usBit = 0;
	uint16_t ui16_mask = 0;


	/* Check if there's a status update */
				b_Status_Change = false;
				usBit = 1;
				for ( i = 0; i < ui16_bit_count; i++ )
				{
					ui16_mask = usBit & Sola_Data[0];
					switch (ui16_mask)
					{
					case 0x0001:
						l_r = read_reg_group(ctx,&Burner_Control_Status_Group);
						break;
					case 0x0002:
						l_r = read_reg_group(ctx,&Burner_Control_Status_Group);
						break;
					case 0x0004:
						l_r = read_reg_group(ctx,&Sensor_Status_Group);
						break;
					case 0x0008:
						break;
					case 0x0010:
						break;
					case 0x0020:
						break;
					case 0x0040:
						break;
					case 0x0080:
						break;
					case 0x0100:
						break;
					case 0x0200:
						break;
					case 0x0400:
						break;
					case 0x0800:
						break;
					case 0x1000:
						break;
					case 0x2000:
						break;
					case 0x4000:
						break;
					case 0x8000:
						break;
					default:
						break;
					}
					usBit <<= 1;
				}


	return b_Status_Change;
}
