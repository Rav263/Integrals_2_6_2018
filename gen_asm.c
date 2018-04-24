#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct mem{
  float num;
  int type;
} mem;


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
      float num;
      sscanf(str + i, "%f", &num);

      fun[index].num  = num;
      fun[index].type = 0;

      index++;

      for(;i < len; i++){
        if(str[i] == ' ')break;
      }
      continue;
    }

    if(now == 'x'){
      fun[index].type = 1;
      index++;
    }
  }

  for(int i = 0; i < index; i++){
    printf("%f ", fun[i].num);
  }
  printf("\n");
}


void read_file(FILE *file, mem *f1, mem *f2, mem *f3, float *a, float *b){
  fscanf(file, "%f %f", a, b);
  char c;
  fscanf(file, "%c", &c);
 
  read_fun(file, f1);
  read_fun(file, f2);
  read_fun(file, f3);
}



int main(int argc, char **args){
  if(argc < 2)return 1;
  FILE *file = fopen(args[1], "r");

  mem *f1 = (mem *)malloc(1000 * sizeof(mem));
  mem *f2 = (mem *)malloc(1000 * sizeof(mem));
  mem *f3 = (mem *)malloc(1000 * sizeof(mem));

  float a, b;

  read_file(file, f1, f2, f3, &a, &b);

  printf("%f %f\n", a, b);


  free(f1);
  free(f2);
  free(f3);


  return 0;
}
