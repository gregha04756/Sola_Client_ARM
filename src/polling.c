/*
 * polling.c
 *
 *  Created on: May 17, 2019
 *      Author: greg
 */
#include <gtk/gtk.h>
#include <gtk/gtkx.h>

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <glib/gprintf.h>

#include "modbus.h"
#include "Reg_Groups.h"
#include "callbacks.h"

volatile uint8_t g_connected_unit_ID = 0;

extern uint16_t Sola_Data[];
extern volatile int die;
extern pthread_mutex_t poll_mutex;
extern void INThandler(int signum);
extern bool Check_Status_Change(modbus_t * ctx);
extern bool Check_Configuration_Change(modbus_t * ctx);

#if defined(_DEBUG)
gint print_Sola_Data_registers(uint16_t *buf, uint16_t count)
{
	int i_x;
	gint gi_r;
	gi_r = g_fprintf(stderr,"Sola_Data[%d - %d] ",(buf-(&Sola_Data[0])),buf+count-(&Sola_Data[0])-1);

	for (i_x = 0;i_x < count && (&Sola_Data[0]+(2*Sola_Register_Count)>(buf+(2*i_x))); ++i_x)
	{
		gi_r = g_printf("0x%04x ",*(buf+i_x));
	}
	return  (gi_r = g_printf("\n"));
}
#endif

long read_reg_group(modbus_t * ctx,
	const SOLAREGGROUP_T * lp_group)
{
#if defined(_DEBUG)
	uint8_t mystring[21] = {'\0'};
#endif
	int i_r;
	long l_r;
	void *p_v;
	const SOLAREGLIST_T * lp_reg_list = lp_group->lp_Sola_Reg_list;
	int i_count = lp_group->i_size;
	uint16_t start_addr = lp_group->base_reg->us_RegAddr;
/*	uint16_t start_addr = lp_reg_list[0].lp_Sola_Reg->us_RegAddr; */
	if ((NULL != lp_group->base_reg->pchStr) &&
		(Stringvalue == lp_group->base_reg->valuetype))
	{
#if defined(_DEBUG)
		p_v = (void*) strncpy(
				(char*)mystring,
				lp_group->base_reg->pchStr,
				(size_t)lp_group->base_reg->cbStrLen
				);
#endif
	    p_v = memset(
	    		(void*)lp_group->base_reg->pchStr,
	    		'\0',
				(size_t)lp_group->base_reg->cbStrLen
				);
#if defined(_DEBUG)
		p_v = (void*) strncpy(
				(char*)mystring,
				lp_group->base_reg->pchStr,
				(size_t)lp_group->base_reg->cbStrLen
				);
#endif
		i_r = modbus_read_string_register(
				ctx,
				lp_group->base_reg->us_RegAddr,
				lp_group->i_size,
				lp_group->base_reg->pchStr
				);
#if defined(_DEBUG)
		p_v = (void*) strncpy(
				(char*)mystring,
				lp_group->base_reg->pchStr,
				(size_t)lp_group->base_reg->cbStrLen
				);
#endif
	}
	else
	{
		i_r = modbus_read_registers(
				ctx,
				(int) start_addr,
				(int) i_count,
				&Sola_Data[start_addr]
			);
#if defined(_DEBUG)
		i_r = (int)print_Sola_Data_registers(&Sola_Data[start_addr],i_count);
#endif
	}
	return (long)i_r;
}

long read_reg_groups(modbus_t * ctx,
		const LISTSOLAREGGROUPS_T * lp_list_groups)
{
	long l_r;
	int i_x;
	const SOLAREGGROUPLIST_T * lp_group_list;

	lp_group_list = lp_list_groups->lp_Sola_Reg_Group_List;
	for (i_x=0;i_x<lp_list_groups->i_size;i_x++)
	{
		l_r = read_reg_group(ctx,lp_group_list[i_x].lp_Sola_Reg_Group);
	}
	return (l_r = 0);
}

long Read_All_Reg_Groups(modbus_t *ctx)
{
	int i_x;
	volatile int local_die = 0;
	long l_r = 0L;
	l_r = read_reg_groups(ctx,&List_All_Groups);
	return l_r;
}

long Read_Alert_Log(modbus_t *ctx)
{
	int i_r = 0;
	long l_r = 0L;
	i_r = modbus_read_registers(ctx,
			(int) ui16_Alerts_Base_Addr,
			(int) ui16_Alerts_Reg_Cnt,
			&Sola_Data[ui16_Alerts_Base_Addr]);
	return (long)i_r;
}

