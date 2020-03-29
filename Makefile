
MODULES_DIRS := bitvector
FLAGS := -Wall -Wextra -Werror  -Wl,--fatal-warnings

all: format modules

re: clean all

clean:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) clean -C $$dir;  \
	done

modules:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) -C $$dir; \
	done






format:
	find . -regex '.*\.\(c\|h\)' -exec clang-format -style=file -i {} \;
