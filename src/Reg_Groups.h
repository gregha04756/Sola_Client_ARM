/*
 * Reg_Groups.h
 *
 *  Created on: May 17, 2019
 *      Author: greg
 */

#ifndef REG_GROUPS_H_
#define REG_GROUPS_H_

#include "Sola_Data_Structs.h"

extern const char *Burner_Control_Status_Group_Name;

extern SOLAREGGROUP_T System_Trend_Status_Group;
extern SOLAREGGROUP_T Burner_Control_Status_Group;
extern SOLAREGGROUP_T Sensor_Status_Group;
extern SOLAREGGROUP_T Demand_Modulation_Status_Group;
extern SOLAREGGROUP_T System_Configuration_Product_type_Group;
extern SOLAREGGROUP_T System_Configuration_Group;
extern SOLAREGGROUP_T System_Configuration_Build_Group;
extern SOLAREGGROUP_T Burner_name_Group;
extern SOLAREGGROUP_T Installation_data_Group;
extern SOLAREGGROUP_T OEM_ID_Group;
extern SOLAREGGROUP_T OS_number_Group;
extern SOLAREGGROUP_T Date_code_Group;

extern SOLAREGGROUPLIST_T All_Groups[];
extern SOLAREGGROUPLIST_T Trend_Groups[];
extern SOLAREGGROUPLIST_T Status_Groups[];
extern SOLAREGGROUPLIST_T Configuration_Groups[];

extern LISTSOLAREGGROUPS_T List_All_Groups;
extern LISTSOLAREGGROUPS_T List_Trend_Groups;
extern LISTSOLAREGGROUPS_T List_Status_Groups;
extern LISTSOLAREGGROUPS_T List_Configuration_Groups;

#endif /* REG_GROUPS_H_ */
