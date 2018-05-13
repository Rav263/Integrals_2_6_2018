#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse_fun.h"
#include "bind_commands.h"


typedef struct function{ //структура, которая описывает функцию
  mem *fun;
  int const_offset;
} function;


void bind_fun_data(function *f1, int *offset){  //Функиця забивает константы из функций в секцию дата
  f1 -> const_offset = *offset;

  for(int i = 0; f1->fun[i].type != -1; i++){
    if(f1->fun[i].type != 0)continue;
    
    printf("  const%d dq %lf\n", *offset, f1->fun[i].num);
    *offset += 1;
  }
}

void bind_section_data(function *f1, function *f2, function *f3, double a, double b){ //функция пишущая секцию дата
  int counter = 2;

  printf("section .rodata\n");
  printf("  const0 dq %f\n", a); //шраницы отрезков
  printf("  const1 dq %f\n", b);
  printf("  constE dq 2.718281825\n"); //число exp

  bind_fun_data(f1, &counter);
  bind_fun_data(f2, &counter);
  bind_fun_data(f3, &counter);
}

void bind_function(function *fun, int counter){ //функция, которая принимает на вход структуру описания алгебраической функции и пишет её ассемблерный код
  printf("global f%d\n", counter); //Стандартное начало функции для соглашения cdecl
  printf("f%d:\n", counter);
  printf("  push ebp\n");
  printf("  mov ebp, esp\n");
  printf("  finit\n");


  int const_offset = 0;

  for(int i = 0; fun->fun[i].type != -1; i++){
    mem now = fun->fun[i];
    if(now.type == 0){
      bind_const(fun->const_offset + const_offset);
      const_offset++;
    }
    //Далее происходит написание функций, в зависимости от типа указанного в структуре
    if(now.type == 1)bind_varable();
    if(now.type == 2)bind_add();
    if(now.type == 3)bind_sub();
    if(now.type == 4)bind_mul();
    if(now.type == 5)bind_div();
    if(now.type == 6)bind_sin();
    if(now.type == 7)bind_tan();
    if(now.type == 8)bind_ctn();
    if(now.type == 9)bind_cos();
    if(now.type == 10)bind_exp();
    if(now.type == 11)bind_pi();
  }

  //стандартный эпилог
  printf("  mov esp, ebp\n");
  printf("  pop ebp\n");
  printf("  ret\n");
  printf("\n");
}


int main(int argc, char **args){
  if(argc < 2)return 1;
  FILE *file = fopen(args[1], "r"); //Открытие файла, поданного на вход с описанием функций 

  mem *f1 = (mem *)malloc(1000 * sizeof(mem)); //Выделение памяти под структуры функций
  mem *f2 = (mem *)malloc(1000 * sizeof(mem));
  mem *f3 = (mem *)malloc(1000 * sizeof(mem));

  double a, b;

  read_file(file, f1, f2, f3, &a, &b); //Разбор функиций из файла и запись их в соответствующие структуры
  
  function fun1 = {f1, 0};
  function fun2 = {f2, 0};
  function fun3 = {f3, 0};

  bind_section_data(&fun1, &fun2, &fun3, a, b); //Запись секции дата
  bind_section_text(); //Пролог секции текст

  bind_function(&fun1, 1); //запись функций из файла
  bind_function(&fun2, 2);
  bind_function(&fun3, 3);
  bind_get_a(); //Запись функий для получения границ
  bind_get_b();

  free(f1); //очищение памяти
  free(f2);
  free(f3);


  return 0;
}
