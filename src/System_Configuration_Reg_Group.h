#ifndef _SYSTEM_CONFIGURATION_REG_GROUP_H_
#define _SYSTEM_CONFIGURATION_REG_GROUP_H_

#include "Sola_Data_Structs.h"


uint8_t sz_Burner_name[21] = {'\0'};
uint8_t sz_Installation_data[21] = {'\0'};
uint8_t sz_OEM_ID[21] = {'\0'};
uint8_t sz_OS_number[17] = {'\0'};
uint8_t sz_Date_code[11] = {'\0'};

SOLAMULTIVALUE_T const mv_Product_type[] = {
	{0x0000,"Unknown product"},
	{0x0100,"Residential Hydronic boiler control"},
	{0x0101,"Commercial Hydronic boiler control"},
	{0x0200,"Residential Steam boiler control"},
	{0x0201,"Commercial Steam boiler control"},
	{0x0300,"Reserved"},
	{0x0400,"Residential Fulton pulse hydronic boiler control"},
	{0x0401,"Commercial Fulton pulse hydronic boiler control"},
	{0x0500,"Residential Fulton pulse steam boiler control"},
	{0x0501,"Commercial Fulton pulse steam boiler control"},
	{0x0800,"Residential Cleaver Brooks hydronic boiler control"},
	{0x0801,"Commercial Cleaver Brooks hydronic boiler control"},
	{0x0700,"Residential Cleaver Brooks steam boiler control"},
	{0x0701,"Commercial Cleaver Brooks steam boiler control"}
};

SOLAMBREG_T const System_Configuration_Product_type = {"Product type",0x03,0x00b0,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Product_type,sizeof(mv_Product_type)/sizeof(SOLAMULTIVALUE_T)};

SOLAREGLIST_T System_Configuration_Product_type_List[] = {
	{(const SOLAMBREG_T *)&System_Configuration_Product_type}
};

SOLAREGGROUP_T System_Configuration_Product_type_Group = {
		&System_Configuration_Product_type,
		sizeof(System_Configuration_Product_type_List)/sizeof(SOLAMBREG_T *),
		(const SOLAREGLIST_T *)&System_Configuration_Product_type_List
};

SOLAMULTIVALUE_T mv_Temperature_units[] = {
	{0,"Fahrenheit"},
	{1,"Celsius"}
};

SOLAMULTIVALUE_T mv_Power_up_with_lockout[] = {
	{0,"Clear lockout on powerup (reset)"},
	{1,"Do not clear lockout on power-up (preserve)"}
};

