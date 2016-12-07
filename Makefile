ALL_BINS = pwm_decode threshold bool2asc asc2bool amplitude_demod 16to8

CFLAGS = -std=c99

all: $(ALL_BINS)

debug: CFLAGS += -DDEBUG -g
debug: all


amplitude_demod: LDLIBS += -lm

clean:
	rm -f $(ALL_BINS)
	rm -rf *.dSYM

.gitignore:
	echo $(ALL_BINS) | xargs -n1 > $@
	echo '*.dSYM' >> $@
