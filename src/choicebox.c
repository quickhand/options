/***************************************************************************
 *   Copyright (C) 2008 by Marc Lajoie   *
 *   marc@gatherer   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <Ewl.h>
#include "keyhandler.h"
#include "choicebox.h"


const int noptions=8;





#define REL_THEME "themes/options.edj"

/*
 * Returns edje theme file name.
 */
char* get_theme_file()
{
    char* cwd = get_current_dir_name();
    char* rel_theme;
    asprintf(&rel_theme, "%s/%s", cwd, REL_THEME);
    free(cwd);
    return rel_theme;
}










typedef struct _choice_info_struct {
    char **choices;
    int numchoices;    
    int curindex;
    int navsel;
    choice_handler handler;
    
} choice_info_struct;

void choicebox_next_page(Ewl_Widget *widget)
{
    choice_info_struct *infostruct;
    infostruct=(choice_info_struct *)ewl_widget_data_get(widget,"choice_info");
    Ewl_Widget *vbox=ewl_container_child_get(EWL_CONTAINER(widget),0);
    Ewl_Widget *tempw1;
    if(infostruct->numchoices<noptions || (infostruct->curindex+noptions+1)>=infostruct->numchoices)
        return;
    infostruct->curindex+=noptions;
    int i;
    //for(i=0;i<noptions;i++)
    //    ewl_widget_hide(EWL_WIDGET(ewl_container_child_get(EWL_CONTAINER(vbox),i)));
    int shownum=((infostruct->numchoices-infostruct->curindex)>noptions)?noptions:(infostruct->numchoices-infostruct->curindex);
    for(i=0;i<noptions;i++)
    {
        tempw1=EWL_WIDGET(ewl_container_child_get(EWL_CONTAINER(vbox),i));
        if(i<shownum)
        {
            
            //ewl_widget_appearance_part_text_set(EWL_WIDGET(tempw1),"ewl/box/dlg_optionbox/text",infostruct->choices[infostruct->curindex+i]);
            ewl_label_text_set(EWL_LABEL(ewl_container_child_get(EWL_CONTAINER(tempw1),0)),infostruct->choices[infostruct->curindex+i]);

        }
        else
        {
            //ewl_widget_appearance_part_text_set(EWL_WIDGET(tempw1),"ewl/box/dlg_optionbox/text","");
            ewl_label_text_set(EWL_LABEL(ewl_container_child_get(EWL_CONTAINER(tempw1),0)),"");
            
        }
    }
    choicebox_change_selection(widget,0);
    
}
void choicebox_previous_page(Ewl_Widget *widget)
{
    choice_info_struct *infostruct;
    infostruct=(choice_info_struct *)ewl_widget_data_get(widget,"choice_info");
    Ewl_Widget *vbox=ewl_container_child_get(EWL_CONTAINER(widget),0);
    Ewl_Widget *tempw1;
    if(infostruct->numchoices<noptions || infostruct->curindex==0)
        return;
    infostruct->curindex-=noptions;
    int i;
    for(i=0;i<noptions;i++)
    {
        tempw1=EWL_WIDGET(ewl_container_child_get(EWL_CONTAINER(vbox),i));
        
        //ewl_widget_appearance_part_text_set(EWL_WIDGET(tempw1),"ewl/box/dlg_optionbox/text",infostruct->choices[infostruct->curindex+i]);  
        ewl_label_text_set(EWL_LABEL(ewl_container_child_get(EWL_CONTAINER(tempw1),0)),infostruct->choices[infostruct->curindex+i]);
    }
    choicebox_change_selection(widget,0);
}

void choicebox_esc(Ewl_Widget *widget)
{
    fini_choicebox(widget);
}


