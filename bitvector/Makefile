ROOT_PATH=$(shell pwd)/..

all: build clean

build: bitvector.o libbitvector.a
	mkdir -p ${ROOT_PATH}/bin && cp libbitvector.a ${ROOT_PATH}/bin/

bitvector.o: bitvector.c
	$(CC) ${CFLAGS} -c bitvector.c -O9 -o bitvector.o

libbitvector.a:
	ar rcs libbitvector.a bitvector.o

clean:
	rm -f bitvector.o libbitvector.a


