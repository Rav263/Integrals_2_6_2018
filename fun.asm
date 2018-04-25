%include 'io.inc'

section .data
  const0 dq 2.200000
  const1 dq 3.100000
  const2 dq 1.000000
  const3 dq 10.000000
  const4 dq 5.000000
  const5 dq 3.000000
  const6 dq 3.000000

section .rodata
  output db "%lf", 10, 0
  input  db "%lf", 0


section .bss
  a resd 1
  b resq 1
 
section .text
global CMAIN
CMAIN:
  push ebp
  mov ebp, esp

  and esp, -16
  sub esp, 16

  mov dword[esp], input
  mov dword[esp + 4], b
  call scanf
  
  finit

  push dword[b + 4]
  push dword[b]
  call f1
  add esp, 8

  mov dword[esp], output
  fstp qword[esp + 4]
  call printf

  call f2

  mov dword[esp], output
  fstp qword[esp + 4]
  call printf

  push dword[b + 4]
  push dword[b]
  call f3
  add esp, 8

  mov dword[esp], output
  fstp qword[esp + 4]
  call printf

  xor eax, eax
  mov esp, ebp
  pop ebp
  ret

f1:
  push ebp
  mov ebp, esp
  fld qword[const2]
  fld qword[ebp + 8]
  faddp
  mov esp, ebp
  pop ebp
  ret
f2:
  push ebp
  mov ebp, esp
  fld qword[const3]
  fld qword[const4]
  fsubp
  fld qword[const5]
  faddp
  mov esp, ebp
  pop ebp
  ret
f3:
  push ebp
  mov ebp, esp
  fld qword[ebp + 8]
  fld qword[const6]
  fdiv
  mov esp, ebp
  pop ebp
  ret
