CXX=gcc
CXXFLAGS=-std=c99 -O2

all: main

main: asm
	${CXX} ${CXXFLAGS} main.c -o main


gen_asm: gen_asm.c ${SPEC_FILE} parse_fun.c parse_fun.h
	${CXX} ${CXXFLAGS} gen_asm.c parse_fun.c -o gen_asm

asm: gen_asm
	./gen_asm ${SPEC_FILE} > functions.asm
	rm gen_asm

clear: 
	rm functioins.asm main