long Read_Lockout_Log(modbus_t *ctx)
{
	int i_r = 0;
	int i_x = 0;
	long l_r = 0L;
	for (i_x = 0;(i_x < ui16_Lockouts_Blk_Cnt) && ((ui16_Lockouts_Base_Addr+(i_x*ui16_Lockouts_Blk_Reg_Cnt)) < Sola_Register_Count); ++i_x)
	{
		i_r = modbus_read_registers(ctx,
				(int) ui16_Lockouts_Base_Addr+(i_x*ui16_Lockouts_Blk_Reg_Cnt),
				(int) ui16_Lockouts_Blk_Reg_Cnt,
				&Sola_Data[ui16_Lockouts_Base_Addr+(i_x*ui16_Lockouts_Blk_Reg_Cnt)]);

	}
	return (long)i_r;
}

long Read_Trend_Groups(modbus_t *ctx)
{
	unsigned int ui_s;
	int i_x;
	volatile int local_die = 0;
	long l_r = 0L;
	l_r = read_reg_groups(ctx,&List_Trend_Groups);
	return l_r;
}

int sola_slave_id(modbus_t *ctx)
{
#if defined(_DEBUG)
	gint gi_r;
#endif
	volatile int local_die = 0;
    int i_r;
    int i_connected_unit_ID = 0;
    int i_probing_unit_ID = 1;
    int nb_points;
    int rc;
    void *p_v;
    uint8_t tab_rp_bits[UT_BITS_NB* sizeof(uint8_t)];


    /* Allocate and initialize the memory to store the bits */
    p_v = memset(tab_rp_bits, 0, sizeof(tab_rp_bits));

#if defined(_DEBUG)
	gi_r = g_printf("Report slave ID: \n");
#endif

    /* tab_rp_bits is used to store bytes */
    while ((0 == i_connected_unit_ID) && (i_probing_unit_ID <= ui8_MAX_SLAVE_ID))
    {
		pthread_mutex_lock(&poll_mutex);
		local_die = die;
		pthread_mutex_unlock(&poll_mutex);
		if (local_die)
		{
			break;
		}
       rc = modbus_report_slave_id(ctx, tab_rp_bits);
       if (rc == -1)
       {
#if defined(_DEBUG)
    	   gi_r = g_printf("No slave at ID %d\n", i_probing_unit_ID);
#endif
          modbus_set_slave(ctx, ++i_probing_unit_ID);
       }
       else
       {
          i_connected_unit_ID = i_probing_unit_ID;
          break;
       }
       sleep(1);
    }

    /* Slave ID is an arbitrary number for libmodbus */
#if defined(_DEBUG)
	i_r = (i_connected_unit_ID > 0) ? g_printf("OK Slave ID is %d\n", i_connected_unit_ID) : printf("Slave ID FAILED\n");
#endif

    return i_connected_unit_ID;
}

void * poll_thread(void * parm)
{
	bool b_r = false;
	unsigned int ui_s;
	int i_r;
	int i_x;
	long l_r;
	const SOLAREGGROUPLIST_T * p_lrg;
	volatile int local_die = 0;
	sigset_t sigs;
	modbus_t *ctx = NULL;

	sigemptyset(&sigs);
	sigaddset(&sigs, SIGINT);
	sigaddset(&sigs, SIGTERM);

	if(pthread_sigmask(SIG_BLOCK, &sigs, NULL) != 0)
	{
		i_r = fprintf(stderr,"pthread_sigmask() failed\n");
		return NULL;
	}




		while (ctx == NULL)
		{
			ctx = modbus_new_rtu("/dev/ttyUSB0", 38400, 'N', 8, 1);
			if (NULL == ctx)
			{
				i_r = fprintf(stderr, "Unable to allocate libmodbus context\n");
				ui_s = sleep(3);
			}
		}

		modbus_set_debug(ctx, FALSE);
		modbus_set_error_recovery(ctx,
				(modbus_error_recovery_mode)(MODBUS_ERROR_RECOVERY_LINK |
						MODBUS_ERROR_RECOVERY_PROTOCOL));

		while (modbus_connect(ctx) == -1)
		{
			i_r = fprintf(stderr, "modbus_connect() connection failed: %s\n",modbus_strerror(errno));
			fprintf(stderr,"Sleeping 3 seconds...\n");
			ui_s = sleep(3);
		}

		i_r = modbus_set_slave(ctx,(int)g_unit_id);



		g_connected_unit_ID = 0;
		while (!local_die && (0 == g_connected_unit_ID))
		{
			pthread_mutex_lock(&poll_mutex);
			local_die = die;
			pthread_mutex_unlock(&poll_mutex);
			if (local_die)
			{
				break;
			}
			i_r = sola_slave_id(ctx);
			pthread_mutex_lock(&poll_mutex);
			g_connected_unit_ID = (uint8_t)i_r;
			pthread_mutex_unlock(&poll_mutex);
		}

/* Get all registers */

	l_r = Read_All_Reg_Groups(ctx);

/* Get alert log */

	l_r = Read_Alert_Log(ctx);

/* Get Lockout history log */

	l_r = Read_Lockout_Log(ctx);

/* Poll until commanded to refresh connection */

	while(!local_die)
	{
		pthread_mutex_lock(&poll_mutex);
		local_die = die;
		pthread_mutex_unlock(&poll_mutex);
		if (local_die)
		{
			break;
		}
		l_r = Read_Trend_Groups(ctx);
		b_r = Check_Status_Change(ctx);
		b_r = Check_Configuration_Change(ctx);
		ui_s = sleep(1);
	}


	/* Close the connection */
	modbus_close(ctx);
	modbus_free(ctx);

	return NULL;
}

