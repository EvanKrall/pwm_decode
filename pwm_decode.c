#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFSIZE 1024

void usage(char **argv) {
    dprintf(2, "Usage: %s <estimate of samples per symbol>\n", argv[0]);
    dprintf(2, "This program assumes input is a stream of signed int8.\n");
    exit(1);
}

void flush(char *buf, size_t *output_buffer_used) {
    write(1, buf, *output_buffer_used);
    *output_buffer_used = 0;
}

void emit(char current_bit, char *buf, size_t *output_buffer_used) {
    if (*output_buffer_used >= BUFSIZE) {
        flush(buf, output_buffer_used);
    }

    buf[*output_buffer_used] = current_bit ? '1' : '0';
    *output_buffer_used = *output_buffer_used + 1;
}

void decode(int samples_per_symbol_est) {
    signed char ibuf[BUFSIZE];
    char obuf[BUFSIZE];
    size_t read_bytes;
    size_t output_buffer_used = 0;

    bool last_bit = false;
    size_t  samples_since_pulse_start;

    while ((read_bytes = read(0, ibuf, BUFSIZE))) {
        for (int i=0; i<read_bytes; i++) {
            bool current_bit = ibuf[i];

            // rising edge
            if (!last_bit && current_bit) {
                samples_since_pulse_start = 0;
            } else {
                samples_since_pulse_start++;
            }

            // Halfway into the bit, measure
            if (samples_since_pulse_start == (samples_per_symbol_est / 2)) {
                emit(current_bit, obuf, &output_buffer_used);
            }

            last_bit = current_bit;
        }
    }
    flush(obuf, &output_buffer_used);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        usage(argv);
    }

    unsigned int samples_per_symbol_est = atoi(argv[1]);

    decode(samples_per_symbol_est);
}
