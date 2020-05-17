/*
 * Screen_Page_Lists.h
 *
 *  Created on: Dec. 10, 2019
 *      Author: greg
 */

#ifndef SCREEN_PAGE_LISTS_H_
#define SCREEN_PAGE_LISTS_H_

#include "Screen_Data_Structs.h"

extern SCREENPAGE_T Summary_Page;


SCREENPAGELIST_T All_Pages[] = {
		{(const SCREENPAGE_T *)&Summary_Page}
};

SCREENPAGEGROUP_T All_Pages_Group[] = {
		(const uint16_t)(sizeof(All_Pages)/sizeof(SCREENPAGELIST_T)),
		{(const SCREENPAGELIST_T *)&All_Pages}
};

#endif /* SCREEN_PAGE_LISTS_H_ */
