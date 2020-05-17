/*
 * page_update.c
 *
 *  Created on: Dec. 10, 2019
 *      Author: greg
 */

#include <gtk/gtk.h>

#include <gtk/gtkx.h>

#include <stdint.h>
#include <stdbool.h>
#include <memory.h>
#include <string.h>
#include <assert.h>


#include "Reg_Groups.h"
#include "Reg_Refs_Extern.h"
#include "Screen_Pages.h"
#include "Sola_Defs_Consts.h"

extern uint16_t Sola_Data[];
extern volatile int die;
extern pthread_mutex_t poll_mutex;
extern GtkBuilder	*builder;


float TempVal (bool units,uint16_t temp)
{
	return ((((9.0*((float)temp))/50.0)+32.0)*(units == FAHRENHEITUNITS))+((((float)temp)/10.0)*(units == CELSIUSUNITS));
}

float HystVal (bool units,uint16_t temp)
{
	if ( units == FAHRENHEITUNITS )
	{
		return (9.0*((float)temp))/50.0;
	}
	return ((float)temp)/10.0;
}

gchar *get_multivalue_string(SOLAMULTIVALUE_T * mv_list,uint16_t ui16_size,uint16_t ui16_ix)
{
	uint16_t i_x;
	for (i_x = 0; i_x < ui16_size; i_x++)
	{
		if (ui16_ix == mv_list[i_x].i_value)
		{
			return (gchar*)mv_list[i_x].lp_String;
		}
	}
	return (gchar*)NULL;
}

