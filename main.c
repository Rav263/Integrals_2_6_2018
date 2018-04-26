#include <stdio.h>
#include <string.h>

//#include "functions.asm"

double f1(double);
double f2(double);
double f3(double);
double get_a();
double get_b();


int iterations = 0;

int process_flags(char *flg){
  char *now = "-help\0";
  if(strcmp(flg, now) == 0){
    printf("Avalible options:\n");
    printf("    -a    print the abscissas of the intersection points\n");
    printf("    -c    print number of iteration in calculations\n");
    printf("    -help print this message\n");
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

double ras_fun(double fun1(double), double fun2(double), double now){
  return fun1(now) - fun2(now);
}

double mod(double a){
  return a < 0 ? -a: a;
}


double root(double fun1(double), double fun2(double), double a, double b, double eps){
  for(;;iterations++){
    double x = a + (b - a) / 2;
    double now_a = ras_fun(fun1, fun2, a);
    double now_b = ras_fun(fun1, fun2, b);
    double now_x = ras_fun(fun1, fun2, x);

    if(mod(now_x) < eps)return x;
    printf("iterations: %d  %lf %lf %lf %lf %lf %lf\n",iterations, x, now_x, now_b, now_a, a, b); 
    
    if(now_a * now_x <= 0){
      printf("aa\n");
      b = x;
      continue;
    }
    if(now_b * now_x <= 0){
      printf("bb\n");
      a = x;
      continue;
    }
  }
  return 0;
}



int main(int argc, char **args){
  int flag = 0;
  if(argc == 2){
    flag = process_flags(args[1]);
    if(flag == -1)return 0;
  }

  double a = get_a();
  double b = get_b();

  printf("%lf %lf\n", a, b);

  double c = root(f1, f2, a, b, 0.00001);
  iterations = 0;
  double d = root(f2, f3, a, b, 0.00001);

  if(a * b < 0)printf("NORMAL %lf\n", a * b);
  else printf("WTF: %lf\n", a * b);

  printf("%lf %lf\n", c, d);
  
  return 0;
}
