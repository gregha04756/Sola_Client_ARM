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


void * screen_update_thread(void * parm)
{
#if defined(_DEBUG)
	uint8_t mystring[21] = {'\0'};
#endif
	unsigned int ui_s;
	int i_r;
	int i_x;
	long l_r;
	void *p_v;
	volatile int local_die = 0;
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


	while(!local_die)
	{
		i_r = pthread_mutex_lock(&poll_mutex);
		local_die = die;
		i_r = pthread_mutex_unlock(&poll_mutex);
		if (!local_die)
		{
			page_update(&Summary_Page);
			ui_s = sleep(1);
#if 0
			p_v = memset(wname,(int)0,sizeof(wname));
			i_r = g_sprintf(wname,"txt%04d",ui_addr);
			p_v = memset(wvalue,(int)0,sizeof(wvalue));
			i_x = Sola_Data[ui_addr];
			i_r = g_sprintf(wvalue,"%d",Sola_Data[ui_addr]);
			txt0006 = GTK_WIDGET(gtk_builder_get_object(builder, wname));
			gtk_label_set_text (GTK_LABEL(txt0006), (const gchar*)wvalue);
#if defined(_DEBUG)
		p_v = (void*) strncpy(
				mystring,
				Configuration_Groups[2].lp_Sola_Reg_Group->lp_Sola_Reg_list->lp_Sola_Reg->pchStr,
				(size_t)Configuration_Groups[2].lp_Sola_Reg_Group->lp_Sola_Reg_list->lp_Sola_Reg->cbStrLen
				);
#endif

			burner_name = GTK_WIDGET(gtk_builder_get_object(builder, (const gchar*)"burner_name"));
			gtk_label_set_text (GTK_LABEL(burner_name),
					(const gchar*)Configuration_Groups[2].lp_Sola_Reg_Group->lp_Sola_Reg_list->lp_Sola_Reg->pchStr);
#endif
		}
	}

	return NULL;
}


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

