.data
	a: .double 4.12111
	promt: .asciiz "\n the number is = "
.text
	la $a0, promt
	li $v0, 4
	syscall 
	
	la $a0, a
	l.d $f0, ($a0)
	li $v0, 3
	mov.d $f12, $f0
	syscall
	