#if 0
DWORD WINAPI CommThread(LPVOID lpParam)
{
	HANDLE hEvents[NUMPROPPAGES+1];
	HANDLE hStartEvents[2];
	BOOL bResult;
	BOOL bSuccess = true;
	BOOL bStatusChange = true;
	BOOL bConfigChange = true;
	int i;
	int j;
	int nResult;
	int nEventCount;
	DWORD dwBytesRead;
	DWORD dwResult;
	HANDLE hCOM;
	HWND hParentWnd;
	HANDLE hQuitEvent;
	HANDLE hReadEvent;
	LPCRITICAL_SECTION lpCOMCritSect;
	LPCRITICAL_SECTION lpReadDataCritSect;
	unsigned char uc_MB_Address;
	unsigned short usBit;
	unsigned char MBMsg[512];
	union {	unsigned char SOLAResponse[512]; SOLAHRRESPONSE hr; SOLAIDRESPONSE SolaID; };
	PVOID lpvTemp;
	RTUCommResult rcr;
	LPSOLAIDRESPONSE lpSolaID = (LPSOLAIDRESPONSE)new SOLAIDRESPONSE;

	bCRCError = false;

	hCOM = ((LPRWTHREADPARMS) lpParam)->hCOM;
	hParentWnd = ((LPRWTHREADPARMS) lpParam)->hParentDlg;
	hQuitEvent = ((LPRWTHREADPARMS) lpParam)->hQuitEvent;
	hReadEvent = ((LPRWTHREADPARMS) lpParam)->hReadEvent;
	lpCOMCritSect = ((LPRWTHREADPARMS) lpParam)->pCommCritSect;
	lpReadDataCritSect= ((LPRWTHREADPARMS) lpParam)->pDataCritSect;
	uc_MB_Address = ((LPRWTHREADPARMS) lpParam)->uchSolaAddr;
	delete ((LPRWTHREADPARMS) lpParam);

	bResult = ::DuplicateHandle(::GetCurrentProcess(),g_hReadQuitEvent,GetCurrentProcess(),&hEvents[0],0,false,DUPLICATE_SAME_ACCESS);
	for ( j = 1; !g_bQuit && j < NUMPROPPAGES+1; j++ )
	{
		bResult = ::DuplicateHandle(::GetCurrentProcess(),g_hPageUpdEvents[j-1],GetCurrentProcess(),&hEvents[j],0,false,DUPLICATE_SAME_ACCESS);
	}

	bResult = ::DuplicateHandle(::GetCurrentProcess(),g_hReadQuitEvent,GetCurrentProcess(),&hStartEvents[0],0,false,DUPLICATE_SAME_ACCESS);
	bResult = ::DuplicateHandle(::GetCurrentProcess(),g_hStartRTUPollEvent,GetCurrentProcess(),&hStartEvents[1],0,false,DUPLICATE_SAME_ACCESS);
	dwResult = ::WaitForMultipleObjects(2,hStartEvents,false,INFINITE);
	if ( dwResult == WAIT_FAILED || dwResult == WAIT_TIMEOUT )
	{
		nResult = ::MessageBox(hParentWnd,_T("RTU poll thread failed, aborting"),szTitle,MB_OK);
		bResult = ::CloseHandle(hStartEvents[0]);
		bResult = ::CloseHandle(hStartEvents[1]);
		return 0;
	}
	if ( dwResult - WAIT_OBJECT_0 < sizeof(hStartEvents)/sizeof(HANDLE) )
	{
		if ( g_bQuit || (0 == (dwResult - WAIT_OBJECT_0)) )
		{
			bResult = ::CloseHandle(hStartEvents[0]);
			bResult = ::CloseHandle(hStartEvents[1]);
			return 0;
		}
	}

/* Begin main while() loop */
	while ( bSuccess && !g_bQuit && ((dwResult = ::WaitForSingleObject(hEvents[0],0)) == WAIT_TIMEOUT) )
	{
		uc_MB_Address = SOLAMBAddress;
		lpvTemp = ::SecureZeroMemory((PVOID)&g_SolaID,sizeof(g_SolaID));
		bStatusChange = true;
		bConfigChange = true;
		if ( !bSolaConnected )
		{
			bResult = ::PostMessage(hParentWnd,WM_APPSOLACONNECTING,(WPARAM)0,(LPARAM)&g_SolaID);
		}
/*		while ( !g_bQuit && bSuccess && !bSolaConnected )*/
		if ( !g_bQuit && bSuccess && !bSolaConnected )
		{
			bSuccess = (HardError != GetSolaID(hParentWnd,hCOM,uc_MB_Address,&g_SolaID));
			bSolaConnected = (g_SolaID.SolaID != 0);
			::EnterCriticalSection(&gTimeCritSect);
			g_dwConnectTime = 0L;
			::LeaveCriticalSection(&gTimeCritSect);
			::EnterCriticalSection(&gCOMCritSect);
			g_dwTotalCRCErrors = 0L;
			g_dwTotalRcvd = g_dwTotalSent = 0L;
			::LeaveCriticalSection(&gCOMCritSect);
		}

		if ( bSuccess && !g_bQuit && bSolaConnected )
		{
			bResult = ::PostMessage(hParentWnd,WM_APPSOLAIDUPD,(WPARAM)0,(LPARAM)&g_SolaID);
			bResult = ::PostMessage(hParentWnd,WM_APPDATAUPDSTART,(WPARAM)0,(LPARAM)0);
		}

/* Get all registers */
		if ( bSuccess && !g_bQuit && bSolaConnected )
		{
			dwTicksLastData = ::GetTickCount();
			bSuccess = (HardError != ReadSolaMap(hParentWnd,hCOM,uc_MB_Address,pcAllSolaMaps));
		}

/* Get alert log */
		if ( bSuccess && !g_bQuit && bSolaConnected )
		{
			bSuccess = (HardError != ReadSolaAlerts(hParentWnd,hCOM,uc_MB_Address,pcAlertLog));
		}

/* Get Lockout history log */
		if ( bSuccess && !g_bQuit && bSolaConnected )
		{
			bSuccess = (HardError != ReadSolaLockouts(hParentWnd,hCOM,uc_MB_Address,pcLockoutLog));
		}

		if ( bSuccess && !g_bQuit && bSolaConnected )
		{
			bResult = ::PostMessage(hParentWnd,WM_APPSOLAIDUPD,(WPARAM)0,(LPARAM)&g_SolaID);
		}

/* Poll until commanded to refresh connection or quit */
		while ( !g_bQuit && bSuccess && bSolaConnected && ((dwResult = ::WaitForSingleObject(hEvents[0],0)) == WAIT_TIMEOUT) )
		{
			::EnterCriticalSection(&gRWDataCritSect);
			nEventCount = g_nActiveTrendPages + (g_nActiveStatusPages*bStatusChange) + (g_nActiveConfigPages*bConfigChange);
			for ( i = 0; !g_bQuit && i < NUMPROPPAGES; i++ )
			{
				if ( g_lpPageDataEvents[i].typePage == TrendPage )
				{
					bResult = ::SetEvent(g_lpPageDataEvents[i].hEvent);
				}
				if ( bStatusChange && g_lpPageDataEvents[i].typePage == StatusPage )
				{
					bResult = ::SetEvent(g_lpPageDataEvents[i].hEvent);
				}
				if ( bConfigChange && g_lpPageDataEvents[i].typePage == ConfigPage )
				{
					bResult = ::SetEvent(g_lpPageDataEvents[i].hEvent);
				}
			}
			::LeaveCriticalSection(&gRWDataCritSect);

/* Always get dynamic trend data */
			if ( bSuccess && !g_bQuit && bSolaConnected )
			{
				rcr = ReadSolaMap(hParentWnd,hCOM,uc_MB_Address,pcTrendMaps);
				bSuccess = (HardError != rcr);
				dwTicksLastData = ((rcr == NoError) ? ::GetTickCount() : dwTicksLastData);
			}

/* Check if there's a status update */
			bStatusChange = false;
			usBit = 1;
			for ( i = 0; !g_bQuit && bSuccess && i < pcStatusChangeCodes->GetSize(); i++ )
			{
				if ( pcStatusChangeCodes->ItemBitMask(i) & pcSystemStatus->GetValue((int)0) )
				{
					bStatusChange = true;
					if ( i == 1 )
					{
						i = i;
					}
					if ( bSuccess && pcStatusChangeCodes->SolaMBMap(i) != NULL )
					{
						bSuccess = (HardError != ReadSolaMap(hParentWnd,hCOM,uc_MB_Address,pcStatusChangeCodes->SolaMBMap(i)));
					}
					if ( bSuccess && pcStatusChangeCodes->SolaAlertLog(i) != NULL )
					{
						bSuccess = (HardError != ReadSolaAlerts(hParentWnd,hCOM,uc_MB_Address,pcAlertLog));
					}
					if ( bSuccess && pcStatusChangeCodes->SolaLockoutLog(i) != NULL )
					{
						bSuccess = (HardError != ReadSolaLockouts(hParentWnd,hCOM,uc_MB_Address,pcLockoutLog));
					}
				}
				usBit <<= 1;
			}

/* Check if there's a configuration update. */
/* System ID and Access has to be handled separately because of string */
/* values. */
			bConfigChange = false;
			usBit = 1;
			if ( bSuccess && usBit & pcSystemStatus->GetValue((int)1) )
			{
				bConfigChange = true;
				bSuccess = (HardError != ReadSolaMap(hParentWnd,hCOM,uc_MB_Address,pcSystemIDMaps));
			}

			for ( i = 0; !g_bQuit && bSuccess && i < pcConfigChangeCodes->GetSize() && pcSystemStatus->GetValue((int)1); i++ )
			{
				if ( pcConfigChangeCodes->ItemBitMask(i) & pcSystemStatus->GetValue((int)1) )
				{
#if _DEBUG
					if ( 0x0001 & pcConfigChangeCodes->ItemBitMask(i) )
					{
						i = i;
					}
					if ( 0x0002 & pcConfigChangeCodes->ItemBitMask(i) )
					{
						i = i;
					}
					if ( 0x0800 & pcConfigChangeCodes->ItemBitMask(i) )
					{
						i = i;
					}
#endif
					bConfigChange = true;
					if ( pcConfigChangeCodes->SolaMBMap(i) != NULL )
					{
						bSuccess = (HardError != ReadSolaMap(hParentWnd,hCOM,uc_MB_Address,pcConfigChangeCodes->SolaMBMap(i)));
					}
				}
				usBit <<= 1;
			}

			::EnterCriticalSection(&gRWDataCritSect);
			while ( !g_bQuit && bSuccess && !g_MBSndRcvReqQ.empty() )
			{
				i = 0;
				while ( !g_bQuit && *g_MBSndRcvReqQ.front().ppchToSnd < *g_MBSndRcvReqQ.front().ppchEndSnd && *g_MBSndRcvReqQ.front().ppchToSnd < g_MBSndRcvReqQ.front().pchSndBuf + g_MBSndRcvReqQ.front().nSndBufSize  )
				{
					MBMsg[i++] = *(*g_MBSndRcvReqQ.front().ppchToSnd)++;
				}
				bSuccess = (HardError != MBWriteRead(hParentWnd,hCOM,MBMsg,i,g_MBSndRcvReqQ.front().pchRcvBuf,g_MBSndRcvReqQ.front().nRcvBufSize,&dwBytesRead));
				*g_MBSndRcvReqQ.front().ppchEndRcv = g_MBSndRcvReqQ.front().pchRcvBuf + dwBytesRead;
				bResult = ::PostMessage(g_MBSndRcvReqQ.front().hPage,g_MBSndRcvReqQ.front().nMsg,(WPARAM)3,(LPARAM) 0);
				g_MBSndRcvReqQ.pop();
			}
			::LeaveCriticalSection(&gRWDataCritSect);
			bSolaConnected = ((::GetTickCount() - dwTicksLastData) < SOLAREADSDTO);
			dwResult = ::WaitForSingleObject(g_hReSyncReqEvent,0);
			bSuccess = ((WAIT_FAILED != dwResult) && bSuccess);
			bSolaConnected = ((WAIT_FAILED != dwResult) && (WAIT_TIMEOUT == dwResult)) ? bSolaConnected : false;
		} /* end while ( !g_bQuit && bSuccess && bSolaConnected && ((dwResult = ::WaitForSingleObject(hEvents[0],0)) == WAIT_TIMEOUT) ) */
	} /* End of the main while() loop */

	for ( j = 0; j < sizeof(hEvents)/sizeof(HANDLE); j++ )
	{
		bResult = ::CloseHandle(hEvents[j]);
	}
	if ( !bSuccess )
	{
//		::DebugBreak();
		bSolaConnected = false;
		bResult = ::PostMessage(hParentWnd,WM_APPSOLAPOLLABORT,(WPARAM)0,(LPARAM)0);
	}

	return 0;
}


