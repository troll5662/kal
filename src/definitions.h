#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define NUM_LIMIT 100000000000000

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

#endif