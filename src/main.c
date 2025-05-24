#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#define MAIN_WINDOW_WIDTH 56
#define MAIN_WINDOW_HEIGHT 16
#define HELP_WINDOW_WIDTH 56
#define HELP_WINDOW_HEIGHT 4
#define WINDOW_WALL '|'
#define WINDOW_FLOOR '-'
#define WINDOW_CORNER '+'
#define MAIN_WINDOW_TITLE "[Licznik]"
#define MAIN_WINDOW_TITLE_LEN 9

#define NUM_INPUT_TXT "[_________________________]"
#define OPTION_PLUS_TXT "(+)"
#define OPTION_MINUS_TXT "(-)"
#define OPTION_MULT_TXT "(*)"
#define OPTION_DIV_TXT "(/)"
#define OPTION_MOD_TXT "(%%)"
#define OPTION_SIN_TXT "(sin)"
#define OPTION_COS_TXT "(cos)"
#define OPTION_POW_TXT "(pow)"

#define OPTION_SELECTED_PLUS_TXT ">  +  <"
#define OPTION_SELECTED_MINUS_TXT ">  -  <"
#define OPTION_SELECTED_MULT_TXT ">  *  <"
#define OPTION_SELECTED_DIV_TXT ">  /  <"
#define OPTION_SELECTED_MOD_TXT ">  %%  <"
#define OPTION_SELECTED_SIN_TXT "> sin <"
#define OPTION_SELECTED_COS_TXT "> cos <"
#define OPTION_SELECTED_POW_TXT "> pow <"

#define BUTTON_TXT "<Licz>"


#define NUM1_NUM 0
#define NUM1_X 22
#define NUM1_Y 4

#define NUM2_NUM 1
#define NUM2_X 22
#define NUM2_Y 5

#define OPTIONS1_NUM 2
#define OPTIONS1_X 26
#define OPTIONS1_Y 7

#define OPTIONS2_NUM 3
#define OPTIONS2_X 25
#define OPTIONS2_Y 8

#define BUTTON_NUM 4
#define BUTTON_X 24
#define BUTTON_Y 14

#define RESULT_X 14
#define RESULT_Y 2

#define SELECTED_X 25
#define SELECTED_Y 9

struct cursor_t {
    int x;
    int y;
};

void clean_main_window(WINDOW* window);

