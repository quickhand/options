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

void main_choicehandler(int choice)
{
    fprintf(stderr,"Chose option #%d",choice);
    
}
int main(int argc, char *argv[])
{
  
    if ( !ewl_init ( &argc, argv ) )
    {
        return 1;
    }
    const char *initchoices[]={"Choice #1","Choice #2","Choice #3","Choice #4","Choice #5","Choice #6","Choice #7","Choice #8","Choice #9","Choice #10","Choice #11","Choice #12"};
    
    Ewl_Widget *startbox=init_choicebox(initchoices,12,main_choicehandler);
    ewl_widget_show(startbox);
    ewl_main();
    

    return 0;
}