RTUCommResult GetSolaID(HWND& hwnd,HANDLE& hCOM,unsigned char uc_mb_addr,LPSOLAIDRESPONSE lpSolaID)
{
	RTUCommResult rcr = HardError;
	BOOL bSuccess = true;
	BOOL bBusQuiet = true;
	unsigned char SOLAIDRequest[2];
	int i;
	union {unsigned char SOLAResponse[512]; HOLDINGREG hr; SOLAIDRESPONSE SolaID;};
	DWORD dwBytesWritten = 0;
	DWORD dwBytesRead = 0;
	PVOID lpvTemp;

	bSuccess = (HardError != (rcr = IsBusQuiet(hCOM)));
	if ( bSuccess )
	{
		bBusQuiet = (rcr == Timeout);
	}
	if ( bBusQuiet && bSuccess )
	{
		lpvTemp = ::SecureZeroMemory((PVOID)SOLAResponse,sizeof(SOLAResponse));
		SOLAIDRequest[0] = uc_mb_addr;
		SOLAIDRequest[1] = 0x11;
		rcr = MBWriteRead(hwnd,hCOM,SOLAIDRequest,sizeof(SOLAIDRequest)/sizeof(unsigned char),SOLAResponse,sizeof(SOLAResponse),&dwBytesRead);
		bSuccess = (rcr != HardError);
	}
	if ( bBusQuiet && (rcr == NoError) && (dwBytesRead > 0) && (SolaID.ByteCount == 0x26) )
	{
		lpSolaID->SolaAddr = SolaID.SolaAddr;
		lpSolaID->FunctionCode = SolaID.FunctionCode;
		lpSolaID->SolaID = SolaID.SolaID;
		lpSolaID->RunIndicator = SolaID.RunIndicator;
		for ( i = 0; i < sizeof(SolaID.BurnerName); i++ )
		{
			*((lpSolaID->BurnerName)+i) = SolaID.BurnerName[i];
		}
		for ( i = 0; i < sizeof(SolaID.OSNumber); i++ )
		{
			*((lpSolaID->OSNumber)+i) = SolaID.OSNumber[i];
		}
		dwTicksLastData = ::GetTickCount();
	}
	return rcr;
}

