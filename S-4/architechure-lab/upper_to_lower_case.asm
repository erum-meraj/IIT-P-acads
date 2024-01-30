.data
	prompt1:.asciiz "Lower case alphabete: "	
	prompt2:.asciiz "The uppercase alphbet is:  "	
	endl:.asciiz "\n"

.text

.globl main

main:
	li $v0, 4 			# Display message to user
	la $a0, prompt1 	
	syscall

	li $v0, 12			# Read input into v0
	syscall
	
	li $a2, 32
	
	sub $t1, $v0, $a2	#substracting the value 32 as it is the difference in the ascii code
				#of any uppercase to its corresponding lowercase
	
	li $v0, 4 			# Display message to user
	la $a0, endl 	
	syscall
	
	li $v0, 4 			# Display message to user
	la $a0, prompt2 	
	syscall
	
	li $v0, 11 			# Display message to user
	la $a0, ($t1)	
	syscall
	
	
	
