/*
 * Screen_Summary_Page.h
 *
 *  Created on: Dec. 9, 2019
 *      Author: greg
 */

#ifndef SCREEN_SUMMARY_PAGE_H_
#define SCREEN_SUMMARY_PAGE_H_

#include "Screen_Data_Structs.h"

const SCREENELEMENTDATASOURCE_T SEDS_Demand_source = {6, &System_Trend_Status_Group};
const SCREENELEMENTDATASOURCE_T SEDS_Outlet_S3S4_sensor = {7,&System_Trend_Status_Group};
const SCREENELEMENTDATASOURCE_T SEDS_Firing_rate = {8,&System_Trend_Status_Group};
const SCREENELEMENTDATASOURCE_T SEDS_Fan_speed = {9,&System_Trend_Status_Group};
const SCREENELEMENTDATASOURCE_T SEDS_Flame_signal = {10,&System_Trend_Status_Group};
const SCREENELEMENTDATASOURCE_T SEDS_Inlet_S1_Sensor = {11,&System_Trend_Status_Group};
const SCREENELEMENTDATASOURCE_T SEDS_DHW_S6S7_Sensor = {12,&System_Trend_Status_Group};
const SCREENELEMENTDATASOURCE_T SEDS_S5_Sensor = {13,&System_Trend_Status_Group};
const SCREENELEMENTDATASOURCE_T SEDS_Stack_S8S9_Sensor = {14,&System_Trend_Status_Group};
const SCREENELEMENTDATASOURCE_T SEDS_Remote_Control_4_20_mA_Input = {15,&System_Trend_Status_Group};
const SCREENELEMENTDATASOURCE_T SEDS_Active_CH_Setpoint = {16,&System_Trend_Status_Group};
const SCREENELEMENTDATASOURCE_T SEDS_Active_DHW_Setpoint = {17,&System_Trend_Status_Group};
const SCREENELEMENTDATASOURCE_T SEDS_Active_LL_Setpoint = {18,&System_Trend_Status_Group};
const SCREENELEMENTDATASOURCE_T SEDS_Burner_name = {0,&Burner_name_Group};
const SCREENELEMENTDATASOURCE_T SEDS_Burner_control_state = {1,&Burner_Control_Status_Group};
const SCREENELEMENTDATASOURCE_T SEDS_Sequence_Time = {6,&Burner_Control_Status_Group};
const SCREENELEMENTDATASOURCE_T SEDS_Delay_Time = {7,&Burner_Control_Status_Group};

SCREENELEMENTLIST_T const Summary_Page_List[] = {
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_Burner_name},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_Demand_source},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_Burner_control_state},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_Outlet_S3S4_sensor},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_Firing_rate},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_Fan_speed},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_Flame_signal},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_Inlet_S1_Sensor},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_DHW_S6S7_Sensor},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_S5_Sensor},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_Stack_S8S9_Sensor},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_Remote_Control_4_20_mA_Input},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_Active_CH_Setpoint},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_Active_DHW_Setpoint},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_Active_LL_Setpoint},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_Sequence_Time},
		{(const SCREENELEMENTDATASOURCE_T *)&SEDS_Delay_Time},
};

SCREENPAGE_T Summary_Page = {
		sizeof(Summary_Page_List)/sizeof(SCREENELEMENTDATASOURCE_T *),
		(const SCREENELEMENTLIST_T *)&Summary_Page_List
};

#endif /* SCREEN_SUMMARY_PAGE_H_ */
