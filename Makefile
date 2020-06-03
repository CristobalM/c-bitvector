
CURRENT_PATH=$(shell pwd)

MODULES_DIRS := src example
CFLAGS :=  -Wall -Wextra -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes \
    -Wold-style-definition -Werror -O3

DEBFLAGS :=  -Wall -Wextra -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes \
    -Wold-style-definition -Werror -g

INCLUDES=-I${CURRENT_PATH}/include

MAKE_FLAGS=CFLAGS="${CFLAGS}" INCLUDES="${INCLUDES}"
DEBUG_FLAGS=CFLAGS="${DEBFLAGS}" INCLUDES="${INCLUDES}"

build: modules

all: format modules test-all

re: clean all

clean:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) clean -C $$dir;  \
	done

	rm -rf test/build/

modules:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) -C $$dir ${MAKE_FLAGS}; \
	done

debug:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) -C $$dir ${DEBUG_FLAGS}; \
	done

test-all:
	cd test && mkdir -p build && cd build && cmake .. && make && ./bitvector_test


format:
	find . -regex '.*\.\(c\|h\)' -exec clang-format -style=file -i {} \;

clean-all: clean
	rm -rf bin