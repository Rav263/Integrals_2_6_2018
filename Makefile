CXX=gcc
CXXFLAGS=-std=c99 -O2

all: main

main: asm
	${CXX} ${CXXFLAGS} main.c -o main


gen_asm: gen_asm.c ${SPEC_FILE} 
	${CXX} ${CXXFLAGS} gen_asm.c -o gen_asm

asm: gen_asm
	./gen_asm ${SPEC_FILE} > functions.asm
	rm gen_asm


clear: 
	rm functioins.asm main
