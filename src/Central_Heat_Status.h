/*
 * Central_Heat_Status.h
 *
 *  Created on: Dec. 16, 2019
 *      Author: greg
 */

#ifndef CENTRAL_HEAT_STATUS_H_
#define CENTRAL_HEAT_STATUS_H_

#include "Sola_Data_Structs.h"

SOLAMULTIVALUE_T const mv_CH_Status[] = {
	{0,"Unknown"},
	{1,"Disabled"},
	{2,"Normal"},
	{3,"Suspended"},
};

SOLAMULTIVALUE_T const mv_CH_setpoint_source[] = {
		{0,"Unknown"},
		{1,"Normal setpoint"},
		{2,"TOD setpoint"},
		{3,"Outdoor reset"},
		{4,"Remote control"},
		{7,"Outdoor reset time of day"},
		{8,"Reserved"},
		{9,"Outdoor boost"},
};

SOLAMULTIVALUE_T const mv_CH_heat_demand[] = {
		{0,"Off"},
		{1,"On"},
};

SOLAMULTIVALUE_T const mv_CH_burner_demand[] = {
		{0,"Off"},
		{1,"On"},
};

SOLAMULTIVALUE_T const mv_CH_frost_heat_demand[] = {
		{0,"Off"},
		{1,"On"},
};

SOLAMULTIVALUE_T const mv_CH_frost_burner_demand[] = {
		{0,"Off"},
		{1,"On"},
};

SOLAMULTIVALUE_T const mv_Active_CH_sensor[] = {
		{0,"No active sensor"},
		{2,"Outlet (S3S4) sensor"},
		{3,"Inlet (S1) sensor"},
		{4,"4-20mA input (S2)"},
		{5,"S5 sensor"},
		{6,"S10 sensor"},
		{7,"Steam (S1) sensor"},
};

SOLAMULTIVALUE_T const mv_Hot_Standby_Heat_Demand[] = {
		{0,"Off"},
		{1,"On"},
};

SOLAMULTIVALUE_T const mv_Hot_Standby_burner_demand[] = {
		{0,"Off"},
		{1,"On"},
};

SOLAMBREG_T const CH_status = {"CH status",0x03,0x0040,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_CH_Status,sizeof(mv_CH_Status)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const CH_setpoint_source = {"CH setpoint source",0x03,0x0041,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_CH_setpoint_source,sizeof(mv_CH_setpoint_source)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const CH_heat_demand = {"CH heat demand",0x03,0x0042,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_CH_heat_demand,sizeof(mv_CH_heat_demand)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const CH_burner_demand = {"CH burner demand",0x03,0x0043,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_CH_burner_demand,sizeof(mv_CH_burner_demand)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const CH_requested_rate = {"CH requested rate",0x03,0x0044,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Numericvalue,NULL,0};
SOLAMBREG_T const CH_frost_heat_demand = {"CH frost heat demand",0x03,0x0045,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_CH_frost_heat_demand,sizeof(mv_CH_frost_heat_demand)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const CH_frost_burner_demand = {"CH frost burner demand",0x03,0x0046,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_CH_frost_burner_demand,sizeof(mv_CH_frost_burner_demand)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Active_CH_on_hysteresis = {"Active CH on hysteresis",0x03,0x0047,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Hysteresis,NULL,0};
SOLAMBREG_T const Active_CH_off_hysteresis = {"Active CH off hysteresis",0x03,0x0048,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Hysteresis,NULL,0};
SOLAMBREG_T const Active_CH_pressure_on_hysteresis = {"Active CH pressure on hysteresis",0x03,0x0049,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Decimal1pl,NULL,0};
SOLAMBREG_T const Active_CH_pressure_off_hysteresis = {"Active CH pressure off hysteresis",0x03,0x004a,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Decimal1pl,NULL,0};
SOLAMBREG_T const Active_CH_pressure_operating_point = {"Active CH pressure operating point",0x03,0x004b,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Decimal1pl,NULL,0};
SOLAMBREG_T const Active_CH_sensor = {"Active CH sensor",0x03,0x004c,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Active_CH_sensor,sizeof(mv_Active_CH_sensor)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Hot_Standby_Heat_Demand = {"Hot Standby Heat Demand",0x03,0x004d,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Hot_Standby_Heat_Demand,sizeof(mv_Hot_Standby_Heat_Demand)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Hot_Standby_burner_demand = {"Hot Standby burner demand",0x03,0x004e,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Hot_Standby_burner_demand,sizeof(mv_Hot_Standby_burner_demand)/sizeof(SOLAMULTIVALUE_T)};

SOLAREGLIST_T const Central_Heat_Status[] = {
		{(const SOLAMBREG_T *)&CH_status},
		{(const SOLAMBREG_T *)&CH_setpoint_source},
		{(const SOLAMBREG_T *)&CH_heat_demand},
		{(const SOLAMBREG_T *)&CH_burner_demand},
		{(const SOLAMBREG_T *)&CH_requested_rate},
		{(const SOLAMBREG_T *)&CH_frost_heat_demand},
		{(const SOLAMBREG_T *)&CH_frost_burner_demand},
		{(const SOLAMBREG_T *)&Active_CH_on_hysteresis},
		{(const SOLAMBREG_T *)&Active_CH_off_hysteresis},
		{(const SOLAMBREG_T *)&Active_CH_pressure_on_hysteresis},
		{(const SOLAMBREG_T *)&Active_CH_pressure_off_hysteresis},
		{(const SOLAMBREG_T *)&Active_CH_pressure_operating_point},
		{(const SOLAMBREG_T *)&Active_CH_sensor},
		{(const SOLAMBREG_T *)&Hot_Standby_Heat_Demand},
		{(const SOLAMBREG_T *)&Hot_Standby_burner_demand},
};


SOLAREGGROUP_T const Central_Heat_Status_Group = {
		&CH_status,
		sizeof(Central_Heat_Status)/sizeof(SOLAMBREG_T *),
		(const SOLAREGLIST_T *)&Central_Heat_Status
};


#endif /* CENTRAL_HEAT_STATUS_H_ */
