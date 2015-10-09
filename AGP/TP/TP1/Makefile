compile:
    gcc -Wall -c validate.c -o validate.o
    gcc -Wall -c hexToAscii.c -o hexToAscii.o
    gcc -Wall -c writeFrame.c -o writeFrame.o
    gcc -Wall -c readFile.c -o readFile.o
    gcc -Wall -c demux.c -o demux.o
    gcc -Wall demux.o validate.o hexToAscii.o writeFrame.o readFile.o -o demux
