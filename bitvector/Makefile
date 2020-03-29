FLAGS :=  -Wall -Wextra -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes \
    -Wold-style-definition -Werror  -Wl,--fatal-warnings

bitvector.o: bitvector.h bitvector.c
	gcc ${FLAGS} -c bitvector.h bitvector.c 

clean:
	rm -f bitvector.h.gch bitvector.o

all:
	bitvector.o