#ifndef _SENSOR_STATUS_REG_GROUP_H_
#define _SENSOR_STATUS_REG_GROUP_H_

#include "Sola_Data_Structs.h"

SOLAMULTIVALUE_T const mv_Sensor_state[] = {
	{0,"None"},
	{1,"Normal"},
	{2,"Open"},
	{3,"Shorted"},
	{4,"Outside high range"},
	{5,"Outside low range"},
	{6,"Not reliable"}
};

SOLAMBREG_T const Outlet_operation_terminal = {"Outlet operation (S4=J8-10) terminal",0x03,0x002b,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Temperature,NULL,0};
SOLAMBREG_T const DHW_operation_terminal = {"DHW operation (S7=J9-3) terminal",0x03,0x002c,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Temperature,NULL,0};
SOLAMBREG_T const Stack_or_Heat_exchanger_operation_terminal = {"Stack or Heat exchanger operation (S9=J9-6) terminal",0x03,0x002d,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Temperature,NULL,0};
SOLAMBREG_T const Outlet_operation_sensor_state = {"Fan speed",0x03,0x002e,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Sensor_state,sizeof(mv_Sensor_state)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const DHW_operation_sensor_state = {"DHW operation sensor (S7=J9-3) state",0x03,0x002f,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Sensor_state,sizeof(mv_Sensor_state)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Outlet_limit_sensor_state = {"Outlet limit sensor (S3=J8-8) stater",0x03,0x0030,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Sensor_state,sizeof(mv_Sensor_state)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Inlet_sensor_state = {"Inlet sensor (S1=J8-4) state",0x03,0x0031,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Sensor_state,sizeof(mv_Sensor_state)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const DHW_limit_sensor_state = {"DHW limit sensor (S7=J9-1) state",0x03,0x0032,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Sensor_state,sizeof(mv_Sensor_state)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Stack_limit_sensor_state = {"Stack limit sensor (S8=J9-4) state",0x03,0x0033,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Sensor_state,sizeof(mv_Sensor_state)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const S5_sensor_state = {"S5 (J8-11) sensor state",0x03,0x0034,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Sensor_state,sizeof(mv_Sensor_state)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Remote_control_input_state = {"4-20mA remote control input (S2=J8-6) state",0x03,0x0035,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Sensor_state,sizeof(mv_Sensor_state)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Pressure_sensor_state = {"Pressure sensor (S1=J8-4) state",0x03,0x0036,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Sensor_state,sizeof(mv_Sensor_state)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Stack_operation_or_Heat_exchanger_sensor_state = {"Stack operation or Heat exchanger sensor (S9=J9-6) state",0x03,0x0037,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Sensor_state,sizeof(mv_Sensor_state)/sizeof(SOLAMULTIVALUE_T)};


SOLAREGLIST_T const Sensor_Status[] = {
	{(const SOLAMBREG_T *)&Outlet_operation_terminal},
	{(const SOLAMBREG_T *)&DHW_operation_terminal},
	{(const SOLAMBREG_T *)&Stack_or_Heat_exchanger_operation_terminal},
	{(const SOLAMBREG_T *)&Outlet_operation_sensor_state},
	{(const SOLAMBREG_T *)&DHW_operation_sensor_state},
	{(const SOLAMBREG_T *)&Outlet_limit_sensor_state},
	{(const SOLAMBREG_T *)&Inlet_sensor_state},
	{(const SOLAMBREG_T *)&DHW_limit_sensor_state},
	{(const SOLAMBREG_T *)&Stack_limit_sensor_state},
	{(const SOLAMBREG_T *)&S5_sensor_state},
	{(const SOLAMBREG_T *)&Remote_control_input_state},
	{(const SOLAMBREG_T *)&Pressure_sensor_state},
	{(const SOLAMBREG_T *)&Stack_operation_or_Heat_exchanger_sensor_state}
};

SOLAREGGROUP_T Sensor_Status_Group = {
		&Outlet_operation_terminal,
		sizeof(Sensor_Status)/sizeof(SOLAMBREG_T *),
		(SOLAREGLIST_T * const)Sensor_Status
};

#endif /* _SENSOR_STATUS_REG_GROUP_H_ */