SOLAMBREG_T const Temperature_units = {"Temperature units",0x03,0x00b2,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Temperature_units,sizeof(mv_Temperature_units)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Antishort_cycle_time = {"Antishort cycle time",0x03,0x00b3,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Seconds,NULL,0};
SOLAMBREG_T const Alarm_silence_time = {"Alarm silence time",0x03,0x00b4,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Seconds,NULL,0};
SOLAMBREG_T const Power_up_with_lockout = {"Power up with lockout",0x03,0x00b5,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Multivalue,(SOLAMULTIVALUE_T * const)mv_Power_up_with_lockout,sizeof(mv_Power_up_with_lockout)/sizeof(SOLAMULTIVALUE_T)};
SOLAMBREG_T const Reset_and_restart = {"Reset and restart",0x03,0x00b6,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Numericvalue,NULL,0};
SOLAMBREG_T const Burner_name = {"Burner name",0x03,0x00b7,0x0001,sizeof(uint16_t),sz_Burner_name,21,true,true,true,Stringvalue,NULL,0};
SOLAMBREG_T const Installation_data = {"Installation data",0x03,0x00b8,0x0001,sizeof(uint16_t),sz_Installation_data,21,true,true,true,Stringvalue,NULL,0};
SOLAMBREG_T const OEM_ID = {"OEM ID",0x03,0x00b9,0x0001,sizeof(uint16_t),sz_OEM_ID,21,true,true,true,Stringvalue,NULL,0};
SOLAMBREG_T const OS_number = {"OS number",0x03,0x00ba,0x0001,sizeof(uint16_t),sz_OS_number,17,true,true,true,Stringvalue,NULL,0};
SOLAMBREG_T const Date_code = {"Date code",0x03,0x00bb,0x0001,sizeof(uint16_t),sz_Date_code,11,true,true,true,Stringvalue,NULL,0};
SOLAMBREG_T const Safety_microprocessor_build = {"Safety microprocessor build",0x03,0x00bc,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Numericvalue,NULL,0};
SOLAMBREG_T const Application_microprocessor_build = {"Application microprocessor build",0x03,0x00bd,0x0001,sizeof(uint16_t),NULL,0,true,true,true,Numericvalue,NULL,0};

SOLAREGLIST_T System_Configuration_List[] = {
	{(const SOLAMBREG_T *)&Temperature_units},
	{(const SOLAMBREG_T *)&Antishort_cycle_time},
	{(const SOLAMBREG_T *)&Alarm_silence_time},
	{(const SOLAMBREG_T *)&Power_up_with_lockout},
};

SOLAREGLIST_T System_Configuration_Build_List[] = {
	{(const SOLAMBREG_T *)&Safety_microprocessor_build},
	{(const SOLAMBREG_T *)&Application_microprocessor_build}
};

SOLAREGGROUP_T System_Configuration_Group = {
		&Temperature_units,
		sizeof(System_Configuration_List)/sizeof(SOLAMBREG_T*),
		(const SOLAREGLIST_T *)&System_Configuration_List
};

SOLAREGGROUP_T System_Configuration_Build_Group = {
		&Safety_microprocessor_build,
		sizeof(System_Configuration_Build_List)/sizeof(SOLAMBREG_T*),
		(const SOLAREGLIST_T *)&System_Configuration_Build_List
};

/*
 * The following are string values and need their own register group so they can be handled
 * individually
 *
 */

/* Burner name */
SOLAREGLIST_T Burner_name_List[] = {
	(const SOLAMBREG_T *)&Burner_name
};

SOLAREGGROUP_T Burner_name_Group = {
		&Burner_name,
		sizeof(Burner_name_List) / sizeof(SOLAMBREG_T*),
		(const SOLAREGLIST_T *)&Burner_name_List
};

/* Installation data */
SOLAREGLIST_T Installation_data_List[] = {
	(const SOLAMBREG_T *)&Installation_data
};

SOLAREGGROUP_T Installation_data_Group = {
		&Installation_data,
		sizeof(Installation_data_List) / sizeof(SOLAMBREG_T*),
		(const SOLAREGLIST_T *)&Installation_data_List
};

/* OEM ID*/
SOLAREGLIST_T OEM_ID_List[] = {
	(const SOLAMBREG_T *)&OEM_ID
};

SOLAREGGROUP_T OEM_ID_Group = {
		&OEM_ID,
		sizeof(OEM_ID_List) / sizeof(SOLAMBREG_T*),
		(const SOLAREGLIST_T *)&OEM_ID_List
};

/* OS number*/
SOLAREGLIST_T OS_number_List[] = {
	(const SOLAMBREG_T *)&OS_number
};

SOLAREGGROUP_T OS_number_Group = {
		&OS_number,
		sizeof(OS_number_List) / sizeof(SOLAMBREG_T*),
		(const SOLAREGLIST_T *)&OS_number_List
};

/* Date code*/
SOLAREGLIST_T Date_code_List[] = {
	(const SOLAMBREG_T *)&Date_code
};

SOLAREGGROUP_T Date_code_Group = {
		&Date_code,
		sizeof(Date_code_List) / sizeof(SOLAMBREG_T*),
		(const SOLAREGLIST_T *)&Date_code_List
};


#endif /* _SYSTEM_CONFIGURATION_REG_GROUP_H_ */
