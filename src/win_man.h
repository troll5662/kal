#ifndef WIN_MAN_H
#define WIN_MAN_H

#include <ncurses.h>

void clean_main_window(WINDOW* window);
void print_selected_option(WINDOW *window, int option);

#endif