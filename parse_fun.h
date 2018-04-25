#ifndef PARSE_FUN
#define PARSE_FUN

typedef struct mem{
  float num;
  int type;
} mem;

void read_file(FILE*, mem*, mem*, mem*, float*, float*);
void print_fun(mem*);

#endif