RTUCommResult IsBusQuiet(HANDLE& hCOM)
{
	RTUCommResult rcr = HardError;
//	COMMTIMEOUTS OldCommTimeouts;
//	COMMTIMEOUTS CommTimeouts;
	unsigned char uchBuf[512];
	PVOID lpVoid;
	DWORD dwBytesRead = 0;
	BOOL bSuccess = true;

	::EnterCriticalSection(&gCOMCritSect);
	bSuccess = ::PurgeComm(hCOM,PURGE_RXCLEAR);
	rcr = ((bSuccess) ? NoError : HardError);
	if ( bSuccess )
	{
		lpVoid = ::SecureZeroMemory((PVOID)uchBuf,(SIZE_T)sizeof(uchBuf));
		rcr = MBRead(hCOM,uchBuf,sizeof(uchBuf)/sizeof(char),&dwBytesRead);
		bSuccess = (rcr != HardError);
	}
	::LeaveCriticalSection(&gCOMCritSect);
	return rcr;
}

RTUCommResult ReadSolaMap(HWND& hwnd,HANDLE& hCOM,unsigned char ucMBAddr,CSolaMBMaps* lpMaps)
{
	RTUCommResult rcr = HardError;
	int j;
	union {unsigned char SOLAResponse[512];SOLAHRRESPONSE hr;SOLAIDRESPONSE SolaID;};

	for ( j = 0; !g_bQuit && j < lpMaps->GetSize(); j++ )
	{
		rcr = ReadSolaMap(hwnd,hCOM,ucMBAddr,lpMaps->GetLPMap(j));
	}
	return (RTUCommResult)rcr;
}

