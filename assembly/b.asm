; TITLE NASM Example (main.asm)

%include “/path/to/my/home/nasm/include/Along32.inc"

newLine EQU 10

%macro printVal 2
push eax
push edx
mov edx, %1
call WriteString
mov eax, [%2]
call WriteInt
sub esp, 4
mov DWORD [esp], newLine
pop eax
call WriteChar
pop edx
pop eax
%endmacro

SECTION .data
outStr: db “The answer is “,0
answer: resd 1

SECTION .text

printAnswer:
printVal outStr, answer
ret

global main

main:
mov DWORD [answer], 42

call printAnswer

ret
