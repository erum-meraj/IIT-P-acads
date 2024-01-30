.data
	promt: .asciiz "\n the number is = "
.text
	la $a0, promt
	li $v0, 4
	syscall 
	