.data
	a: .float 4.12
	promt: .asciiz "\n the number is = "
.text
	la $a0, promt
	li $v0, 4
	syscall 
	
	la $a0, a
	l.s $f0, ($a0)
	li $v0, 2
	mov.s $f12, $f0
	syscall
	