#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "definitions.h"
#include "movement.h"
#include "win_man.h"
#include "num_man.h"

int main(int argc, char *argv[]) {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    WINDOW *main_window = newwin(MAIN_WINDOW_HEIGHT, MAIN_WINDOW_WIDTH, 1, 1);
    WINDOW *help_window = newwin(HELP_WINDOW_HEIGHT, HELP_WINDOW_WIDTH, 16, 1);
    refresh();
    keypad(main_window, TRUE);

    clean_main_window(main_window);
    wborder(help_window, WINDOW_WALL, WINDOW_WALL, WINDOW_FLOOR, WINDOW_FLOOR, WINDOW_CORNER, WINDOW_CORNER, WINDOW_CORNER, WINDOW_CORNER);

    mvwprintw(help_window, 1, 7, "[Strzalki] Poruszanie    [Enter] Potwierdz");
    mvwprintw(help_window, 2, 7, "[Spacja]   Wybierz       [q]     Wyjdz");
    wrefresh(help_window);

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    wattron(main_window, COLOR_PAIR(1));
    mvwprintw(main_window, NUM1_Y, NUM1_X, NUM_INPUT_TXT);
    wattroff(main_window, COLOR_PAIR(1));   

    int64_t num1 = 0, num2 = 0;
    int64_t result = 0;
    float result_float = 0;
    int counted = 0;
    int get_num1 = 0, get_num2 = 0;
    int option_hovered = 0, option_selected = 0;
    struct cursor_t cursor = {0, 0} , old_cursor = {0, 0};
    wchar_t input_char;
    while (1) {
        input_char = wgetch(main_window);
        if (input_char == 'q') break;

        if (!(get_num1 || get_num2)) {
            switch(input_char) {
                case KEY_UP:
                    move_up(&cursor);
                    break;

                case KEY_DOWN:
                    move_down(&cursor);
                    break;

                case KEY_LEFT:
                    move_left(&cursor);
                    break;

                case KEY_RIGHT:
                    move_right(&cursor);
                    break;

                case ' ':
                    if      (cursor.y == NUM1_NUM) get_num1 = 1;
                    else if (cursor.y == NUM2_NUM) get_num2 = 1;
                    else if (cursor.y == OPTIONS1_NUM || cursor.y == OPTIONS2_NUM) option_selected = option_hovered;
                    else if (cursor.y == BUTTON_NUM) {
                        switch (option_selected) {
                            case 1:
                            case 2:
                            case 3:
                            case 5:
                            case 8:
                                result = calculate(option_selected, num1, num2);
                                counted = 1;
                                break;

                            case 4:
                            case 6:
                            case 7:
                                result_float = calculate_float(option_selected, num1, num2);
                                counted = 2;
                                break;
                        }
                    }
                    break;
                default:
                    break;
            }
        } else {
            switch(input_char) {
                case '\n':
                    get_num1 = 0;
                    get_num2 = 0;
                    break;

                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if      (get_num1) append_num(&num1, (int)(input_char - '0'));
                    else if (get_num2) append_num(&num2, (int)(input_char - '0'));
                    break;

                case KEY_BACKSPACE:
                    if      (get_num1) append_num(&num1, -1);
                    else if (get_num2) append_num(&num2, -1);
                    break;

                default:
                    break;
            }
        }

        if ((cursor.y == OPTIONS1_NUM || cursor.y == OPTIONS2_NUM)) option_hovered = (cursor.y - OPTIONS1_NUM) * 5 + cursor.x + 1;
        else option_hovered = 0;

        clean_main_window(main_window);

        if (num1 > 0) mvwprintw(main_window, NUM1_Y, NUM1_X + 1, "%ld", num1);
        if (num2 > 0) mvwprintw(main_window, NUM2_Y, NUM2_X + 1, "%ld", num2);

        if 		(counted == 1) mvwprintw(main_window, RESULT_Y, RESULT_X, "%ld", result);
        else if (counted == 2) mvwprintw(main_window, RESULT_Y, RESULT_X, "%lf", result_float);

        switch (cursor.y) {
            case NUM1_NUM:
                if (get_num1)   mvwchgat(main_window, NUM1_Y, NUM1_X, strlen(NUM_INPUT_TXT), A_BOLD, 1, NULL);
                else            mvwchgat(main_window, NUM1_Y, NUM1_X, strlen(NUM_INPUT_TXT), A_NORMAL, 1, NULL);
                break;

            case NUM2_NUM:
                if (get_num2)   mvwchgat(main_window, NUM2_Y, NUM2_X, strlen(NUM_INPUT_TXT), A_BOLD, 1, NULL);
                else            mvwchgat(main_window, NUM2_Y, NUM2_X, strlen(NUM_INPUT_TXT), A_NORMAL, 1, NULL);
                break;

            case OPTIONS1_NUM:
            case OPTIONS2_NUM:
                switch (option_hovered) {
                    case 1:
                        mvwchgat(main_window, OPTIONS1_Y, OPTIONS1_X, strlen(OPTION_PLUS_TXT), A_NORMAL, 1, NULL);
                        break;

                    case 2:
                        mvwchgat(main_window, OPTIONS1_Y, OPTIONS1_X + 4, strlen(OPTION_MINUS_TXT), A_NORMAL, 1, NULL);
                        break;

                    case 3:
                        mvwchgat(main_window, OPTIONS1_Y, OPTIONS1_X + 8, strlen(OPTION_MULT_TXT), A_NORMAL, 1, NULL);
                        break;

                    case 4:
                        mvwchgat(main_window, OPTIONS1_Y, OPTIONS1_X + 12, strlen(OPTION_DIV_TXT), A_NORMAL, 1, NULL);
                        break;

                    case 5:
                        mvwchgat(main_window, OPTIONS1_Y, OPTIONS1_X + 16, strlen(OPTION_MOD_TXT), A_NORMAL, 1, NULL);
                        break;

                    case 6: 
                        mvwchgat(main_window, OPTIONS2_Y, OPTIONS2_X, strlen(OPTION_SIN_TXT), A_NORMAL, 1, NULL);
                        break;

                    case 7: 
                        mvwchgat(main_window, OPTIONS2_Y, OPTIONS2_X + 8, strlen(OPTION_COS_TXT), A_NORMAL, 1, NULL);
                        break;

                    case 8: 
                        mvwchgat(main_window, OPTIONS2_Y, OPTIONS2_X + 16, strlen(OPTION_POW_TXT), A_NORMAL, 1, NULL);
                        break;

                    default:
                        break;
                }
                break;

            case BUTTON_NUM:
                mvwchgat(main_window, BUTTON_Y, BUTTON_X, strlen(BUTTON_TXT), A_NORMAL, 1, NULL);
                break;
        }
        print_selected_option(main_window, option_selected);

        wrefresh(main_window);
        refresh();

        old_cursor.x = cursor.x;
        old_cursor.y = cursor.y;
    }

    endwin();

    return 0;
}