void page_update(SCREENPAGE_T * page)
{
#if defined(_DEBUG)
	uint8_t mystring[21] = {'\0'};
#endif
	bool temperature_units;
	int i_r;
	int i_x;
	long l_r;
	void *p_v;
	uint16_t ui16_offset;
	uint16_t ui16_reg_addr;
	uint16_t ui16_value;
	uint16_t ui16_mv_list_size;
	uint16_t ui16_hh;
	uint16_t ui16_mm;
	uint16_t ui16_ss;
	float temperature_value;
	float decimal_value;
	gchar *mv_string = {'\0'};
	SOLAMULTIVALUE_T *mv_list;
	enum SolaType thistype;
	volatile int local_die = 0;
	GtkWidget   *widget_target;
	gchar wname[10] = {'\0'};
	gchar wvalue[10] = {'\0'};
	uint16_t ui_addr = 0x0006;

#if defined(_DEBUG)
	p_v = (void*) strncpy(
		mystring,
		Configuration_Groups[2].lp_Sola_Reg_Group->lp_Sola_Reg_list->lp_Sola_Reg->pchStr,
		(size_t)Configuration_Groups[2].lp_Sola_Reg_Group->lp_Sola_Reg_list->lp_Sola_Reg->cbStrLen
		);
#endif

	for (i_x = 0; i_x < page->count; ++i_x)
	{
		ui16_offset = page->p_Screen_Element_List[i_x].p_Screen_Element->offset;
		thistype = page->p_Screen_Element_List[i_x].p_Screen_Element->reg_group->lp_Sola_Reg_list[ui16_offset].lp_Sola_Reg->valuetype;
		ui16_reg_addr = page->p_Screen_Element_List[i_x].p_Screen_Element->reg_group->lp_Sola_Reg_list[ui16_offset].lp_Sola_Reg->us_RegAddr;
		assert(Sola_Register_Count > ui16_reg_addr);
		ui16_value = Sola_Data[ui16_reg_addr];
		switch(thistype)
		{
		case Novalue:
			break;
		case Numericvalue:
			p_v = memset(wname,(int)0,sizeof(wname));
			i_r = g_sprintf(wname,"txt%04X",ui16_reg_addr);
			p_v = memset(wvalue,(int)0,sizeof(wvalue));
			i_r = g_sprintf(wvalue,"%d",ui16_value);
			widget_target = GTK_WIDGET(gtk_builder_get_object(builder, wname));
			assert(NULL != widget_target);
			gtk_label_set_text (GTK_LABEL(widget_target), (const gchar*)wvalue);
			break;
		case Bitmask:
			break;
		case Digitalvalue:
			break;
		case Temperature:
			temperature_units = (bool)Sola_Data[Temperature_units.us_RegAddr];
			temperature_value = TempVal(temperature_units,ui16_value);
			i_r = g_sprintf(wname,"txt%04X",ui16_reg_addr);
			p_v = memset(wvalue,(int)0,sizeof(wvalue));
			i_r = (temperature_units == (bool)FAHRENHEITUNITS) ? \
					g_sprintf(wvalue,"%-.2f",temperature_value) : \
							g_sprintf(wvalue,"%-.2f",temperature_value);
			widget_target = GTK_WIDGET(gtk_builder_get_object(builder, wname));
			assert(NULL != widget_target);
			if (NULL != widget_target)
			{
				gtk_label_set_text (GTK_LABEL(widget_target), (const gchar*)wvalue);
			}
			i_r = g_sprintf(wname,"lvl%04X",ui16_reg_addr);
			widget_target = GTK_WIDGET(gtk_builder_get_object(builder, wname));
			if (NULL != widget_target)
			{
				gtk_level_bar_set_value  (GTK_LEVEL_BAR(widget_target), (gdouble)temperature_value);
			}
			break;
		case TemperatureSetpoint:
			break;
		case Setpointvalue:
			break;
		case Hysteresis:
			temperature_units = (bool)Sola_Data[Temperature_units.us_RegAddr];
			temperature_value = HystVal(temperature_units,ui16_value);
			i_r = g_sprintf(wname,"txt%04X",ui16_reg_addr);
			p_v = memset(wvalue,(int)0,sizeof(wvalue));
			i_r = (temperature_units == (bool)FAHRENHEITUNITS) ? \
					g_sprintf(wvalue,"%-.2f",temperature_value) : \
							g_sprintf(wvalue,"%-.2f",temperature_value);
			widget_target = GTK_WIDGET(gtk_builder_get_object(builder, wname));
			assert(NULL != widget_target);
			gtk_label_set_text (GTK_LABEL(widget_target), (const gchar*)wvalue);
			break;
		case Timevalue:
			ui16_hh = ui16_value/3600;
			ui16_mm = (ui16_value-(ui16_hh*3600))/60;
			ui16_ss = ui16_value-(ui16_hh*3600)-(ui16_mm*60);
			i_r = g_sprintf(wname,"txt%04X",ui16_reg_addr);
			p_v = memset(wvalue,(int)0,sizeof(wvalue));
			i_r = g_sprintf(wvalue,"%02d:%02d:%02d",ui16_hh,ui16_mm,ui16_ss);
			widget_target = GTK_WIDGET(gtk_builder_get_object(builder, wname));
			assert(NULL != widget_target);
			gtk_label_set_text (GTK_LABEL(widget_target), (const gchar*)wvalue);
			break;
		case Seconds:
			ui16_hh = ui16_value/3600;
			ui16_mm = (ui16_value-(ui16_hh*3600))/60;
			ui16_ss = ui16_value-(ui16_hh*3600)-(ui16_mm*60);
			i_r = g_sprintf(wname,"txt%04X",ui16_reg_addr);
			p_v = memset(wvalue,(int)0,sizeof(wvalue));
			i_r = g_sprintf(wvalue,"%02d:%02d:%02d",ui16_hh,ui16_mm,ui16_ss);
			widget_target = GTK_WIDGET(gtk_builder_get_object(builder, wname));
			assert(NULL != widget_target);
			gtk_label_set_text (GTK_LABEL(widget_target), (const gchar*)wvalue);
			break;
		case Minutes:
			break;
		case Hours:
			break;
		case SensorMultivalue:
			break;
		case Multivalue:
			mv_list = page->p_Screen_Element_List[i_x].p_Screen_Element->reg_group->lp_Sola_Reg_list[ui16_offset].lp_Sola_Reg->lp_mv_list;
/* Don't forget NDEBUG pre-processor definition to turn off assertions when not needed */
			assert(NULL != mv_list);
			ui16_mv_list_size = page->p_Screen_Element_List[i_x].p_Screen_Element->reg_group->lp_Sola_Reg_list[ui16_offset].lp_Sola_Reg->i_mv_list_size;
			assert(0 != ui16_mv_list_size);
			mv_string = (gchar*)get_multivalue_string(mv_list,ui16_mv_list_size,ui16_value);
			assert(NULL != mv_string);
			p_v = memset(wname,(int)0,sizeof(wname));
			i_r = g_sprintf(wname,"txt%04X",ui16_reg_addr);
			widget_target = GTK_WIDGET(gtk_builder_get_object(builder, wname));
			assert(NULL != widget_target);
			if (NULL != widget_target)
			{
				gtk_label_set_text (GTK_LABEL(widget_target), (const gchar*)mv_string);
			}
			break;
		case Stringvalue:
			mv_string = page->p_Screen_Element_List[i_x].p_Screen_Element->reg_group->lp_Sola_Reg_list[ui16_offset].lp_Sola_Reg->pchStr;
			assert(NULL != mv_string);
			p_v = memset(wname,(int)0,sizeof(wname));
			i_r = g_sprintf(wname,"txt%04X",ui16_reg_addr);
			widget_target = GTK_WIDGET(gtk_builder_get_object(builder, wname));
			assert(NULL != widget_target);
			if (NULL != widget_target)
			{
				gtk_label_set_text (GTK_LABEL(widget_target), (const gchar*)mv_string);
			}
			break;
		case Percentvalue:
			decimal_value = ((float)ui16_value)/10.0;
			p_v = memset(wname,(int)0,sizeof(wname));
			i_r = g_sprintf(wname,"txt%04X",ui16_reg_addr);
			p_v = memset(wvalue,(int)0,sizeof(wvalue));
			i_r = g_sprintf(wvalue,"%-6.1f",decimal_value);
			widget_target = GTK_WIDGET(gtk_builder_get_object(builder, wname));
			assert(NULL != widget_target);
			gtk_label_set_text (GTK_LABEL(widget_target), (const gchar*)wvalue);
			break;
		case Lockoutcode:
			break;
		case Holdcode:
			break;
		case Alertcode:
			break;
		case Alarmreason:
			break;
		case Alarmcode:
			break;
		case Fanspeed:
			break;
		case Decimal1pl:
			decimal_value = ((float)ui16_value)/10.0;
			p_v = memset(wname,(int)0,sizeof(wname));
			i_r = g_sprintf(wname,"txt%04X",ui16_reg_addr);
			p_v = memset(wvalue,(int)0,sizeof(wvalue));
			i_r = g_sprintf(wvalue,"%-6.1f",decimal_value);
			widget_target = GTK_WIDGET(gtk_builder_get_object(builder, wname));
			assert(NULL != widget_target);
			gtk_label_set_text (GTK_LABEL(widget_target), (const gchar*)wvalue);
			break;
		case Decimal2pl:
			decimal_value = ((float)ui16_value)/100.0;
			p_v = memset(wname,(int)0,sizeof(wname));
			i_r = g_sprintf(wname,"txt%04X",ui16_reg_addr);
			p_v = memset(wvalue,(int)0,sizeof(wvalue));
			i_r = g_sprintf(wvalue,"%-6.2f",decimal_value);
			widget_target = GTK_WIDGET(gtk_builder_get_object(builder, wname));
			assert(NULL != widget_target);
			gtk_label_set_text (GTK_LABEL(widget_target), (const gchar*)wvalue);
			break;
		case Unsigned32:
			break;
		case ODTemperature:
			break;
		case SlaveIDvalue:
			break;
		default:
			break;
		}
	}

}
