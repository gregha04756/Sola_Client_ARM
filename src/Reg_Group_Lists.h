/*
 * Reg_Groups.h
 *
 *  Created on: May 17, 2019
 *      Author: greg
 */

#ifndef REG_GROUP_LISTS_H_
#define REG_GROUP_LISTS_H_

#include "Sola_Data_Structs.h"

extern SOLAREGGROUP_T System_Trend_Status_Group;
extern SOLAREGGROUP_T Burner_Control_Status_Group;
extern SOLAREGGROUP_T Sensor_Status_Group;
extern SOLAREGGROUP_T Demand_Modulation_Status_Group;
extern SOLAREGGROUP_T Central_Heat_Status_Group;
extern SOLAREGGROUP_T System_Configuration_Product_type_Group;
extern SOLAREGGROUP_T System_Configuration_Group;
extern SOLAREGGROUP_T Burner_name_Group;
extern SOLAREGGROUP_T Installation_data_Group;
extern SOLAREGGROUP_T OEM_ID_Group;
extern SOLAREGGROUP_T OS_number_Group;
extern SOLAREGGROUP_T Date_code_Group;

SOLAREGGROUPLIST_T All_Groups[] = {
		{(const SOLAREGGROUP_T *)&System_Trend_Status_Group},
		{(const SOLAREGGROUP_T *)&Burner_Control_Status_Group},
		{(const SOLAREGGROUP_T *)&Sensor_Status_Group},
		{(const SOLAREGGROUP_T *)&Demand_Modulation_Status_Group},
		{(const SOLAREGGROUP_T *)&Central_Heat_Status_Group},
		{(const SOLAREGGROUP_T *)&System_Configuration_Product_type_Group},
		{(const SOLAREGGROUP_T *)&System_Configuration_Group},
		{(const SOLAREGGROUP_T *)&Burner_name_Group},
		{(const SOLAREGGROUP_T *)&Installation_data_Group},
		{(const SOLAREGGROUP_T *)&OEM_ID_Group},
		{(const SOLAREGGROUP_T *)&OS_number_Group},
		{(const SOLAREGGROUP_T *)&Date_code_Group}

};


SOLAREGGROUPLIST_T Trend_Groups[] = {
		{(const SOLAREGGROUP_T *)&System_Trend_Status_Group}
};

SOLAREGGROUPLIST_T Status_Groups[] = {
		{(const SOLAREGGROUP_T *)&Burner_Control_Status_Group},
		{(const SOLAREGGROUP_T *)&Sensor_Status_Group},
		{(const SOLAREGGROUP_T *)&Demand_Modulation_Status_Group},
		{(const SOLAREGGROUP_T *)&Central_Heat_Status_Group},
};

SOLAREGGROUPLIST_T Configuration_Groups[] = {
		{(const SOLAREGGROUP_T *)&System_Configuration_Product_type_Group},
		{(const SOLAREGGROUP_T *)&System_Configuration_Group},
		{(const SOLAREGGROUP_T *)&Burner_name_Group},
		{(const SOLAREGGROUP_T *)&Installation_data_Group},
		{(const SOLAREGGROUP_T *)&OEM_ID_Group},
		{(const SOLAREGGROUP_T *)&OS_number_Group},
		{(const SOLAREGGROUP_T *)&Date_code_Group}
};

LISTSOLAREGGROUPS_T List_All_Groups = {
		(int const)(sizeof(All_Groups)/sizeof(SOLAREGGROUPLIST_T)),
		(const SOLAREGGROUPLIST_T *)All_Groups
};

LISTSOLAREGGROUPS_T List_Trend_Groups = {
		(int const)(sizeof(Trend_Groups)/sizeof(SOLAREGGROUPLIST_T)),
		(const SOLAREGGROUPLIST_T *)Trend_Groups
};

LISTSOLAREGGROUPS_T List_Status_Groups = {
		(int const)(sizeof(Status_Groups)/sizeof(SOLAREGGROUPLIST_T)),
		(const SOLAREGGROUPLIST_T *)Status_Groups
};

LISTSOLAREGGROUPS_T List_Configuration_Groups = {
		(int const)(sizeof(Configuration_Groups)/sizeof(SOLAREGGROUPLIST_T)),
		(const SOLAREGGROUPLIST_T *)Configuration_Groups
};

#endif /* REG_GROUP_LISTS_H_ */
