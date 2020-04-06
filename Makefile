
MODULES_DIRS := bitvector example
FLAGS := -Wall -Wextra -Werror  -Wl,--fatal-warnings

build:
	modules

all: format modules test-all

re: clean all

clean:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) clean -C $$dir;  \
	done

modules:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) -C $$dir; \
	done


test-all:
	cd test && mkdir -p build && cd build && cmake .. && make && ./bitvector_test


format:
	find . -regex '.*\.\(c\|h\)' -exec clang-format -style=file -i {} \;


