TESTFILES := $(wildcard *.a)
TESTS := $(TESTFILES:.a=.test)

.PHONY: all

all: $(TESTS)

%.test:
	@rm -f $*.out
	@touch $*.out
	@echo "TEST $*"
	@../ac $*.a -n $*.out 2> $*.err; \
	PROG_EXIT_CODE=$$?;\
	diff -B --ignore-all-space $*.out $*.unparse.expected; \
	STDOUT_DIFF_EXIT=$$?;\
	diff -B --ignore-all-space $*.err $*.err.expected; \
	STDERR_DIFF_EXIT=$$?;\
	FAIL=$$(($$STDOUT_DIFF_EXIT || $$STDERR_DIFF_EXIT));\
	exit $$FAIL || echo "All tests passed"

clean:
	rm -f *.unparse *.err
