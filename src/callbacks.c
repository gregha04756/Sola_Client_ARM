/*
 * callbacks.c
 *
 *  Created on: Jan. 23, 2020
 *      Author: greg
 */

#include "callbacks.h"


gboolean window_is_showing(GtkBuilder *builder)
{
	int i_r;
	i_r = start_polling();
	i_r = start_screen_update();
	return FALSE;
}


void INThandler(int signum)
{
    signal(signum, SIG_IGN);
	fprintf(stderr, "Shutting down by signal\n");
	pthread_mutex_lock(&poll_mutex);
	die = 1;
	pthread_mutex_unlock(&poll_mutex);
}

void	on_toggle1_toggled(GtkToggleButton *b)
{
	gboolean T = gtk_toggle_button_get_active(b);
	assert(NULL != padlock_locked);
	assert(NULL != padlock_unlocked);
	if (T)
	{
		gtk_button_set_image(b,padlock_unlocked);
	}
	else
	{
		gtk_button_set_image(b,padlock_locked);
	}
}

#if 0
void	on_button2_clicked (GtkButton *b)
{
/*	old_image = gtk_button_get_image(b);
	assert(NULL != old_image); */
	assert(NULL != padlock_locked);
	assert(NULL != padlock_unlocked);
	if (image_toggle)
	{
		gtk_button_set_image(b,padlock_locked);
	}
	if (!image_toggle)
	{
		gtk_button_set_image(b,padlock_unlocked);
	}
	image_toggle = !image_toggle;
}
#endif
