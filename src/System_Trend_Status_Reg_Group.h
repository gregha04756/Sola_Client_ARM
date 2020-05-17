/*
 * System_Trend_Status_Reg_Group.h
 *
 *  Created on: Dec. 9, 2019
 *      Author: greg
 */

#ifndef SYSTEM_TREND_STATUS_REG_GROUP_H_
#define SYSTEM_TREND_STATUS_REG_GROUP_H_



#include "Sola_Data_Structs.h"


SOLAMULTIVALUE_T const mv_Demand_Source[] = {
	{0,"Unknown"},
	{1,"No source demand"},
	{2,"CH"},
	{3,"DHW"},
	{4,"Lead Lag slave"},
	{5,"Lead Lag master"},
	{6,"CH frost protection"},
	{7,"DHW frost protection"},
	{8,"No demand due to burner switch (register 199) turned off"},
	{9,"DHW storage"},
	{10,"Reserved"},
	{11,"Warm weather shutdown"},
	{12,"Hot standby"}
};

SOLAMULTIVALUE_T const mv_Register_Access_Status[] = {
		{0,"No register writes allowed"},
		{1,"Installer register writes allowed"},
		{2,"OEM register writes allowed"},
		{3,"All register"}
};

SOLAMBREG_T const Status_Change = {"Status Change",0x03,0x0000,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Bitmask,NULL,0};
SOLAMBREG_T const Configuration_Change = {"Configuration Change",0x03,0x0001,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Bitmask,NULL,0};
SOLAMBREG_T const Digital_IO = {"Digital I/O",0x03,0x0002,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Bitmask,NULL,0};
SOLAMBREG_T const Annunciation_IO = {"Annunciation I/O",0x03,0x0003,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Bitmask,NULL,0};
SOLAMBREG_T const Limits = {"Limits",0x03,0x0004,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Bitmask,NULL,0};
SOLAMBREG_T const Program_Module_Status = {"Program Module (PM) status",0x03,0x0005,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Bitmask,NULL,0};
SOLAMBREG_T const Demand_Source = {"Demand source",0x03,0x0006,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Demand_Source,sizeof(mv_Demand_Source)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Outlet_S3S4_Sensor = {"Outlet (S3S4) or Outlet limit (S3) sensor",0x03,0x0007,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Temperature,NULL,0};
SOLAMBREG_T const Firing_Rate = {"Firing rate",0x03,0x0008,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Numericvalue,NULL,0};
SOLAMBREG_T const Fan_Speed = {"Fan speed",0x03,0x0009,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Numericvalue,NULL,0};
SOLAMBREG_T const Flame_Signal = {"Flame signal",0x03,0x000a,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Decimal2pl,NULL,0};
SOLAMBREG_T const Inlet_S1_Sensor = {"Inlet (S1) sensor",0x03,0x000b,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Temperature,NULL,0};
SOLAMBREG_T const DHW_S6S7_Sensor = {"DHW (S6S7) or DHW limit (S6) sensor",0x03,0x000c,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Temperature,NULL,0};
SOLAMBREG_T const S5_Sensor = {"S5 sensor",0x03,0x000d,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Temperature,NULL,0};
SOLAMBREG_T const Stack_S8S9_Sensor = {"Stack (S8S9) or Stack limit (S8) sensor",0x03,0x000e,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Temperature,NULL,0};
SOLAMBREG_T const Remote_Control_4_20_mA_Input = {"4-20 mA remote control input (S2) terminal",0x03,0x000f,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Decimal1pl,NULL,0};
SOLAMBREG_T const Active_CH_Setpoint = {"Active CH setpoint",0x03,0x0010,0x0001,sizeof(uint16_t),NULL,0,true,true,true,TemperatureSetpoint,NULL,0};
SOLAMBREG_T const Active_DHW_Setpoint = {"Active DHW setpoint",0x03,0x0011,0x0001,sizeof(uint16_t),NULL,0,true,true,true,TemperatureSetpoint,NULL,0};
SOLAMBREG_T const Active_LL_Setpoint = {"Active LL setpoint",0x03,0x0012,0x0001,sizeof(uint16_t),NULL,0,true,true,true,TemperatureSetpoint,NULL,0};
SOLAMBREG_T const Register_Access_Status = {"Register Access Status",0x03,0x0013,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Register_Access_Status,sizeof(mv_Register_Access_Status)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Steam_Pressure = {"Steam pressure",0x03,0x0014,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Decimal1pl,NULL,0};
SOLAMBREG_T const Analog_Modulation_Input = {"Analog modulation input",0x03,0x0015,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Decimal1pl,NULL,0};
SOLAMBREG_T const Active_CH_Pressure_Setpoint = {"Active CH pressure setpoint",0x03,0x0016,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Decimal1pl,NULL,0};
SOLAMBREG_T const Extended_Status_Change = {"Extended Status Change",0x03,0x0017,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Bitmask,NULL,0};
SOLAMBREG_T const Reserved_0x0018 = {"RESERVED",0x03,0x0018,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Novalue,NULL,0};
SOLAMBREG_T const Active_CH_Operating_Point = {"Active CH operating point",0x03,0x0019,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Temperature,NULL,0};
SOLAMBREG_T const Active_DHW_Operating_Point = {"Active DHW operating point",0x03,0x001a,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Temperature,NULL,0};
SOLAMBREG_T const Active_Lead_Lag_Operating_Point = {"Active Lead Lag operating point",0x03,0x001b,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Temperature,NULL,0};
SOLAMBREG_T const Active_System_Operating_Point = {"Active system operating point",0x03,0x001c,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Temperature,NULL,0};
SOLAMBREG_T const Active_System_Setpoint = {"Active system setpoint",0x03,0x001d,0x0001,sizeof(uint16_t),NULL,0,true,true,true,TemperatureSetpoint,NULL,0};
SOLAMBREG_T const Active_System_On_Hysteresis = {"Active system on hysteresis",0x03,0x001e,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Hysteresis,NULL,0};
SOLAMBREG_T const Active_System_Off_Hysteresis = {"Active system off hysteresis",0x03,0x001f,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Hysteresis,NULL,0};


SOLAREGLIST_T const System_Trend_Status[] = {
	{(const SOLAMBREG_T *)&Status_Change},
	{(const SOLAMBREG_T *)&Configuration_Change},
	{(const SOLAMBREG_T *)&Digital_IO},
	{(const SOLAMBREG_T *)&Annunciation_IO},
	{(const SOLAMBREG_T *)&Limits},
	{(const SOLAMBREG_T *)&Program_Module_Status},
	{(const SOLAMBREG_T *)&Demand_Source},
	{(const SOLAMBREG_T *)&Outlet_S3S4_Sensor},
	{(const SOLAMBREG_T *)&Firing_Rate},
	{(const SOLAMBREG_T *)&Fan_Speed},
	{(const SOLAMBREG_T *)&Flame_Signal},
	{(const SOLAMBREG_T *)&Inlet_S1_Sensor},
	{(const SOLAMBREG_T *)&DHW_S6S7_Sensor},
	{(const SOLAMBREG_T *)&S5_Sensor},
	{(const SOLAMBREG_T *)&Stack_S8S9_Sensor},
	{(const SOLAMBREG_T *)&Remote_Control_4_20_mA_Input},
	{(const SOLAMBREG_T *)&Active_CH_Setpoint},
	{(const SOLAMBREG_T *)&Active_DHW_Setpoint},
	{(const SOLAMBREG_T *)&Active_LL_Setpoint},
	{(const SOLAMBREG_T *)&Register_Access_Status},
	{(const SOLAMBREG_T *)&Steam_Pressure},
	{(const SOLAMBREG_T *)&Analog_Modulation_Input},
	{(const SOLAMBREG_T *)&Active_CH_Pressure_Setpoint},
	{(const SOLAMBREG_T *)&Extended_Status_Change},
	{(const SOLAMBREG_T *)&Reserved_0x0018},
	{(const SOLAMBREG_T *)&Active_CH_Operating_Point},
	{(const SOLAMBREG_T *)&Active_DHW_Operating_Point},
	{(const SOLAMBREG_T *)&Active_Lead_Lag_Operating_Point},
	{(const SOLAMBREG_T *)&Active_System_Operating_Point},
	{(const SOLAMBREG_T *)&Active_System_Setpoint},
	{(const SOLAMBREG_T *)&Active_System_On_Hysteresis},
	{(const SOLAMBREG_T *)&Active_System_Off_Hysteresis}
};

SOLAREGGROUP_T System_Trend_Status_Group = {
		&Status_Change,
		sizeof(System_Trend_Status)/sizeof(SOLAMBREG_T *),
		(const SOLAREGLIST_T *)&System_Trend_Status
};

#endif /* SYSTEM_TREND_STATUS_REG_GROUP_H_ */
