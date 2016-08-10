SRCS=$(wildcard *_koan.c)
LLVMS=$(SRCS:_koan.c=_koan.bc) 
OKS=$(SRCS:_koan.c=_koan.ok)
KLEE=~/klee/Release+Asserts/bin/klee
KLEE_FLAGS=-silent-klee-assume -max-memory=1300 -optimize --libc=uclibc --posix-runtime --allow-external-sym-calls
CLANG=clang-3.4
CFLAGS=-Werror=return-type -emit-llvm -D_KLEE_ -I . -I ../../klee/include -c -g
all: $(OKS)

%_koan.ok: %_koan.bc
	@set -e ;\
	ERRFILE=$$(mktemp) ;\
    $(KLEE) $(KLEE_FLAGS) $< 2>$$ERRFILE || exit 1 ;\
	grep ERROR $$ERRFILE || exit 0 ;\
	for failed_test in klee-last/*.assert.err; do [ -e $$failed_test ] && echo 'COUNTEREXAMPLE: ' && ktest-tool `echo $$failed_test | sed -e 's/\.assert\.err/\\.ktest/'` | grep '^object    [^0]' && exit 3; done

%_koan.bc: %_koan.c
	@$(CLANG) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	@rm -rf $(OKS) $(LLVMS) klee-out* klee-last
