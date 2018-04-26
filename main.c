#include <stdio.h>

//#include "functions.asm"

double f1(double);
double f2(double);
double f3(double);

int main(void){
  double a;

  scanf("%lf", &a);

  double b = f1(a);
  double c = f2(a);
  double d = f3(a);

  printf("%lf %lf %lf\n", b, c, d);
  
  return 0;
}