void choicebox_item(Ewl_Widget *widget,int item)
{
    choice_info_struct *infostruct;
    if(item>=1&&item<=8)
    {
        int curchoice;
        infostruct=(choice_info_struct *)ewl_widget_data_get(widget,"choice_info");
        curchoice=infostruct->curindex+(item-1);
        if(curchoice<infostruct->numchoices)
            (infostruct->handler)(curchoice);
        
    }
    else if(item==9)
        choicebox_previous_page(widget);
    else if(item==0)
        choicebox_next_page(widget);
}
void choicebox_change_selection(Ewl_Widget *widget,int new_navsel)
{
    choice_info_struct *infostruct=(choice_info_struct *)ewl_widget_data_get(widget,"choice_info");
    Ewl_Widget *vbox=ewl_container_child_get(EWL_CONTAINER(widget),0);
    Ewl_Widget *oldselected=ewl_container_child_get(EWL_CONTAINER(vbox),infostruct->navsel);
    Ewl_Widget *newselected=ewl_container_child_get(EWL_CONTAINER(vbox),new_navsel);
    
    if(get_nav_mode()==1)
    {
        ewl_widget_state_set(oldselected,"unselect",EWL_STATE_PERSISTENT);
        ewl_widget_state_set(ewl_container_child_get(EWL_CONTAINER(oldselected),0),"unselect",EWL_STATE_PERSISTENT);
        ewl_widget_state_set(newselected,"select",EWL_STATE_PERSISTENT);
        ewl_widget_state_set(ewl_container_child_get(EWL_CONTAINER(newselected),0),"select",EWL_STATE_PERSISTENT);
    }
    infostruct->navsel=new_navsel;
}



void choicebox_nav_up(Ewl_Widget *widget)
{
    choice_info_struct *infostruct=(choice_info_struct *)ewl_widget_data_get(widget,"choice_info");
    //Ewl_Widget *vbox=ewl_container_child_get(EWL_CONTAINER(widget),0);
    if(infostruct->navsel==0)
        return;

    choicebox_change_selection(widget,infostruct->navsel-1);
    /*Ewl_Widget *oldselected=ewl_container_child_get(EWL_CONTAINER(vbox),infostruct->navsel);
    infostruct->navsel--;
    Ewl_Widget *newselected=ewl_container_child_get(EWL_CONTAINER(vbox),infostruct->navsel);
    
    ewl_widget_state_set(oldselected,"unselect",EWL_STATE_PERSISTENT);
    ewl_widget_state_set(ewl_container_child_get(EWL_CONTAINER(oldselected),0),"unselect",EWL_STATE_PERSISTENT);
    ewl_widget_state_set(newselected,"select",EWL_STATE_PERSISTENT);
    ewl_widget_state_set(ewl_container_child_get(EWL_CONTAINER(newselected),0),"select",EWL_STATE_PERSISTENT);*/
}

void choicebox_nav_down(Ewl_Widget *widget)
{
    choice_info_struct *infostruct=(choice_info_struct *)ewl_widget_data_get(widget,"choice_info");
    //Ewl_Widget *vbox=ewl_container_child_get(EWL_CONTAINER(widget),0);
    if(infostruct->navsel==(noptions-1) || ((infostruct->curindex+infostruct->navsel+1)>=infostruct->numchoices))
        return;
    choicebox_change_selection(widget,infostruct->navsel+1);
    /*Ewl_Widget *oldselected=ewl_container_child_get(EWL_CONTAINER(vbox),infostruct->navsel);
    infostruct->navsel++;
    Ewl_Widget *newselected=ewl_container_child_get(EWL_CONTAINER(vbox),infostruct->navsel);
    
    ewl_widget_state_set(oldselected,"unselect",EWL_STATE_PERSISTENT);
    ewl_widget_state_set(ewl_container_child_get(EWL_CONTAINER(oldselected),0),"unselect",EWL_STATE_PERSISTENT);
    ewl_widget_state_set(newselected,"select",EWL_STATE_PERSISTENT);
    ewl_widget_state_set(ewl_container_child_get(EWL_CONTAINER(newselected),0),"select",EWL_STATE_PERSISTENT);*/
}

void choicebox_nav_left(Ewl_Widget *widget)
{
    choicebox_previous_page(widget);
}

void choicebox_nav_right(Ewl_Widget *widget)
{
    choicebox_next_page(widget);
}

void choicebox_nav_sel(Ewl_Widget *widget)
{
    choice_info_struct *infostruct=(choice_info_struct *)ewl_widget_data_get(widget,"choice_info");
    (infostruct->handler)(infostruct->curindex*noptions+infostruct->navsel);
    
}

static key_handler_info_t choicebox_handlers =
{
    .nav_up_handler=&choicebox_nav_up,
    .nav_down_handler=&choicebox_nav_down,
    .nav_left_handler=&choicebox_nav_left,
    .nav_right_handler=&choicebox_nav_right,
    .nav_sel_handler=&choicebox_nav_sel,
    .esc_handler = &choicebox_esc,
    .item_handler = &choicebox_item,
};

