/*
 * Screen_Data_Structs.h
 *
 *  Created on: Dec. 9, 2019
 *      Author: greg
 */

#ifndef SCREEN_DATA_STRUCTS_H_
#define SCREEN_DATA_STRUCTS_H_

#include "Reg_Groups.h"

typedef struct tagScreenElementDataSource {
	const uint16_t offset;
	const SOLAREGGROUP_T * reg_group;
} SCREENELEMENTDATASOURCE_T;

typedef struct tagScreenElementList {
	const SCREENELEMENTDATASOURCE_T * p_Screen_Element;
} SCREENELEMENTLIST_T;

typedef struct tagScreenPage {
	const uint16_t count;
	const SCREENELEMENTLIST_T * p_Screen_Element_List;
} SCREENPAGE_T;


typedef struct tagScreenPageList {
	const SCREENPAGE_T * p_Screen_Page;
} SCREENPAGELIST_T;


typedef struct tagScreenPageGroup {
	const uint16_t count;
	const SCREENPAGELIST_T * p_Screen_Page_List;
} SCREENPAGEGROUP_T;

typedef struct tagScreenPageGroupList {
	const SCREENPAGEGROUP_T * lp_Screen_Page_Group;
} SCREENPAGEGROUPLIST_T;

typedef struct tagListScreenPageGroups {
	int const i_size;
	const SOLAREGGROUPLIST_T * lp_Screen_Page_Group_List;
} LISTSCREENPAGEGROUPS_T;

#endif /* SCREEN_DATA_STRUCTS_H_ */
