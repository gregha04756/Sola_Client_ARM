/*
 * callbacks.h
 *
 *  Created on: Jan. 23, 2020
 *      Author: greg
 */

#ifndef CALLBACKS_H_
#define CALLBACKS_H_

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

extern volatile int die;
extern uint16_t Sola_Data[];
extern pthread_mutex_t poll_mutex;
extern pthread_mutex_t screen_update_mutex;
extern pthread_cond_t screen_update_cond;
extern GtkWidget   *padlock_locked;
extern GtkWidget   *padlock_unlocked;
extern bool image_toggle;

extern int start_polling(void);
extern int start_screen_update(void);

extern gboolean window_is_showing(GtkBuilder *builder);
extern void INThandler(int signum);
extern void	on_toggle1_toggled(GtkToggleButton *b);
extern void * screen_update_fn(void * parm);
extern gboolean screen_update_cb(void * p_v);


#endif /* CALLBACKS_H_ */
