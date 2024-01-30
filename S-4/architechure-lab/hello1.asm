.data
string1: .asciiz "Hellow World:\n"
string2: .asciiz "Second Hello World: \n"
string3: .asciiz "Third Hello World:\n"
endLine: .asciiz "\n"

.text
main:

	li $v0 , 4				#print string1 
	la $a0 , string1  
	syscall

		
	li $v0 , 4
	la $a0 , string2        
	syscall
	
		
		 
	li $v0, 10              #exit
	syscall
