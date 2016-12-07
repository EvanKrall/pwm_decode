#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFSIZE 1024

void decode() {
    signed char ibuf[BUFSIZE];
    char obuf[BUFSIZE];
    size_t read_bytes;

    while ((read_bytes = read(0, ibuf, BUFSIZE))) {
        for (int i=0; i<read_bytes; i++) {
            obuf[i] = ibuf[i] >= '1' ? 1 : 0;
        }
        write(1, obuf, read_bytes);
    }
}

int main(int argc, char **argv) {
    decode();
}
