#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFSIZE 1024

void usage(char **argv) {
    dprintf(2, "Usage: %s <threshold>\n", argv[0]);
    exit(1);
}

void decode(signed char threshold) {
    signed char ibuf[BUFSIZE];
    char obuf[BUFSIZE];
    size_t read_bytes;

    while ((read_bytes = read(0, ibuf, BUFSIZE))) {
        for (int i=0; i<read_bytes; i++) {
            obuf[i] = (ibuf[i] > threshold);
        }
        write(1, obuf, read_bytes);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        usage(argv);
    }

    signed char threshold = atoi(argv[1]);

    decode(threshold);
}