RTUCommResult ReadSolaMap(HWND& hwnd,HANDLE& hCOM,unsigned char ucMBAddr,CSolaMBMap* lpMap)
{
	BOOL bOkCRC;
	BOOL bSuccess;
	RTUCommResult rcr = HardError;
	CSolaMBMap::LPSOLAMBMAP lpSolaRequest = NULL;
	DWORD dwBytesRead;
	int j;
	int nOffset;
	unsigned char MBMsg[512];
	unsigned char uchRespLo;
	unsigned char uchRespHi;
	U32 u32Value;
	U32 u32Ret;
	union {unsigned char SOLAResponse[512];SOLAHRRESPONSE hr;SOLAIDRESPONSE SolaID;};
	short sRegCount;
	PVOID lpvTemp;

	if ( NULL != lpMap->GetLPMap((int)0) )
	{
		lpSolaRequest = lpMap->GetLPMap((int)0);
		sRegCount = (short)lpMap->GetRegRequestLen();
	}
	if ( NULL != lpMap->GetLPU32Map((int)0) )
	{
		sRegCount = (short)lpMap->GetU32RegTotal();
	}
	MBMsg[0] = ucMBAddr;
	MBMsg[1] = lpMap->GetFuncCode((int)0);
	MBMsg[2] = (lpMap->GetStartRegAddr((int)0) >> 8) & 0x00ff;
	MBMsg[3] = lpMap->GetStartRegAddr((int)0) & 0x00ff;
	MBMsg[4] = (sRegCount >> 8) & 0x00ff;
	MBMsg[5] = sRegCount & 0x00ff;
	bSuccess = (HardError != (rcr = MBWriteRead(hwnd,hCOM,MBMsg,6,SOLAResponse,sizeof(SOLAResponse),&dwBytesRead)));
	bOkCRC = false;
	if ( (rcr == NoError) && (dwBytesRead > 0) )
	{
		for ( nOffset = 0; nOffset < lpMap->GetRegGroupSize(); nOffset++ )
		{
			switch (lpMap->GetType((int)nOffset))
			{
			case CSolaMBMap::Novalue:
				break;
			case CSolaMBMap::DupStringValue:
			case CSolaMBMap::Stringvalue:
				if (((lpMap->GetType((int)nOffset) == CSolaMBMap::Stringvalue) ||
					(lpMap->GetType((int)nOffset) == CSolaMBMap::DupStringValue)) &&
					(lpMap->GetStr((int)nOffset) != NULL) )
				{
					lpvTemp = (PVOID)lpMap->SetStr((int)nOffset,&SOLAResponse[sizeof(hr)],hr.cbByteCount);
				}
				break;
			case CSolaMBMap::Unsigned32:
				j = nOffset;
				u32Value = SOLAResponse[sizeof(hr)+(j*4)+3] +
					(SOLAResponse[sizeof(hr)+(j*4)+2]*256L) +
					(SOLAResponse[sizeof(hr)+(j*4)+1]*65536L) +
					(SOLAResponse[sizeof(hr)+(j*4)]*16777216L);
				u32Ret = lpMap->SetU32Value((int)nOffset,u32Value);
				break;
			default:
				j = nOffset;
				uchRespLo = SOLAResponse[sizeof(hr)+(j*2)+1];
				uchRespHi = SOLAResponse[sizeof(hr)+(j*2)];
				lpMap->SetValue((int)nOffset,uchRespLo+(256*uchRespHi));
				break;
			}
		}
	}

	return (RTUCommResult)rcr;
}

