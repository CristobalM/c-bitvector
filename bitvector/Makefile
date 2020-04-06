FLAGS :=  -Wall -Wextra -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes \
    -Wold-style-definition -Werror  -Wl,--fatal-warnings

all: bitvector.o bitvector.a
	

bitvector.o: bitvector.h bitvector.c
	gcc ${FLAGS} -c bitvector.h bitvector.c -O9

bitvector.a:
	ar rcs bitvector.a bitvector.o

clean:
	rm -f bitvector.h.gch bitvector.o bitvector.a

