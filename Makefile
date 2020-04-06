
MODULES_DIRS := bitvector example
CFLAGS :=  -Wall -Wextra -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes \
    -Wold-style-definition -Werror

MAKE_FLAGS=CFLAGS="${CFLAGS}"

build: modules

all: format modules test-all

re: clean all

clean:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) clean -C $$dir ${MAKE_FLAGS};  \
	done

	rm -rf test/build/

modules:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) -C $$dir ${MAKE_FLAGS}; \
	done


test-all:
	cd test && mkdir -p build && cd build && cmake .. && make && ./bitvector_test


format:
	find . -regex '.*\.\(c\|h\)' -exec clang-format -style=file -i {} \;

cleanall: clean
	rm -rf bin