RTUCommResult ReadSolaAlerts(HWND& hwnd,HANDLE& hCOM,unsigned char ucMBAddr,CSolaAlert* lpLog)
{
	BOOL bOkCRC;
	BOOL bSuccess;
	RTUCommResult rcr = HardError;
	LPSOLAALERT lpAlertRecord;
	DWORD dwBytesRead;
	int i;
	unsigned char MBMsg[512];
	union {unsigned char SOLAResponse[512];SOLAHRRESPONSE hr;SOLAIDRESPONSE SolaID;};
	for ( i = 0; !g_bQuit && i < lpLog->GetSize(); i++ )
	{
		lpAlertRecord = pcAlertLog->GetLPMap(i);
		MBMsg[0] = ucMBAddr;
		MBMsg[1] = lpAlertRecord->uchFuncCode;
		MBMsg[2] = (lpAlertRecord->usStartRegAddr >> 8) & 0x00ff;
		MBMsg[3] = lpAlertRecord->usStartRegAddr & 0x00ff;
		MBMsg[4] = (lpAlertRecord->usRegCount >> 8) & 0x00ff;
		MBMsg[5] = lpAlertRecord->usRegCount & 0x00ff;
		bSuccess = (HardError != (rcr = MBWriteRead(hwnd,hCOM,MBMsg,6,SOLAResponse,sizeof(SOLAResponse),&dwBytesRead)));
		bOkCRC = false;
		if ( (rcr == NoError) && (dwBytesRead > 0) )
		{
			lpAlertRecord->pAlertRecord->aa.usAlertCode =  (256*SOLAResponse[sizeof(hr)]) + SOLAResponse[sizeof(hr)+1];
				lpAlertRecord->pAlertRecord->aa.ulCycle = (256*256*256*SOLAResponse[sizeof(hr)+2]) + (256*256*SOLAResponse[sizeof(hr)+3]) +
				(256*SOLAResponse[sizeof(hr)+4]) + (SOLAResponse[sizeof(hr)+5]);
			lpAlertRecord->pAlertRecord->aa.ulHours = (256*256*256*(SOLAResponse[sizeof(hr)+6])) + (256*256*SOLAResponse[sizeof(hr)+7]) +
				(256*SOLAResponse[sizeof(hr)+8]) + (256*256*256*SOLAResponse[sizeof(hr)+9]);
			lpAlertRecord->pAlertRecord->aa.uchCount =  SOLAResponse[sizeof(hr)+11];
		}
	}
	return rcr;
}

