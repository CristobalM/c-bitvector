
CURRENT_PATH=$(shell pwd)

MODULES_DIRS := src example
CFLAGS :=  -Wall -Wextra -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes \
    -Wold-style-definition -Werror -O3

VERY_LIGHT := -D VERY_LIGHT_FIELDS
LIGHT := -D LIGHT_FIELDS

INCLUDES=-I${CURRENT_PATH}/include

MAKE_FLAGS=CFLAGS="${CFLAGS}" INCLUDES="${INCLUDES}"
VERY_LIGHT_FLAGS=CFLAGS="${CFLAGS} ${VERY_LIGHT}" INCLUDES="${INCLUDES}"
LIGHT_FLAGS=CFLAGS="${CFLAGS} ${LIGHT}" INCLUDES="${INCLUDES}"

build: modules

all: format modules test-all

all-light: format light-modules test-all

all-very-light: format very-light-modules test-all

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


light-modules:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) -C $$dir ${LIGHT_FLAGS}; \
	done


very-light-modules:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) -C $$dir ${VERY_LIGHT_FLAGS}; \
	done

test-all:
	cd test && mkdir -p build && cd build && cmake .. && make && ./bitvector_test


format:
	find . -regex '.*\.\(c\|h\)' -exec clang-format -style=file -i {} \;

clean-all: clean
	rm -rf bin