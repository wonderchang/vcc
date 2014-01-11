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
	c	dd	3
	x	dd	0
	_i1	dd	0
	_i4	dd	0
	_s1	db	""
	a	dd	1
	d	dd	4
	y	dd	10
	_i2	dd	0
	_i5	dd	0
	b	dd	2
	e	dd	5
	_i3	dd	0
