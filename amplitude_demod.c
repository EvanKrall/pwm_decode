#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define BUFSIZE 1024

void usage(char **argv) {
    dprintf(2, "Usage: %s\n", argv[0]);
    exit(1);
}


unsigned char limit(double x) {
    if (x > 255) {
        return 255;
    } else {
        return (unsigned char) x;
    }

}
void decode() {
    signed char ibuf[BUFSIZE];
    unsigned char obuf[BUFSIZE];
    size_t read_bytes;

    char carryover = 0;
    bool carryover_needed = false;

    int i=0;
    int write_bytes = 0;

    while ((read_bytes = i + read(0, ibuf+i, BUFSIZE-i))) {
        while ((i+1) < read_bytes) {
            obuf[i/2] = limit(hypot((double)(ibuf[i]), (double)(ibuf[i+1])));
            write_bytes++;
            i += 2;
        }
        if (i < read_bytes) {
            // there's one leftover
            ibuf[0] = ibuf[i];
            i = 1;
        } else {
            i = 0;
        }
        write(1, obuf, write_bytes);
        write_bytes = 0;
    }
}

int main(int argc, char **argv) {
    if (argc > 1) {
        usage(argv);
    }

    decode();
}
