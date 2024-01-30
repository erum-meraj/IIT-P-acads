.data
	a: .word  0x87654321
	tdata: .byte 0x87654321
	tdata1: .half 0x87654321
	promt: .asciiz "\n the number is = "
.text
	la $a0, promt
	li $v0, 4
	syscall 
	lb $a0,tdata
	li $v0, 34 
	syscall
		
	li $v0,10
   	syscall

	
