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
	c123	db	'A'
	b88	db	1
	y2	dd	0
	_s1	db	""
	abc1	dd	123
	def1	dd	123
	c34	db	'B'
	s123	dd	_s2
	x1	dd	0
	b5	db	' '
	s6	dd	_s1
	abc2	dd	34
	_s2	db	"String 123!"
	b99	db	1
	z3	dd	0
	a4	db	' '
	B77	db	1
