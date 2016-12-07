# Building

Run `make`.

This should build cleanly on both OS X (clang 7.3.0) and Linux (gcc 4.8.4)
Please file an issue if it doesn't.

# Example usage:

```
# Record some data, e.g. using one of the following:

SAMP_RATE=2000000
rtl_sdr -f 433000000 -s $SAMP_RATE packet.cu8
# TODO: rtl_sdr records offset-signed data, so there's a DC shift of 127. This messes up amplitude demodulation.

SAMP_RATE=2000000
hackrf_transfer -r packet.cs8 -f 433000000 -s $SAMP_RATE -b 1 -l 40

SAMP_RATE=3000000
airspy_rx -f 433 -a 3000000 -t2 -r packet.cs16 && ./16to8 packet.cs16 > packet.cs8

# Make sure you actually caught a clean recording, and figure out the baud, if necessary.

inspectrum packet.cs8

# Look at baseline noise levels in your recording to figure out what your threshold should be

./amplitude_demod < ./packet.cs8 | od -v -d u1 | less

# Now decode:

./amplitude_demod < ./packet.cs8 | ./threshold 20 | ./pwm_decode $((SAMP_RATE/BAUD))
```

This example doesn't do any filtering/shifting of the signal, so it won't be robust to interference from other signals within the receive window of your SDR. [CSDR](https://github.com/simonyiszk/csdr) might be useful if you want that sort of filtering.


# How `pwm_decode` works

`pwm_decode` reads `unsigned char` from stdin, expecting them to be 0 or 1.
You must pass the estimated length of each symbol (in samples) as an argument.
This does not have to be exact, but should be within a factor of 2.
At a rising edge (a 0 to 1 transition), it starts counting symbols.
Halfway through the symbol (when the counter is `samples_per_symbol_est / 2`) emits the ASCII char '0' or '1', depending on whether the input is still high or low.
When `samples_per_symbol_est * 2` symbols have passed without another rising edge, it emits a newline.
