int hexToAscii(char c) {
    int v = 0;
    if ( c > 47 && c <= 57 ) {
        v = c - 48;
    } else if ( c > 64 && c <= 70 ) {
        v = c - 55;
    }

    return v;
}