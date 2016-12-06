ALL_BINS = pwm_decode threshold bool2asc asc2bool amplitude_demod 16to8

all: $(ALL_BINS)

debug: CFLAGS += -DDEBUG -g
debug: all


clean:
	rm -f $(ALL_BINS)
	rm -rf *.dSYM

.gitignore:
	echo $(ALL_BINS) | xargs -n1 > $@
	echo '*.dSYM' >> $@
