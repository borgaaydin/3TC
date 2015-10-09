#include<stdlib.h>
#include<stdio.h>

#include"functions.h"
#include"consts.h"

int main() {
    char tabChar[MAX_FRAME_SIZE];
    int bytes[NB_FILES_LIMIT] = {0, 0, 0, 0, 0, 0};
    int rejected = 0;
    int total = 0;
    FILE *data;

    // Opening input file
    if( (data = fopen("./data.sujet", "r")) == NULL ) {
        printf("Can't open input file data.sujet.\n");
    }

    // Opening output files
    FILE *f[NB_FILES_LIMIT];
    char filename[NB_FILES_LIMIT];
    int n;
    for( n = 0; n < NB_FILES_LIMIT; n++ ) {
        sprintf(filename, "f%d", n);
        if( (f[n] = fopen(filename, "w")) == NULL) {
            printf("Can't create/read f%d.\n", n);
        }
    }

    // Read frames in input file until we reach EOF
    while( readFile(data, tabChar) == 0) {
        int i = 2;
        n = validate(tabChar);

        if( n == -1 ) {
            while ( tabChar[i] != '\n' ) {
                fputc(tabChar[i-1], f[0]);
                bytes[0]++;
                i++;
            }
            fputc('\n', f[0]);
            rejected++;
            total++;
        } else if ( n > 0 && n < NB_FILES_LIMIT ) {
            writeFrame(f[n], tabChar, n, bytes);
            total++;
        }
    }

    fclose(data);

    printf("Ratio rejected/total = %d/%d\n", rejected, total);

    for ( n = 1; n < NB_FILES_LIMIT; n++ ) {
        fclose(f[n]);
        printf("File %d : %d bytes written.\n", n, bytes[n]);
    }

    return 0;
}