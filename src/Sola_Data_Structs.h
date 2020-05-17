#ifndef _SOLA_DATA_STRUCTS_H_
#define _SOLA_DATA_STRUCTS_H_

#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdbool.h>

#include "Sola_Defs_Consts.h"

enum SolaType {
	Novalue,		/* Value not defined */
	Numericvalue,	/* Generic numeric value */
	Bitmask,			/* Bit mask */
	Digitalvalue,	/* Boolean (digital) value, true/false, on/off, yes/no, etc. */
	Temperature,	/* Temperature value */
	TemperatureSetpoint, // Temperature setpoint value
	Setpointvalue, // Generic setpoint value
	Hysteresis,		// Hysteresis value
	Timevalue,		// Time in hh:mm:ss
	Seconds,		// Time in seconds
	Minutes,		// Time in minutes
	Hours,			// Time in hours
	SensorMultivalue,	// Special sensor multiple string value
	Multivalue,			// Generic multiple string value
	Stringvalue,		// String Value
	Percentvalue,		// Percentage value
	Lockoutcode,		// Lockoutcode
	Holdcode,			// Hold code
	Alertcode,			// Alert code
	Alarmreason,		// Alarm reason
	Alarmcode,			// Alarm code
	Fanspeed,			// Fan speed
	Decimal2pl,			// Real value, 0.01 precision
	Decimal1pl,		// Real value, 0.1 precision
	Unsigned32,		// Unsigned 32-bit value (2 16-bit holding registers)
	ODTemperature,    /* Outdoor temperature is a special case because it may come from one of several sources */
	SlaveIDvalue   /* Modbus slave ID */
};


typedef struct tagSolaMultiValue {
	const uint16_t i_value;
	const char* lp_String;
} SOLAMULTIVALUE_T;


typedef struct tagSolaRegister {
	const char* const ParmName;
	uint8_t const uc_Func_Code;
	const uint16_t us_RegAddr;
	const uint16_t us_RegCnt;
	const uint16_t us_cb_RegSize;
	char* pchStr;
	uint16_t const cbStrLen;
	_Bool bWrtable;
	_Bool bVisible;
	_Bool bNonSafety;
	const enum SolaType valuetype;
	SOLAMULTIVALUE_T * const lp_mv_list;
	int const i_mv_list_size;
} SOLAMBREG_T;

typedef struct tagSolaRegList { /* A register list must consist of a contiguous list of registers of equal size */
	const SOLAMBREG_T *  lp_Sola_Reg;
} SOLAREGLIST_T;

typedef struct tagSolaRegGroup { /* A register group must consist of a contiguous list of registers of equal size */
	const SOLAMBREG_T *base_reg;
	int const i_size;
	const SOLAREGLIST_T * lp_Sola_Reg_list;
} SOLAREGGROUP_T;

typedef struct tagSolaRegGroupList {
	const SOLAREGGROUP_T * lp_Sola_Reg_Group;
} SOLAREGGROUPLIST_T;

typedef struct tagListSolaRegGroups {
	int const i_size;
	const SOLAREGGROUPLIST_T * lp_Sola_Reg_Group_List;
} LISTSOLAREGGROUPS_T;

typedef struct tagMBRequest {
	uint8_t lpuchReq;
	int nSize;
} MBREQUEST_T;


typedef struct tagSolaAlertRecord {
	uint16_t ui16_AlertCode;
	uint32_t ui32_Cycle;
	uint32_t ui32_Hours;
	uint8_t ui8_Unused;
	uint8_t ui8_Count;
} SOLAALERTRECORD, *LPSOLAALERTRECORD;

typedef union tagSolaAlertUnion {
	uint8_t ui8_cc[12];
	SOLAALERTRECORD sar;
} SOLAALERTUNION, *LPSOLAALERTUNION;


typedef struct tagSolaLockoutRecord {
	uint16_t ui16_LockoutCode;				//0-1
	uint16_t ui16_AnnunciatorFirstOut;		//2-3
	uint16_t ui16_BurnerControlState;		//4-5
	uint16_t ui16_SequenceTime;				//6-7
	uint32_t ui32_Cycle;					//8-11
	uint32_t ui32_Hours;					//12-15
	uint16_t ui16_IO;						//16-17
	uint16_t ui16_Annunciator;				//18-19
	uint16_t ui16_OutletTemperature;		//20-21
	uint16_t ui16_InletTemperature;			//22-23
	uint16_t ui16_DHWTemperature;			//24-25
	uint16_t ui16_ODTemperature;			//26-27
	uint16_t ui16_StackTemperature;			//28-29
	uint16_t ui16_4to20mAInput;				//30-31
	uint8_t ui8_FaultData0;					//32
	uint8_t ui8_FaultData1;					//33
} SOLALOCKOUTRECORD, *LPSOLALOCKOUTRECORD;

typedef union tagSolaLockoutUnion {
	uint8_t cc[sizeof(SOLALOCKOUTRECORD)];
	SOLALOCKOUTRECORD slr;
} SOLALOCKOUTUNION, *LPSOLALOCKOUTUNION;

#endif /* _SOLA_DATA_STRUCTS_H_ */
