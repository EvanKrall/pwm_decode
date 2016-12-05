
ALL_BINS = pwm_decode threshold bool2asc asc2bool

debug: CFLAGS += -DDEBUG -g
debug: all

all: $(ALL_BINS)

clean:
	rm -f $(ALL_BINS)

.gitignore:
	echo $(ALL_BINS) | xargs -n1 > $@
	echo '*.dSYM' >> $@
