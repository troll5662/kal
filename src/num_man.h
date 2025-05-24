#ifndef NUM_MAN_H
#define NUM_MAN_H

#include <stdlib.h>

void append_num(int64_t *num, int to_append);
int64_t calculate(int option, int64_t num1, int64_t num2);
float calculate_float(int option, int64_t num1, int64_t num2);

#endif