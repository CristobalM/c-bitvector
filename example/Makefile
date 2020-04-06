all: example1

INCLUDE_PATH=../include
BIN_PATH=../bin

example1: example1.c
	gcc example1.c  -o example1 -I${INCLUDE_PATH} -L${BIN_PATH} -lbitvector 


clean:
	rm -f example1
