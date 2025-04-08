TESTFILES := $(wildcard **/*.a) $(wildcard *.a)
TESTS := $(TESTFILES:.a=.test)

.PHONY: all

all: $(TESTS)

%.test:
	@echo "Testing $*.a"
	@touch $*.err
	@../ac $*.a -c 2> $*.err ;\
	PROG_EXIT_CODE=$$?;\
	echo "diff error...";\
	diff $*.err $*.err.expected;\
	ERR_EXIT_CODE=$$?;\
	exit $$ERR_EXIT_CODE

clean:
	rm -f *.out *.err
