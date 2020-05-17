#ifndef _BURNER_CONTROL_STATUS_REG_GROUP_H_
#define _BURNER_CONTROL_STATUS_REG_GROUP_H_

#include "Sola_Data_Structs.h"


SOLAMULTIVALUE_T const mv_Burner_Control_Status[] = {
	{0,"Disabled"},
	{1,"Locked out"},
	{4,"Anti-short cycle"},
	{5,"Unconfigured safety data"},
	{34,"Standby Hold"},
	{35,"Standby Delay"},
	{48,"Normal Standby"},
	{49,"Preparing"},
	{50,"Ignition"},
	{51,"Firing"},
	{52,"Postpurge"},
};

SOLAMULTIVALUE_T const mv_Burner_control_state[] = {
		{0,"Initiate"},
		{1,"Standby Delay"},
		{2,"Standby"},
		{3,"Safe Startup"},
		{4,"Prepurge - Drive to Purge Rate"},
		{5,"Prepurge – Measured Purge Time"},
		{6,"Prepurge – Drive to Lightoff Rate"},
		{7,"Preignition Test"},
		{8,"Preignition Time"},
		{9,"Pilot Flame Establishing Period"},
		{10,"Main Flame Establishing Period"},
		{11,"Direct Burner Ignition"},
		{12,"Run"},
		{13,"Postpurge"},
		{14,"Lockout"},
		{15,"Prepurge (Fulton pulse)"},
		{16,"Ignition (Fulton pulse)"},
		{17,"Combustion Pressure Establish (Fulton pulse)"},
		{18,"Combustion Pressure Stabilization (Fulton pulse)"},
		{19,"Main Flame Stabilization (Fulton pulse)"},
		{255,"Safety Processor Offline"},
};



SOLAMBREG_T const Burner_Control_Status = {"Burner control status",0x03,0x0020,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Burner_Control_Status,sizeof(mv_Burner_Control_Status)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Burner_Control_State = {"Burner control state",0x03,0x0021,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Burner_control_state,sizeof(mv_Burner_control_state)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Lockout_Code = {"Lockout code",0x03,0x0022,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,NULL,0};
SOLAMBREG_T const Alarm_Reason = {"Alarm reason",0x03,0x0023,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,NULL,0};
SOLAMBREG_T const Annunciator_First_Out = {"Annunciator first out",0x03,0x0024,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,NULL,0};
SOLAMBREG_T const Annunciator_Hold = {"Annunciator hold",0x03,0x0025,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,NULL,0};
SOLAMBREG_T const Sequence_Time = {"Sequence time",0x03,0x0026,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Seconds,NULL,0};
SOLAMBREG_T const Delay_Time = {"Delay time",0x03,0x0027,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Seconds,NULL,0};
SOLAMBREG_T const Hold_Code = {"Hold code",0x03,0x0028,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,NULL,0};
SOLAMBREG_T const Burner_Control_Flags = {"Burner control flags",0x03,0x0029,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Bitmask,NULL,0};
SOLAMBREG_T const CH_Remote_Stat = {"CH remote Stat",0x03,0x002a,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,NULL,0};


SOLAREGLIST_T Burner_Control_Status_List[] = {
	{(const SOLAMBREG_T *)&Burner_Control_Status},
	{(const SOLAMBREG_T *)&Burner_Control_State},
	{(const SOLAMBREG_T *)&Lockout_Code},
	{(const SOLAMBREG_T *)&Alarm_Reason},
	{(const SOLAMBREG_T *)&Annunciator_First_Out},
	{(const SOLAMBREG_T *)&Annunciator_Hold},
	{(const SOLAMBREG_T *)&Sequence_Time},
	{(const SOLAMBREG_T *)&Delay_Time},
	{(const SOLAMBREG_T *)&Hold_Code},
	{(const SOLAMBREG_T *)&Burner_Control_Flags},
	{(const SOLAMBREG_T *)&CH_Remote_Stat}
};

SOLAREGGROUP_T Burner_Control_Status_Group = {
		&Burner_Control_Status,
		sizeof(Burner_Control_Status_List)/sizeof(SOLAMBREG_T *),
		(const SOLAREGLIST_T *)&Burner_Control_Status_List
};

#endif /* _BURNER_CONTROL_STATUS_REG_GROUP_H_ */
