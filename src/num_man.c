#include <stdlib.h>
#include <math.h>
#include "num_man.h"
#include "definitions.h"

void append_num(int64_t *num, int to_append) {
    if (to_append == -1) {
		*num = *num / 10;
	} else {
		if ((float)*num / (float)NUM_LIMIT < 1) {
			*num = *num * 10 + to_append;
		}
	}
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

		default:
			break;
    }
    return 0;
}