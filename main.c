#include <stdio.h>
#include <string.h>
#include <math.h>


//#include "functions.asm"

double f1(double); //Объявление ассемблерных функций
double f2(double);
double f3(double);
double get_a();
double get_b();


int iterations = 0; //счётчик итераций

int process_flags(char *flg){ //Функция для разбора поданных на вход флагов
  char *now = "-help\0";
  if(strcmp(flg, now) == 0){
    printf("Avalible options:\n");
    printf("    -a          print the abscissas of the intersection points\n");
    printf("    -c          print number of iteration in calculations\n");
    printf("    -testRoot   test root function\n");
    printf("    -testInteg  test integral function\n");
    printf("    -help       print this message\n");
    return -1;
  }
  now = "-a";
  if(strcmp(flg, now) == 0)return 1;
  now = "-c";
  if(strcmp(flg, now) == 0)return 2;
  now = "-testRoot";
  if(strcmp(flg, now) == 0)return 4;
  now = "-testInteg";
  if(strcmp(flg, now) == 0)return 5;


  printf("Unavalible option!\n");
  now = "-help";
  return process_flags(now);
}

double ras_fun(double fun1(double), double fun2(double), double now){ //Разность двух функций
  return fun1(now) - fun2(now);
}

double mod(double a){
  return a < 0 ? -a: a;
}


double root(double fun1(double), double fun2(double), double a, double b, double eps){ //Функция поиска корня
  for(;;iterations++){
    double x = a + (b - a) / 2; //Выбераем текущую середину отрезка
    double now_a = ras_fun(fun1, fun2, a); //Значения в важных точках
    double now_b = ras_fun(fun1, fun2, b);
    double now_x = ras_fun(fun1, fun2, x);

    //if(mod(now_x) < eps)return round(x / eps) * eps; //Если x корень
    if(mod(b - a) < eps)return round(x / eps) * eps; //Если отрезок стал достаточно малым
    //printf("iterations: %d  %lf %lf %lf %lf %lf %lf\n",iterations, x, now_x, now_b, now_a, a, b); 
    
    if(now_a * now_x <= 0){ //Выюор нужной половины отрезка
      b = x; 
      continue;
    }
    if(now_b * now_x <= 0){
      a = x;
      continue;
    }
  }
  return 0;
}


double integral(double fun(double), double a, double b, double eps){ // Функция поиска интеграла
  int n = 4; //Количество разбиений
  double h = (b - a) / n; //Шаг
  double I0 = fun(a) + fun(b); //Значения входящие с коэффицентом 0 в интегральную сумму
  double I2 = 0; //С коэффицентом 2
  double I4 = 0; //С коэффицентом 3

  for(int i = 1; i < n; i++){
    if(i % 2 == 0)I2 += fun(a + i * h);
    else I4 += fun(a + i * h); 
  }

  double I = I0 + 2 * I2 + 4 * I4; //Начальное значение

  I *= h / 3;

  for(int j = 0;;j++){
    double N0 = I0; //Элементы суммы нового этапа приблежения
    double N2 = I2 + I4;
    double N4 = 0;
    n *= 2;
    h /= 2;

    for(int i = 1; i < n; i += 2){
      N4 += fun(a + i * h); //Досчитывание оставшихся
    }

    double now = N0 + 2 * N2 + 4 * N4; //Новая интегральная сумма
    now *= h / 3;


    double coof = (I - now) / 15; //Правило Рунге
    //printf("iteration: %d %lf %d %lf %lf\n", j, coof, n, now, I);
    if(mod(coof) < eps)return round(now / eps) * eps; //Если удовлетворяет ему 
    I0 = N0;
    I2 = N2;
    I4 = N4;
    I = now;
  }

  return I;
}


double f1f2(double x){
  return f1(x) - f2(x);
}

double f1f3(double x){
  return f1(x) - f3(x);
}

double f2f3(double x){
  return f2(x) - f3(x);
}

