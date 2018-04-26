#include <stdio.h>
#include <string.h>

//#include "functions.asm"

double f1(double);
double f2(double);
double f3(double);


int process_flags(char *flg){
  char *now = "-help\0";
  if(strcmp(flg, now) == 0){
    printf("Avalible options:\n");
    printf("    -a    print the abscissas of the intersection points\n");
    printf("    -c    print number of iteration in calculations\n");
    return -1;
  }
  now = "-a";
  if(strcmp(flg, now) == 0)return 1;
  now = "-c";
  if(strcmp(flg, now) == 0)return 2;

  printf("Unavalible option!\n");
  now = "-help";
  return process_flags(now);
}

int main(int argc, char **args){
  int flag = 0;
  if(argc == 2){
    flag = process_flags(args[1]);
    if(flag == -1)return 0;
  }
  double a;

  scanf("%lf", &a);

  double b = f1(a);
  double c = f2(a);
  double d = f3(a);

  printf("%lf %lf %lf\n", b, c, d);
  
  return 0;
}
