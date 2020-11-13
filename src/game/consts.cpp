#include "consts.h"

double SIN_TABLE[TABLES_SIZE];
double COS_TABLE[TABLES_SIZE];

void init_tables() {
    for (int i = 0; i < TABLES_SIZE; ++i) {
        SIN_TABLE[i] = sin(i * PI / 180);
    }

    for (int i = 0; i < TABLES_SIZE; ++i) {
        COS_TABLE[i] = cos(i * PI / 180);
    }
}
