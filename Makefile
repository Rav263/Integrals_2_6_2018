CXX=gcc
CXXFLAGS=-std=c99 -O2
ADDITIONALFLG=-c

all: main

main: asm 
	${CXX} ${CXXFLAGS} functions.o  main.c -o main -m32
	rm functions.o

asm: gen_asm
	./gen_asm ${SPEC_FILE} > functions.asm
	nasm -g -f elf32 functions.asm -o functions.o -D UNIX
	rm gen_asm

gen_asm: gen_asm.c ${SPEC_FILE} parse_fun bind_commands
	${CXX} ${CXXFLAGS} gen_asm.c parse_fun.o bind_commands.o -o gen_asm
	rm parse_fun.o bind_commands.o

parse_fun: parse_fun.c parse_fun.h
	${CXX} ${CXXFLAGS} ${ADDITIONALFLG} parse_fun.c 

bind_commands: bind_commands.c bind_commands.h
	${CXX} ${CXXFLAGS} ${ADDITIONALFLG} bind_commands.c

clear: 
	rm functioins.asm main
