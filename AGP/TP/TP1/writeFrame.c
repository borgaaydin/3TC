#include<stdio.h>

#include"consts.h">

int writeFrame(FILE* file, char tabChar[], int n, int bytes[]) {
    int j = 0;
    int i = 2;

    while ( tabChar[i] != '\n' ) {
        fputc(tabChar[i-1], file);
        bytes[n]++;
        i++;

        if ( (i-2)%7 == 0 ) {
            fputc('7', file);
            fputc('\n', file);
        }
    }

    if ( (i-2)%7 != 0 ) {
        for ( j = (i-2)%7; j < 7; j++) {
            fputc('?', file);
        }

        fputc((i-2)%7+48, file); // Ascii code of the number
        fputc('\n', file);
    }

    return 0;
}