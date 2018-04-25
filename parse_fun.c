#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct mem{
  double num;
  int type;
} mem;


int parse_sym(char now){
  if(now == 'x')return 1;
  if(now == '+')return 2;
  if(now == '-')return 3;
  if(now == '*')return 4;
  if(now == '/')return 5;

  if(now == 's')return 6;
  if(now == 't')return 7;
  
  if(now == 'e')return 10;
  if(now == 'p')return 11;

  return -1;
}

void print_fun(mem*);

void read_fun(FILE *file, mem *fun){
  char str[1000];
   fgets(str, 1000, file);

  int len = strlen(str);

  str[len - 1] = 0;
  len--;

  int index = 0;

  for(int i = 0; i < len; i++){
    char now = str[i];
    if(now == ' ')continue;

    if(now >= '0' && now <= '9'){
      double num;
      sscanf(str + i, "%lf", &num);

      fun[index].num  = num;
      fun[index].type = 0;

      index++;
    }

    if(now == 'c'){
      if(str[i + 1] == 't')fun[index].type = 8;
      else if(str[i + 1] == 'o')fun[index].type = 9;
      else continue;
      fun[index].num = 0;
      index++;
    }

    int type = parse_sym(now);
    if(type != -1){
      fun[index].type = type;
      fun[index].num  = 0;

      index++;
    }
    
    for(;i < len; i++){
      if(str[i] == ' ')break;
    }
  }

  fun[index].type = -1;
  fun[index].num = -1;
}


void read_file(FILE *file, mem *f1, mem *f2, mem *f3, double *a, double *b){
  fscanf(file, "%lf %lf", a, b);
  char c;
  fscanf(file, "%c", &c);
 
  read_fun(file, f1);
  read_fun(file, f2);
  read_fun(file, f3);
}


void print_fun(mem *fun){
  for(int i = 0; fun[i].type != -1; i++){
    printf("(%d;%lf) ", fun[i].type, fun[i].num);
  }
  printf("\n");
}



