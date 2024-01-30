.data
	str: .asciiz "input age= "
	str1: .asciiz "\noutput age after 10 years= "

	
.text

	la $a0, str
	li $v0, 4
	syscall

#taking input
	li $v0, 5
	syscall
	move $t0, $v0 
	
#prep to print output
	la $a0, str1
	li $v0, 4
	syscall

#output
	addi $t0, $t0, 10
	move $a0, $t0
	li $v0, 1
	syscall
	
	