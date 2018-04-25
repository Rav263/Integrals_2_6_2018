#ifndef PARSE_FUN
#define PARSE_FUN

typedef struct mem{
  double num;
  int type;
} mem;

void read_file(FILE*, mem*, mem*, mem*, double*, double*);
void print_fun(mem*);

#endif
