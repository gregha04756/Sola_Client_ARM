/*
 * screen_update.c
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
#include <stddef.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include "modbus.h"

#include "Reg_Groups.h"
#include "Screen_Pages.h"

extern void page_update(SCREENPAGE_T * page);
extern uint16_t Sola_Data[];
extern volatile int die;
extern pthread_mutex_t poll_mutex;
extern GtkBuilder	*builder;


void * screen_update_fn(void * parm)
{
#if 0
	int i_r;
	int i_x;
	long l_r;
	void *p_v;
	GtkWidget   *txt0006;
	GtkWidget   *burner_name;
	gchar wname[10];
	gchar wvalue[10];
	uint16_t ui_addr = 0x0006;

	p_v = memset(wname,(int)0,sizeof(wname));
	i_r = g_sprintf(wname,"txt%04d",ui_addr);
	p_v = memset(wvalue,(int)0,sizeof(wvalue));
	i_x = Sola_Data[ui_addr];
	i_r = g_sprintf(wvalue,"%d",Sola_Data[ui_addr]);
#endif

	page_update(&Summary_Page);

	return NULL;
}

#if 0
int start_screen_update(void)
{
	int i_r;
	pthread_t pt_su_thread;

	i_r = pthread_create(
			&pt_su_thread,
			NULL,
			screen_update_thread,
			(void *) NULL);


	return i_r;
}
#endif
