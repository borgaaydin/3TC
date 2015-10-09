#include<stdio.h>

#include"consts.h"

int readFile(FILE *file, char tabChar[]) {
    char c;
    int i = 0;
    c = fgetc(file);

    while ( c != '\n' && c != EOF) {
        if ( i > MAX_FRAME_SIZE-1 ) {
            break;
        }

        tabChar[i] = c;
        i++;
        c = fgetc(file);
    }

    if ( c == EOF ) return 1;
    tabChar[i] = c;
    return 0;
}