void destroy_cb ( Ewl_Widget *w, void *event, void *data )
{
    fini_choicebox( w );
}



Ewl_Widget *init_choicebox(const char *choicelist[], int numchoices,choice_handler handler)
{
    Ewl_Widget *win,*vbox,*tempw1,*tempw2;
    int i;
    //int *curchoice=(int *)malloc(sizeof(int));
    //*curchoice=-1;
    set_nav_mode(1);
    choice_info_struct *info=(choice_info_struct*)malloc(sizeof(choice_info_struct));
    
    info->numchoices=numchoices;
    info->curindex=0;
    info->navsel=0;
    info->handler=handler;
    
    info->choices=(char**)malloc(sizeof(char*)*numchoices);
    for(i=0;i<numchoices;i++)
    {
    
        info->choices[i]=(char *)malloc(sizeof(char)*(strlen(choicelist[i])+1));
        //strcat(info->choices[i],choicelist[i]);
        asprintf(&(info->choices[i]),"%s",choicelist[i]);
    
    }
    
    win = ewl_window_new();
    ewl_window_title_set ( EWL_WINDOW ( win ), "EWL_WINDOW" );
    ewl_window_name_set ( EWL_WINDOW ( win ), "EWL_WINDOW" );
    ewl_window_class_set ( EWL_WINDOW ( win ), "ChoiceBox" );
    set_key_handler(EWL_WIDGET(win), &choicebox_handlers);
    //ewl_attach_other_set(win,(void *)curchoice);
    ewl_callback_append ( win, EWL_CALLBACK_DELETE_WINDOW, destroy_cb, NULL );
    ewl_widget_data_set(EWL_WIDGET(win),(void *)"choice_info",(void *)info);
    ewl_widget_show ( win );
    
   
    vbox=ewl_vbox_new();
    ewl_container_child_append(EWL_CONTAINER(win),vbox);
    ewl_object_fill_policy_set(EWL_OBJECT(vbox),EWL_FLAG_FILL_FILL);
    ewl_widget_show(vbox);
    
    int shownum=(numchoices<=noptions)?numchoices:noptions;
    char *tempstr;
    tempstr=get_theme_file();
    for(i=0;i<shownum;i++)
    {
        
        tempw1=ewl_hbox_new();
        ewl_container_child_append(EWL_CONTAINER(vbox),tempw1);
        ewl_theme_data_str_set(EWL_WIDGET(tempw1),"/hbox/file",tempstr);
        ewl_theme_data_str_set(EWL_WIDGET(tempw1),"/hbox/group","ewl/box/dlg_optionbox");
        //ewl_widget_appearance_part_text_set(EWL_WIDGET(tempw1),"ewl/box/dlg_optionbox/text",info->choices[i]);
        ewl_object_fill_policy_set(EWL_OBJECT(tempw1),EWL_FLAG_FILL_FILL);
        if(get_nav_mode()==1 && i==0)
            ewl_widget_state_set(tempw1,"select",EWL_STATE_PERSISTENT);
        
        ewl_widget_show(tempw1);
        
        tempw2=ewl_label_new();
        ewl_container_child_append(EWL_CONTAINER(tempw1),tempw2);
        ewl_theme_data_str_set(EWL_WIDGET(tempw2),"/label/file",tempstr);
        ewl_theme_data_str_set(EWL_WIDGET(tempw2),"/label/group","ewl/label/dlg_optionlabel");
        ewl_theme_data_str_set(EWL_WIDGET(tempw2),"/label/textpart","ewl/label/dlg_optionlabel/text");
        if(get_nav_mode()==1 && i==0)
            ewl_widget_state_set(tempw2,"select",EWL_STATE_PERSISTENT);
        ewl_label_text_set(EWL_LABEL(tempw2),info->choices[i]);
        ewl_widget_show(tempw2);
        
    }
    free(tempstr);       
    return win;

}

void fini_choicebox(Ewl_Widget *win)
{
    ewl_widget_hide(win);
    choice_info_struct *infostruct=(choice_info_struct *)ewl_widget_data_get(win,"choice_info");
    int i;
    for(i=0;i<infostruct->numchoices;i++)
        free(infostruct->choices[i]);
    free(infostruct->choices);
    free(infostruct);
    ewl_widget_destroy(win);  
    
}



