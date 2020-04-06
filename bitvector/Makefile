FLAGS :=  -Wall -Wextra -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes \
    -Wold-style-definition -Werror  -Wl,--fatal-warnings


all: build clean

build: bitvector.o libbitvector.a
	mkdir -p ../bin && cp libbitvector.a ../bin/

bitvector.o:
	gcc ${FLAGS} -c bitvector.c -O9

libbitvector.a:
	ar rcs libbitvector.a bitvector.o

clean:
	rm -f bitvector.o libbitvector.a


