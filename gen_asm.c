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
    
    printf("  const%d dq %lf\n", *offset, f1->fun[i].num);
    *offset += 1;
  }
}

void bind_section_data(function *f1, function *f2, function *f3, double a, double b){
  int counter = 2;

  printf("section .data\n");
  printf("  const0 dq %f\n", a);
  printf("  const1 dq %f\n", b);

  bind_fun_data(f1, &counter);
  bind_fun_data(f2, &counter);
  bind_fun_data(f3, &counter);
}

void bind_add(){
  printf("  faddp\n");
}

void bind_sub(){
  printf("  fsubp\n");
}

void bind_div(){
  printf("  fdiv\n");
}

void bind_mul(){
  printf("  fmul\n");
}

void bind_const(int number){
  printf("  fld qword[const%d]\n", number);
}

void bind_varable(){
  printf("  fld qword[ebp + 8]\n");
}

void bind_function(function *fun, int counter){
  printf("f%d:\n", counter);
  printf("  push ebp\n");
  printf("  mov ebp, esp\n");

  int const_offset = 0;

  for(int i = 0; fun->fun[i].type != -1; i++){
    mem now = fun->fun[i];
    if(now.type == 0){
      bind_const(fun->const_offset + const_offset);
      const_offset++;
    }
    if(now.type == 1)bind_varable();
    if(now.type == 2)bind_add();
    if(now.type == 3)bind_sub();
    if(now.type == 4)bind_mul();
    if(now.type == 5)bind_div();
  }

  printf("  mov esp, ebp\n");
  printf("  pop ebp\n");
  printf("  ret\n");
}

void bind_section_text(){
  printf("section .text\n");
}



int main(int argc, char **args){
  if(argc < 2)return 1;
  FILE *file = fopen(args[1], "r");

  mem *f1 = (mem *)malloc(1000 * sizeof(mem));
  mem *f2 = (mem *)malloc(1000 * sizeof(mem));
  mem *f3 = (mem *)malloc(1000 * sizeof(mem));

  double a, b;

  read_file(file, f1, f2, f3, &a, &b);
  
  function fun1 = {f1, 0};
  function fun2 = {f2, 0};
  function fun3 = {f3, 0};

  bind_section_data(&fun1, &fun2, &fun3, a, b);
  bind_section_text();

  bind_function(&fun1, 1);
  bind_function(&fun2, 2);
  bind_function(&fun3, 3);

  free(f1);
  free(f2);
  free(f3);


  return 0;
}
