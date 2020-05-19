/*
 * Sola_Client.c
 *
 *  Created on: May 16, 2019
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
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>


#include "modbus.h"
#include "Reg_Groups.h"
#include "callbacks.h"

/* Global variables */
volatile int die = 0;
uint16_t Sola_Data[Sola_Register_Count];
pthread_mutex_t poll_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t screen_update_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t screen_update_cond = PTHREAD_COND_INITIALIZER;
GtkWidget   *padlock_locked;
GtkWidget   *padlock_unlocked;
bool image_toggle = false;


GtkWidget	*window;
GtkWidget	*fixed_01;
GtkWidget	*stack_01;
GtkWidget	*switcher_01;
GtkWidget   *stk_01_fxd_01;
GtkWidget   *stk_01_fxd_01_frm;
GtkWidget   *stk_01_fxd_02;
GtkWidget   *stk_01_fxd_02_frm;
GtkWidget   *stk_01_fxd_03;
GtkWidget   *stk_01_fxd_03_frm;
GtkWidget   *stk_01_fxd_04;
GtkWidget   *stk_01_fxd_04_frm;
GtkWidget   *stk_01_fxd_05;
GtkWidget   *stk_01_fxd_05_frm;
GtkBuilder	*builder;
GtkWidget	*toggle1;
GtkWidget	*lvl000B;

int main (int argc, char** argv)
{
	int i_r = 0;
	int status;
	void * p_v;

	p_v = memset(Sola_Data,(int)0,sizeof(Sola_Data));

	gtk_init(&argc, &argv); // init Gtk

	//---------------------------------------------------------------------
	// establish contact with xml code used to adjust widget settings
	//---------------------------------------------------------------------

	builder = gtk_builder_new_from_file ("./src/Sola_Client.glade");
	assert(NULL != builder);
	window = GTK_WIDGET(gtk_builder_get_object(builder, "wnd_01"));

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_builder_connect_signals(builder, NULL);

	fixed_01 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed_01"));
	stack_01 = GTK_WIDGET(gtk_builder_get_object(builder, "stack_01"));
	switcher_01 = GTK_WIDGET(gtk_builder_get_object(builder, "switcher_01"));
	stk_01_fxd_01 = GTK_WIDGET(gtk_builder_get_object(builder, "stk_01_fxd_01"));
	stk_01_fxd_01_frm = GTK_WIDGET(gtk_builder_get_object(builder, "stk_01_fxd_01_frm"));
	stk_01_fxd_02 = GTK_WIDGET(gtk_builder_get_object(builder, "stk_01_fxd_02"));
	stk_01_fxd_02_frm = GTK_WIDGET(gtk_builder_get_object(builder, "stk_01_fxd_02_frm"));
	stk_01_fxd_03 = GTK_WIDGET(gtk_builder_get_object(builder, "stk_01_fxd_03"));
	stk_01_fxd_03_frm = GTK_WIDGET(gtk_builder_get_object(builder, "stk_01_fxd_03_frm"));
	stk_01_fxd_04 = GTK_WIDGET(gtk_builder_get_object(builder, "stk_01_fxd_04"));
	stk_01_fxd_04_frm = GTK_WIDGET(gtk_builder_get_object(builder, "stk_01_fxd_04_frm"));
	stk_01_fxd_05 = GTK_WIDGET(gtk_builder_get_object(builder, "stk_01_fxd_05"));
	stk_01_fxd_05_frm = GTK_WIDGET(gtk_builder_get_object(builder, "stk_01_fxd_05_frm"));
	toggle1 = GTK_WIDGET(gtk_builder_get_object(builder, "toggle1"));
	lvl000B = GTK_WIDGET(gtk_builder_get_object(builder, "lvl000B"));

	padlock_locked = gtk_image_new_from_file("./src/padlock_locked_32x32.png");
	padlock_unlocked = gtk_image_new_from_file("./src/padlock_unlocked_32x32.png");
	g_object_ref(padlock_locked);
	g_object_ref(padlock_unlocked);
	gtk_button_set_image(toggle1,padlock_locked);
	gtk_button_set_always_show_image (toggle1,true);

	gtk_widget_show(window);
	g_idle_add(window_is_showing,builder);
	gtk_main();

	g_object_unref(padlock_locked);
	g_object_unref(padlock_unlocked);


	return (status = EXIT_SUCCESS);
}