double zero_fun(double x){
  return 0.0;
}


int main(int argc, char **args){
  int flag = 0;  //Обработка флагов
  if(argc >= 2){
    flag = process_flags(args[1]);
    int flg = 0;
    if(argc >= 3){
      flg = process_flags(args[2]);
      if(flg == -1)return 0;
    }
    if(flag == -1)return 0;
    if(flg != flag && !(flg == 0 || flag == 0))flag = 3; 
  }

  double eps;
  printf("Please, enter the eps: ");
  scanf("%lf", &eps);
  double eps1 = eps/100;
  double eps2 = eps/10;

  // Получение границ отрезка
  double a = get_a();
  double b = get_b();

  if(flag == 4){
    iterations = 0;
    double x1 = root(f1, zero_fun, a, b, eps1);
    printf("f1: Iterations: %d, root: %lf\n", iterations, x1);

    iterations = 0;
    double x2 = root(f2, zero_fun, a, b, eps1);
    printf("f2: Iterations: %d, root: %lf\n", iterations, x2);

    iterations = 0;
    double x3 = root(f3, zero_fun, a, b, eps1);
    printf("f3: Iterations: %d, root: %lf\n", iterations, x3);
    return 0;
  }

  if(flag == 5){
    double I1 = integral(f1, a, b, eps2);
    printf("f1: %lf\n", I1);
    double I2 = integral(f2, a, b, eps2);
    printf("f2: %lf\n", I2);
    double I3 = integral(f3, a, b, eps2);
    printf("f3: %lf\n", I3);
    return 0;
  }



  // Вычисления точек пересечения трёх функций
  iterations = 0;
  double x1 = root(f1, f2, a, b, eps1);
  if(flag == 2 || flag == 3)printf("Iterations of root search f1 = f2: %d\n", iterations);

  iterations = 0;
  double x2 = root(f1, f3, a, b, eps1);
  if(flag == 2 || flag == 3)printf("Iterations of root search f1 = f3: %d\n", iterations);
  
  iterations = 0;
  double x3 = root(f2, f3, a, b, eps1);
  if(flag == 2 || flag == 3)printf("Iterations of root search f2 = f3: %d\n", iterations);


  if(flag == 1 || flag == 3)
    printf("The abcissies and ordinates of roots\n  f1 = f2: %lf %lf\n  f1 = f3: %lf %lf\n  f2 = f3: %lf %lf\n", x1, f1(x1), x2, f1(x2), x3, f2(x3));



  //Вычисление площади

  double res = 0;

  if(x1 < x2 && x2 < x3){
    double fir = mod(integral(f1f2, x1, x2, eps2));
    double sec = mod(integral(f2f3, x2, x3, eps2));
    res = fir + sec;
  }

  if(x2 < x1 && x1 < x3){
    double fir = mod(integral(f1f3, x2, x1, eps2));
    double sec = mod(integral(f2f3, x1, x3, eps2));
    res = fir + sec;
  }

  if(x3 < x1 && x1 < x2){
    double fir = mod(integral(f2f3, x3, x1, eps2));
    double sec = mod(integral(f1f3, x1, x2, eps2));
    res = fir + sec;
  }

  if(x3 < x2 && x2 < x1){
    double fir = mod(integral(f2f3, x3, x2, eps2));
    double sec = mod(integral(f1f3, x2, x1, eps2));
    res = fir + sec;
  }

  if(x1 < x3 && x3 < x2){
    double fir = mod(integral(f1f2, x1, x3, eps2));
    double sec = mod(integral(f1f3, x3, x2, eps2));
    res = fir + sec;
  }

  if(x2 < x3 && x3 < x1){
    double fir = mod(integral(f1f3, x2, x3, eps2));
    double sec = mod(integral(f1f2, x3, x1, eps2));
    res = fir + sec;
  }

  printf("The square of figure: %lf\n", res);
  
  return 0;
}
