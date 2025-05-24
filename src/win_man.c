#include <ncurses.h>
#include "definitions.h"
#include "win_man.h"


void clean_main_window(WINDOW* window) {
    werase(window);
    wborder(window, WINDOW_WALL, WINDOW_WALL, WINDOW_FLOOR, WINDOW_FLOOR, WINDOW_CORNER, WINDOW_CORNER, WINDOW_CORNER, WINDOW_CORNER);
    mvwprintw(window, 0, (MAIN_WINDOW_WIDTH / 2 - MAIN_WINDOW_TITLE_LEN / 2) + 1, MAIN_WINDOW_TITLE);
    mvwprintw(window, 2, 7, "Wynik: ");
    mvwprintw(window, 4, 7, "Podaj numer 1: [_________________________]");
    mvwprintw(window, 5, 7, "Podaj numer 2: [_________________________]");
    mvwprintw(window, 7, 7, "Wybierz operacje:  (+) (-) (*) (/) (%%)");
    mvwprintw(window, 8, 25, "(sin)   (cos)   (pow)");
    mvwprintw(window, 9, 7, "Wybrana operacja: >   <");
    mvwprintw(window, 12, 7, "! Tylko numer 1 jest uzywany do sin i cos");
    mvwprintw(window, 14, 24, "<Licz>");
    wrefresh(window);
}

void print_selected_option(WINDOW *window, int option) {
    if      (option == 1) mvwprintw(window, SELECTED_Y, SELECTED_X, OPTION_SELECTED_PLUS_TXT);
    else if (option == 2) mvwprintw(window, SELECTED_Y, SELECTED_X, OPTION_SELECTED_MINUS_TXT);
    else if (option == 3) mvwprintw(window, SELECTED_Y, SELECTED_X, OPTION_SELECTED_MULT_TXT);
    else if (option == 4) mvwprintw(window, SELECTED_Y, SELECTED_X, OPTION_SELECTED_DIV_TXT);
    else if (option == 5) mvwprintw(window, SELECTED_Y, SELECTED_X, OPTION_SELECTED_MOD_TXT);
    else if (option == 6) mvwprintw(window, SELECTED_Y, SELECTED_X, OPTION_SELECTED_SIN_TXT);
    else if (option == 7) mvwprintw(window, SELECTED_Y, SELECTED_X, OPTION_SELECTED_COS_TXT);
    else if (option == 8) mvwprintw(window, SELECTED_Y, SELECTED_X, OPTION_SELECTED_POW_TXT);
}
