section	.text
global	_start
_start:
; 	The main program begin
; 	Exit program
	mov eax, 1
	mov ebx, 0
	int 80h

; Data segment
section .data
