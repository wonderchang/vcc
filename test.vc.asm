section	.text
global	_start
_start:
; 	The main program begin
	mov	eax	[b]
	sub	eax	[c]
	mov	[_i1]	eax
	mov	eax	[_i1]
	imul	dword	[y]
	mov	[_i2]	eax
	mov	eax	[d]
	mov	edx
	idiv	dword	[e]
	mov	[_i3]	eax
	mov	eax	[_i2]
	sub	eax	[_i3]
	mov	[_i4]	eax
	mov	eax	[a]
	add	eax	[_i4]
	mov	[_i5]	eax
	mov	eax	[_i5]
	mov	[x]	eax
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
