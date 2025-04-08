TESTFILES := $(wildcard *.a)
TESTS := $(TESTFILES:.a=.test)
UNPARSE := $(TESTFILES:.a=)

.PHONY: all

all: $(TESTS)

testAll:
	echo "TEST ALL TESTS"
	cat *.a > ALLTESTS.a
	../ac ALLTESTS.a -u ALLTESTS.unparse 2> ALLTESTS.err
	diff -B --ignore-all-space ALLTESTS.unparse ALLTESTS.unparse.expected

testAndOutput:
	@for test in $(UNPARSE); do \
		echo "\n"; \
		echo "TEST $$test"; \
		../ac $$test.a -u $$test.unparse 2> $$test.err; \
		cat $$test.unparse; \
		echo "TEST $$test COMPLETED"; \
	done

%.test:
	@rm -f $*.unparse $*.err
	@touch $*.unparse
	@echo "TEST $*"
	@../ac $*.a -u $*.unparse 2> $*.err ;\
	PROG_EXIT_CODE=$$?;\
	if [ $$PROG_EXIT_CODE != 0 ]; then \
		echo "ac error:"; \
		cat $*.err; \
		exit 1; \
	fi; \
	diff -B --ignore-all-space $*.unparse $*.unparse.expected; \
	STDOUT_DIFF_EXIT=$$?;\
	exit $$STDOUT_DIFF_EXIT || echo "Tests passed"

clean:
	rm -f *.unparse *.err
