#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "functions.h"

void encoding(int *sequence) {
    int number = VERTEX_NUMBER - 1;
    int mark[VERTEX_NUMBER];
    memset(mark, 0, sizeof(mark));

    mark[DEPOT] = 1;
    int count = 0;
    int selected;

    while (1) {
        selected = rand() % VERTEX_NUMBER;
        if (!mark[selected]) {
            count = add_element(sequence, selected, count, count);
            mark[selected] = 1;
        }
        if (count == number) break;
    }
};

void decoding(int *sequence, int vNumber) {
    int seq[VERTEX_NUMBER];
    memcpy(seq, sequence, sizeof(seq));

    int count = VERTEX_NUMBER;

    for (int i = VERTEX_NUMBER - 1; i > 0; i--) {
        if (seq[i] >= vNumber) count = delete_element(seq, i, count);
    }
    memcpy(sequence, seq, sizeof(int) * vNumber);
};