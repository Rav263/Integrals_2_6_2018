CXX=gcc
CXXFLAGS=-std=c99 -O2
ADDITIONALFLG=-c

all: main

main: asm functions.o main.c
	${CXX} ${CXXFLAGS} functions.o  main.c -o main -m32 -lm

asm: gen_asm ${SPEC_FILE}
	./gen_asm ${SPEC_FILE} > functions.asm
	nasm -f elf32 functions.asm -o functions.o -D UNIX

gen_asm: gen_asm.c parse_fun.o bind_commands.o
	${CXX} ${CXXFLAGS} gen_asm.c parse_fun.o bind_commands.o -o gen_asm

parse_fun.o: parse_fun.c parse_fun.h
	${CXX} ${CXXFLAGS} ${ADDITIONALFLG} parse_fun.c 

bind_commands.o: bind_commands.c bind_commands.h
	${CXX} ${CXXFLAGS} ${ADDITIONALFLG} bind_commands.c

clean: 
	rm functions.asm main gen_asm *.o