void move_up(struct cursor_t *cursor);
void move_down(struct cursor_t *cursor);
void move_left(struct cursor_t *cursor);
void move_right(struct cursor_t *cursor);
int cursor_on_options(struct cursor_t *cursor);
void print_selected_option(WINDOW *window, int option);
void append_num(int64_t *num, int to_append);
int64_t calculate(int option, int64_t num1, int64_t num2);
float calculate_float(int option, int64_t num1, int64_t num2);

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
                    if      (cursor.y == NUM1_NUM)                              get_num1 = 1;
                    else if (cursor.y == NUM2_NUM)                              get_num2 = 1;
                    else if (cursor_on_options(&cursor))                option_selected = option_hovered;
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

                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '0':
                    if      (get_num1) append_num(&num1, (int)(input_char - '0'));
                    else if (get_num2) append_num(&num2, (int)(input_char - '0'));
                    break;
                default:
                    break;
            }
        }

        if (cursor_on_options(&cursor)) option_hovered = (cursor.y - OPTIONS1_NUM) * 5 + cursor.x + 1;
        else                                    option_hovered = 0;

        clean_main_window(main_window);

        if (num1 > 0) {
            mvwprintw(main_window, NUM1_Y, NUM1_X + 1, "%ld", num1);
        }

        if (num2 > 0) {
            mvwprintw(main_window, NUM2_Y, NUM2_X + 1, "%ld", num2);
        }
        if (counted == 1) {
            mvwprintw(main_window, RESULT_Y, RESULT_X, "%ld", result);
        } else if (counted == 2) {
            mvwprintw(main_window, RESULT_Y, RESULT_X, "%lf", result_float);
        }
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
                if      (option_hovered == 1) mvwchgat(main_window, OPTIONS1_Y, OPTIONS1_X, strlen(OPTION_PLUS_TXT), A_NORMAL, 1, NULL);
                else if (option_hovered == 2) mvwchgat(main_window, OPTIONS1_Y, OPTIONS1_X + 4, strlen(OPTION_MINUS_TXT), A_NORMAL, 1, NULL);
                else if (option_hovered == 3) mvwchgat(main_window, OPTIONS1_Y, OPTIONS1_X + 8, strlen(OPTION_MULT_TXT), A_NORMAL, 1, NULL);
                else if (option_hovered == 4) mvwchgat(main_window, OPTIONS1_Y, OPTIONS1_X + 12, strlen(OPTION_DIV_TXT), A_NORMAL, 1, NULL);
                else if (option_hovered == 5) mvwchgat(main_window, OPTIONS1_Y, OPTIONS1_X + 16, strlen(OPTION_MOD_TXT), A_NORMAL, 1, NULL);
                break;

            case OPTIONS2_NUM:
                if      (option_hovered == 6) mvwchgat(main_window, OPTIONS2_Y, OPTIONS2_X, strlen(OPTION_SIN_TXT), A_NORMAL, 1, NULL);
                else if (option_hovered == 7) mvwchgat(main_window, OPTIONS2_Y, OPTIONS2_X + 8, strlen(OPTION_COS_TXT), A_NORMAL, 1, NULL);
                else if (option_hovered == 8) mvwchgat(main_window, OPTIONS2_Y, OPTIONS2_X + 16, strlen(OPTION_POW_TXT), A_NORMAL, 1, NULL);
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

void move_up(struct cursor_t *cursor) {
    if (cursor->y > 0)   cursor->y--;
    else                return;

    if (cursor->y == OPTIONS1_NUM) {
        if      (cursor->x == 1) cursor->x = 2;
        else if (cursor->x == 2) cursor->x = 4;
    } else {
        cursor->x = 0;
    }
}

void move_down(struct cursor_t *cursor) {
    if (cursor->y < 4)   cursor->y++;
    else                return;

    if (cursor->y == OPTIONS2_NUM) {
        if      (cursor->x == 1)                     cursor->x = 0;
        else if (cursor->x == 2)                     cursor->x = 1;
        else if (cursor->x == 3 || cursor->x == 4)    cursor->x = 2;
    } else {
        cursor->x = 0;
    }
}

void move_left(struct cursor_t *cursor) {
    if (cursor->y == OPTIONS1_NUM || cursor->y == OPTIONS2_NUM) {
        if (cursor->x > 0)   cursor->x--;
    } else {
        return;
    }
}

void move_right(struct cursor_t *cursor) {
    if (cursor->y == OPTIONS1_NUM) {
        if (cursor->x < 4) cursor->x++;
    } else if (cursor->y == OPTIONS2_NUM) {
        if (cursor->x < 2) cursor->x++;
    } else {
        return;
    }
}

int cursor_on_options(struct cursor_t *cursor) {
    return (cursor->y == OPTIONS1_NUM || cursor->y == OPTIONS2_NUM);
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

void append_num(int64_t *num, int to_append) {
    *num = *num * 10 + to_append;
}

int64_t calculate(int option, int64_t num1, int64_t num2) {
    switch (option) {
        case 1:
            return num1 + num2;
            break;
        case 2:
            return num1 - num2;
            break;
        case 3:
            return num1 * num2;
            break;
        case 5:
            return num1 % num2;
            break;
        case 8:
            return pow(num1, num2);
            break;
        default:
            break;
    }
    return 0;
}

float calculate_float(int option, int64_t num1, int64_t num2) {
    switch (option) {
        case 4:
            return (float)num1 / (float)num2;
            break;
        case 6:
            return sin(num1);
            break;
        case 7:
            return cos(num1);
            break;
    }
    return 0;
}