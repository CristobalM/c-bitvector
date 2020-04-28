ROOT_PATH=$(shell pwd)/..

all: build clean

build: libbitvector.a libbitvector_se.a
	mkdir -p ${ROOT_PATH}/bin && cp libbitvector.a ${ROOT_PATH}/bin/
	cp libbitvector_se.a ${ROOT_PATH}/bin/

bitvector.o: bitvector.c
	$(CC) ${CFLAGS} -c bitvector.c -o bitvector.o

bitvector_se.o: bitvector.c
	$(CC) -fPIC ${CFLAGS} -c bitvector.c -o bitvector_se.o

libbitvector.a: bitvector.o
	ar rcs libbitvector.a bitvector.o

libbitvector_se.a: bitvector_se.o
	ar rcs libbitvector_se.a bitvector_se.o

clean:
	rm -f bitvector.o bitvector_se.o libbitvector.a libbitvector_se.a
