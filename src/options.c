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
#include "choicebox.h"

Ewl_Widget *options_choicebox;
Ewl_Widget *font_family_choicebox;
Ewl_Widget *font_size_choicebox;
Ewl_Widget *margin_choicebox;
Ewl_Widget *margin_setting_choicebox;
Ewl_Widget *line_space_choicebox;



void font_family_choicehandler(int choice)
{
    fini_choicebox(font_family_choicebox);
}
void font_size_choicehandler(int choice)
{
    fini_choicebox(font_size_choicebox);
}
int margin_setting=0;
void margin_setting_choicehandler(int choice)
{
    fini_choicebox(margin_setting_choicebox);
    fini_choicebox(margin_choicebox);
}
void margin_choicehandler(int choice)
{
    margin_setting=choice;
    const char *initchoices[]={"1. 0px","2. 1px","3. 2px","4. 3px","5. 4px","6. 5px","7. 6px","8. 7px","1. 8px","2. 9px","3. 10px","4. 11px","5. 12px","6. 13px","7. 14px","8. 15px"};
    ewl_widget_show(margin_setting_choicebox=init_choicebox(initchoices,16,margin_setting_choicehandler));
}

void line_space_choicehandler(int choice)
{
    fini_choicebox(line_space_choicebox);
}

void main_choicehandler(int choice)
{
    
    if(choice==0)
    {
        const char *initchoices[]={"1. Times New Roman","2. Georgia","3. Arial"};
        ewl_widget_show(font_family_choicebox=init_choicebox(initchoices,3,font_family_choicehandler));
    }
    else if(choice==1)
    {
        const char *initchoices[]={"1. 8pt","2. 9pt","3. 10pt","4. 11pt","5. 12pt","6. 13pt","7. 14pt"};
        ewl_widget_show(font_size_choicebox=init_choicebox(initchoices,7,font_size_choicehandler));
    }
    else if(choice==2)
    {
        const char *initchoices[]={"1. Left Margin","2. Right Margin","3. Top Margin","4. Bottom Margin"};
        ewl_widget_show(margin_choicebox=init_choicebox(initchoices,4,margin_choicehandler));
    }
    else if(choice==3)
    {
        const char *initchoices[]={"1. Single Spaced","2. 1.5 Spaced","3. Double Spaced","4. Triple Spaced"};
        ewl_widget_show(line_space_choicebox=init_choicebox(initchoices,4,line_space_choicehandler));
        
    }
    
    
}

int main(int argc, char *argv[])
{
  
    if ( !ewl_init ( &argc, argv ) )
    {
        return 1;
    }
    const char *initchoices[]={"1. Font Family","2. Font Size","3. Margin","4. Line Spacing"};
    ewl_widget_show(options_choicebox=init_choicebox(initchoices,4,main_choicehandler));
    
    ewl_main();
    

    return 0;
}
