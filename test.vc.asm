section	.text
global	_start
_start:

; 	The main program begin

; 	Minus
	mov	eax,	[b]
	sub	eax,	[c]
	mov	[_i1],	eax

; 	Plus
	mov	eax,	[a]
	add	eax,	[_i1]
	mov	[_i2],	eax

; 	Assigment
	mov	eax,	[_i2]
	mov	[x],	eax

; 	Exit program
	mov eax, 1
	mov ebx, 0
	int 80h


; Data segment
section .data
	c:	dd	3
	x:	dd	0
	_i1:	dd	0
	_s1:	db	""
	a:	dd	1
	_i2:	dd	0
	b:	dd	8
