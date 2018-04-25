#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse_fun.h"

typedef struct function{
  mem *fun;
  int const_offset;
} function;


void bind_fun_data(function *f1, int *offset){
  f1 -> const_offset = *offset;

  for(int i = 0; f1->fun[i].type != -1; i++){
    if(f1->fun[i].type != 0)continue;
    
    printf("  const%d db %f\n", *offset, f1->fun[i].num);
    *offset += 1;
  }
}

void bind_section_data(function *f1, function *f2, function *f3, float a, float b){
  int counter = 2;

  printf("section .data\n");
  printf("  const0 db %f\n", a);
  printf("  const1 db %f\n", b);

  bind_fun_data(f1, &counter);
  bind_fun_data(f2, &counter);
  bind_fun_data(f3, &counter);
}



int main(int argc, char **args){
  if(argc < 2)return 1;
  FILE *file = fopen(args[1], "r");

  mem *f1 = (mem *)malloc(1000 * sizeof(mem));
  mem *f2 = (mem *)malloc(1000 * sizeof(mem));
  mem *f3 = (mem *)malloc(1000 * sizeof(mem));

  float a, b;

  read_file(file, f1, f2, f3, &a, &b);
  
  function fun1 = {f1, 0};
  function fun2 = {f2, 0};
  function fun3 = {f3, 0};

  bind_section_data(&fun1, &fun2, &fun3, a, b);


  free(f1);
  free(f2);
  free(f3);


  return 0;
}
