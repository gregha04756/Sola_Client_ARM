/*
 * Check_Configuration_Change.c
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
#include <glib/gprintf.h>

#include "modbus.h"
#include "Reg_Groups.h"

extern long read_reg_group(modbus_t * ctx,const SOLAREGGROUP_T * lp_group);
extern volatile uint8_t g_connected_unit_ID;
extern uint16_t Sola_Data[];
extern volatile int die;
extern pthread_mutex_t poll_mutex;

bool Check_Configuration_Change(modbus_t * ctx)
{
	bool b_Config_Change = false;
	bool b_r = false;
	int i_x;
	int i_r;
	long l_r;
	uint16_t usBit = 0;
	uint16_t ui16_mask = 0;

	/* Check if there's a configuration update. */
	/* System ID and Access has to be handled separately because of string */
	/* values. */
	b_Config_Change = false;
	usBit = 1;
#if defined(_DEBUG)
		i_r = g_printf("Configuration change check Sola_Data[0][1]=0x%04x 0x%04x\n",Sola_Data[0], Sola_Data[1]);
#endif
	for ( i_x = 0; i_x < ui16_bit_count; ++i_x )
	{
		ui16_mask = usBit & Sola_Data[1];
		switch (ui16_mask)
		{
		case 0x0001:
			l_r = read_reg_group(ctx,&System_Configuration_Group);
			l_r = read_reg_group(ctx,&System_Configuration_Product_type_Group);
			l_r = read_reg_group(ctx,&System_Configuration_Build_Group);
			l_r = read_reg_group(ctx,&Burner_name_Group);
			l_r = read_reg_group(ctx,&Installation_data_Group);
			l_r = read_reg_group(ctx,&OEM_ID_Group);
			l_r = read_reg_group(ctx,&OS_number_Group);
			l_r = read_reg_group(ctx,&Date_code_Group);
			break;
		case 0x0002:
			break;
		case 0x0004:
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

	return b_Config_Change;
}
