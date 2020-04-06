FLAGS :=  -Wall -Wextra -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes \
    -Wold-style-definition -Werror  -Wl,--fatal-warnings

all: bitvector.o libbitvector.a
	

bitvector.o: bitvector.h bitvector.c
	gcc ${FLAGS} -c bitvector.h bitvector.c -O9

libbitvector.a:
	ar rcs libbitvector.a bitvector.o

clean:
	rm -f bitvector.h.gch bitvector.o libbitvector.a

