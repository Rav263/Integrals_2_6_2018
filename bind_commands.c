#include <stdio.h>
#include <stdlib.h>


void bind_add(){
  printf("  faddp\n");
}

void bind_sub(){
  printf("  fsubp\n");
}

void bind_div(){
  printf("  fdiv\n");
}

void bind_mul(){
  printf("  fmul\n");
}

void bind_sin(){
  printf("  fsin\n");
}

void bind_cos(){
  printf("  fcos\n");
}

void bind_tan(){
  printf("  fptan\n");
}

void bind_ctn(){
  printf("  fsincos\n");
  printf("  fdivrp\n");
}

void bind_pi(){
  printf("  fldpi\n");
}

void bind_exp(){
  printf("  fld qword[constExp]\n"); 
}

void bind_const(int number){
  printf("  fld qword[const%d]\n", number);
}

void bind_varable(){
  printf("  fld qword[ebp + 8]\n");
}

void bind_section_text(){
  printf("section .text\n");
}