RTUCommResult ReadSolaLockouts(HWND& hwnd,HANDLE& hCOM,unsigned char ucMBAddr,CSolaLockout* lpLog)
{
	RTUCommResult rcr = HardError;
	BOOL bOkCRC;
	BOOL bSuccess;
	LPSOLALOCKOUT lpLockoutRecord;
	DWORD dwBytesRead;
	int i;
	unsigned char MBMsg[512];
	union {unsigned char SOLAResponse[512];SOLAHRRESPONSE hr;SOLAIDRESPONSE SolaID;};

	for ( i = 0; !g_bQuit && i < pcLockoutLog->GetSize(); i++ )
	{
		lpLockoutRecord = lpLog->GetLPMap(i);
		MBMsg[0] = ucMBAddr;
		MBMsg[1] = lpLockoutRecord->uchFuncCode;
		MBMsg[2] = (lpLockoutRecord->usStartRegAddr >> 8) & 0x00ff;
		MBMsg[3] = lpLockoutRecord->usStartRegAddr & 0x00ff;
		MBMsg[4] = (lpLockoutRecord->usRegCount >> 8) & 0x00ff;
		MBMsg[5] = lpLockoutRecord->usRegCount & 0x00ff;
		bSuccess = (HardError != (rcr = MBWriteRead(hwnd,hCOM,MBMsg,8,SOLAResponse,sizeof(SOLAResponse),&dwBytesRead)));
		bOkCRC = false;
		if ( (rcr == NoError) && (dwBytesRead > 0) )
		{
			lpLockoutRecord->pLockoutUnion->slr.usLockoutCode = (256*SOLAResponse[sizeof(hr)]) + SOLAResponse[sizeof(hr)+1];
			lpLockoutRecord->pLockoutUnion->slr.usAnnunciatorFirstOut = (256*SOLAResponse[sizeof(hr)+2]) + SOLAResponse[sizeof(hr)+3];
			lpLockoutRecord->pLockoutUnion->slr.usBurnerControlState = (256*SOLAResponse[sizeof(hr)+4]) + SOLAResponse[sizeof(hr)+5];
			lpLockoutRecord->pLockoutUnion->slr.usSequenceTime = (256*SOLAResponse[sizeof(hr)+6]) + SOLAResponse[sizeof(hr)+7];
			lpLockoutRecord->pLockoutUnion->slr.ulCycle = (16777216*SOLAResponse[sizeof(hr)+8]) + (65536*SOLAResponse[sizeof(hr)+9]) +
				(256*SOLAResponse[sizeof(hr)+10]) + (SOLAResponse[sizeof(hr)+11]);
			lpLockoutRecord->pLockoutUnion->slr.ulHours = (16777216*SOLAResponse[sizeof(hr)+12]) + (65536*SOLAResponse[sizeof(hr)+13]) +
				(256*SOLAResponse[sizeof(hr)+14]) + (SOLAResponse[sizeof(hr)+15]);
			lpLockoutRecord->pLockoutUnion->slr.usIO = (256*SOLAResponse[sizeof(hr)+16]) + SOLAResponse[sizeof(hr)+17];
			lpLockoutRecord->pLockoutUnion->slr.usAnnunciator = (256*SOLAResponse[sizeof(hr)+18]) + SOLAResponse[sizeof(hr)+19];
			lpLockoutRecord->pLockoutUnion->slr.usOutletTemperature = (256*SOLAResponse[sizeof(hr)+20]) + SOLAResponse[sizeof(hr)+21];
			lpLockoutRecord->pLockoutUnion->slr.usInletTemperature = (256*SOLAResponse[sizeof(hr)+22]) + SOLAResponse[sizeof(hr)+23];
			lpLockoutRecord->pLockoutUnion->slr.usDHWTemperature = (256*SOLAResponse[sizeof(hr)+24]) + SOLAResponse[sizeof(hr)+25];
			lpLockoutRecord->pLockoutUnion->slr.usODTemperature = (256*SOLAResponse[sizeof(hr)+26]) + SOLAResponse[sizeof(hr)+27];
			lpLockoutRecord->pLockoutUnion->slr.usStackTemperature = (256*SOLAResponse[sizeof(hr)+28]) + SOLAResponse[sizeof(hr)+29];
			lpLockoutRecord->pLockoutUnion->slr.us4to20mAInput = (256*SOLAResponse[sizeof(hr)+30]) + SOLAResponse[sizeof(hr)+31];
			lpLockoutRecord->pLockoutUnion->slr.ucFaultData0 = SOLAResponse[sizeof(hr)+32];
			lpLockoutRecord->pLockoutUnion->slr.ucFaultData1 = SOLAResponse[sizeof(hr)+33];
		}
	}
	return rcr;
}


#endif

int start_polling(void)
{
	unsigned int ui_s;
	int i_r = -1;
	pthread_t pt_poll_thread;

	if(SIG_ERR  != signal(SIGINT, INThandler))
	{
		i_r = pthread_create(
				&pt_poll_thread,
		       NULL,
		       poll_thread,
		       (void *) NULL);
	}


	return i_r;
}

