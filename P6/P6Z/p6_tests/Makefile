TESTFILES := $(wildcard **/*.a) $(wildcard *.a)
TESTS := $(TESTFILES:.a=.test)

.PHONY: all

all: $(TESTS)

%.test:
	@rm -f $*.err $*.3ac
	@touch $*.err $*.3ac
	@echo "TEST $*"
	@../ac $*.a -a $*.3ac ;\
	PROG_EXIT_CODE=$$?;\
	echo "Comparing 3AC output for $*.a...";\
	diff -B --ignore-all-space $*.3ac $*.3ac.expected;\
	TAC_DIFF_EXIT=$$?;\
	exit $$TAC_DIFF_EXIT

clean:
	rm -f *.3ac *.out *.err
