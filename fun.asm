%include 'io.inc'

section .data
  const0 db 2.200000
  const1 db 3.100000
  const2 db 1.000000
  const3 db 10.000000
  const4 db 5.000000
  const5 db 3.000000
  const6 db 3.000000

section .rodata
  output db "%f", 10, 0

section .text
global CMAIN
CMAIN:
  push ebp
  mov ebp, esp

  and esp, -16
  sub esp, 16

  GET_DEC 4, ebx
  
  finit

  push ebx
  call f1
  add esp, 4

  mov dword[esp], output
  fstp dword[esp + 4]
  call printf

  call f2

  mov dword[esp], output
  fstp dword[esp + 4]
  call printf

  push ebx
  call f3
  add esp, 4

  mov dword[esp], output
  fstp dword[esp + 4]
  call printf

  xor eax, eax
  mov esp, ebp
  pop ebp
  ret

f1:
  push ebp
  mov ebp, esp
  fld dword[const2]
  fld dword[ebp + 8]
  faddp
  mov esp, ebp
  pop ebp
  ret
f2:
  push ebp
  mov ebp, esp
  fld dword[const3]
  fld dword[const4]
  fsubp
  fld dword[const5]
  faddp
  mov esp, ebp
  pop ebp
  ret
f3:
  push ebp
  mov ebp, esp
  fld dword[ebp + 8]
  fld dword[const6]
 fdiv
  mov esp, ebp
  pop ebp
  ret
