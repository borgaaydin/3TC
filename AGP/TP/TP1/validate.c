#include<stdio.h>

#define PACKET_SIZE 8

int validate(char tabChar[]) {
    // Check if the first byte matches an output file
    int n;
    if ( (n = hexToAscii(tabChar[0])) > 5 ) {
        return -1;
    }

    // Count the number of bytes
    int i = 1;
    while ( tabChar[i] != '\n' && tabChar[i] != EOF ) {
        i++;
    }

    int checksum = hexToAscii(tabChar[i-1]);
    if ( checksum % PACKET_SIZE != (i-2) % PACKET_SIZE ) {
        return -1;
    } else if ( i == 2 ) {
        return -2;
    } else {
        return n;
    }
}