# experiments/Makefile

CFLAGS += -std=c11 \
          -Wall -Wextra -Wpedantic \
          -Wcomments -Wformat=2 -Wjump-misses-init -Wlogical-op \
          -Wmissing-include-dirs -Wnested-externs -Wold-style-definition \
          -Wredundant-decls -Wshadow -Wstrict-prototypes -Wswitch-enum \
          -Wunused-macros -Wvla -Wwrite-strings \
          -Wno-override-init -Wno-unused-parameter

CPPFLAGS += -DMAX=100

binaries = $(basename $(wildcard *.c))


.PHONY: slow
slow: $(binaries)
slow: CFLAGS += -O0


.PHONY: fast
fast: $(binaries)
fast: CFLAGS += -O2


.PHONY: benchmark
benchmark:
	@echo "::: RUNNING BENCHMARKS UNDER -O0"
	$(MAKE) clean slow benchmark-run
	@echo
	@echo "::: RUNNING BENCHMARKS UNDER -O2"
	$(MAKE) clean fast benchmark-run

n = 43
.PHONY: benchmark-run
benchmark-run:
	@echo
	time -p ./rec-single $(n)
	@echo
	time -p ./rec-fork $(n)
	@echo
	time -p ./cache-single $(n)

clean:
	-rm -f $(binaries)
.PHONY: clean

