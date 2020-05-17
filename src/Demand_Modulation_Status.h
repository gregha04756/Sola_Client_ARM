/*
 * Demand_Modulation_Status.h
 *
 *  Created on: Dec. 11, 2019
 *      Author: greg
 */

#ifndef DEMAND_MODULATION_STATUS_H_
#define DEMAND_MODULATION_STATUS_H_

#include "Sola_Data_Structs.h"


SOLAMULTIVALUE_T const mv_Active_rate_limiter[] = {
		{0,"None"},
		{1,"Outlet high limit"},
		{2,"Delta T limit"},
		{3,"Stack limit"},
		{4,"Slow start limit"},
		{5,"Anti-condensation"},
		{6,"Minimum modulation"},
		{7,"Forced rate"},
		{8,"IAS is open"}
};

SOLAMULTIVALUE_T const mv_Active_rate_override[] = {
		{0,"None"},
		{1,"Burner control default"},
		{2,"Burner control"},
		{3,"Manual firing rate"},
		{4,"Manual firing rate off"},
		{5,"Fan on during off cycle"},
		{6,"Assured low fire cutoff"},
};

SOLAMULTIVALUE_T const mv_Active_system_sensor[] = {
		{0,"No active sensor"},
		{1,"DHW (S6S7) sensor"},
		{2,"Outlet (S3S4) sensor"},
		{3,"Inlet (S1) sensor"},
		{4,"4-20mA input (S2)"},
		{5,"S5 sensor"},
		{6,"S10 sensor"},
		{7,"Steam (S1) sensor"},
		{8,"DHW (S6S7) and Inlet (S1) sensor"},
		{9,"DHW (S6S7) and S5 sensor"},
		{10,"Outlet (S3S4) and Inlet (S1) sensor"},
		{11,"Outlet (S3S4) and S5 sensor"},
};

SOLAMULTIVALUE_T const mv_Active_Lead_Lag_sensor[] = {
		{0,"No active sensor"},
		{2,"Outlet (S3S4) sensor"},
		{5,"S5 sensor"},
		{6,"S10 sensor"},
};

SOLAMBREG_T const Active_rate_limiter = {"Active rate limiter",0x03,0x0038,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Active_rate_limiter,sizeof(mv_Active_rate_limiter)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Limited_rate = {"Limited rate",0x03,0x0039,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Numericvalue,NULL,0};
SOLAMBREG_T const Active_rate_override = {"Active rate limiter",0x03,0x003a,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Active_rate_override,sizeof(mv_Active_rate_override)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Override_rate = {"Override rate",0x03,0x003b,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Numericvalue,NULL,0};
SOLAMBREG_T const Demand_rate = {"Demand rate",0x03,0x003c,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Numericvalue,NULL,0};
SOLAMBREG_T const Active_system_sensor = {"Active system sensor",0x03,0x003d,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Active_system_sensor,sizeof(mv_Active_system_sensor)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Active_Lead_Lag_sensor = {"Active Lead Lag sensor",0x03,0x003e,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Active_Lead_Lag_sensor,sizeof(mv_Active_Lead_Lag_sensor)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Demand_Modulation_Status_RESERVED00 = {"RESERVED",0x03,0x003f,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Novalue,NULL,0};

SOLAREGLIST_T const Demand_Modulation_Status[] = {
		{(const SOLAMBREG_T *)&Active_rate_limiter},
		{(const SOLAMBREG_T *)&Limited_rate},
		{(const SOLAMBREG_T *)&Active_rate_override},
		{(const SOLAMBREG_T *)&Override_rate},
		{(const SOLAMBREG_T *)&Demand_rate},
		{(const SOLAMBREG_T *)&Active_system_sensor},
		{(const SOLAMBREG_T *)&Active_Lead_Lag_sensor},
		{(const SOLAMBREG_T *)&Demand_Modulation_Status_RESERVED00},
};

SOLAREGGROUP_T const Demand_Modulation_Status_Group = {
		&Active_rate_limiter,
		sizeof(Demand_Modulation_Status)/sizeof(SOLAMBREG_T *),
		(const SOLAREGLIST_T *)&Demand_Modulation_Status
};


#endif /* DEMAND_MODULATION_STATUS_H_ */
