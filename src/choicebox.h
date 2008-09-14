#ifndef CHOICEBOX_H
#define CHOICEBOX_H

typedef void (*choice_handler)(int choice);
Ewl_Widget *init_choicebox(const char *choices[], int numchoices,choice_handler handler);
void fini_choicebox(Ewl_Widget *win);

#endif
