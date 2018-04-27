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
    if(mod(b - a) < eps)return x;
    printf("iterations: %d  %lf %lf %lf %lf %lf %lf\n",iterations, x, now_x, now_b, now_a, a, b); 
    
    if(now_a * now_x <= 0){
     // printf("aa\n");
      b = x;
      continue;
    }
    if(now_b * now_x <= 0){
      //printf("bb\n");
      a = x;
      continue;
    }
  }
  return 0;
}


double integral(double fun(double), double a, double b, double eps){
  int n = 4;
  
  double h = (b - a) / n;


  printf("%lf %lf\n", fun(a), fun(b));

  double I0 = fun(a) + fun(b);
  double I2 = 0;
  double I4 = 0;

  for(int i = 1; i < n; i++){
    if(i % 2 == 0)I2 += fun(a + i * h);
    else I4 += fun(a + i * h); 
  }

  double I = I0 + 2 * I2 + 4 * I4;

  I *= h / 3;
  printf("%lf %lf\n", I, h); 

  for(int j = 0;;j++){
    double N0 = I0;
    double N2 = I2 + I4;
    double N4 = 0;
    n *= 2;
    h /= 2;

    for(int i = 1; i < n; i += 2){
      N4 += fun(a + i * h);
    }

    double now = N0 + 2 * N2 + 4 * N4;
    now *= h / 3;


    double coof = (I - now) / 15;

    printf("iteration: %d %lf %d %lf %lf\n", j, coof, n, now, I);
    if(mod(coof) < eps)return now;
    I0 = N0;
    I2 = N2;
    I4 = N4;
    I = now;

  }
  return I;
}

double some(double x){
  return f3(x) - f2(x);
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
  printf("f1: %lf %lf\n", f1(a), f1(b));
  printf("f1 - f2: %lf, %lf\n", ras_fun(f1, f2, a), ras_fun(f1, f2, b));

  //double c = root(f1, f2, a, b, 0.00001);
  iterations = 0;
  // double d = root(f2, f3, a, b, 0.00001);
  
  double e = integral(f1, a, b, 0.00001);
  
  printf("%lf\n", e);

  //printf("%lf %lf %lf\n", c, 0.2, e);

 

  /*for(;;){

    double c;
    scanf("%lf", &c);

    double d = f1(c);
    double e = f2(c);
    double f = ras_fun(f1, f2, c);

    printf("%lf %lf %lf\n", d, e, f);
  }*/


  //if(a * b < 0)printf("NORMAL %lf\n", a * b);
  //else printf("WTF: %lf\n", a * b);

  
  return 0;
}
