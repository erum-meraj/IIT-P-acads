      .data
      mydata: .word 1,2,3
     str:  .asciiz " Array initialized "
      final: .word 1
        .text
          addi $s0, $0, 0    # argument i = 0
 	 # addi $s1, $0, 0    # asum= 0 
	  addi $s2, $0, 10   # argument 1 = 3
	  la $t1, mydata
	loop:  beq $s2, $t1, exit    # argument 2 = 4
	  sw  $s0, 0($t1)
	  addi $t1, $t1, 1    # argument 3 = 5
	  j loop
	  add  $a0, $s1, $0  # y = returned value
	  li $v0 , 4
          #add  $a0, $v0,$0       # integer to print
     exit:
          li $v0, 10              #exit
	  syscall

.data
      str:  .asciiz "Array initialized"	
 
      mydata: .word 1,2,3
      
     
      data11: .space 100
      
      final: .word 1
        .text
          addi $s0, $0, 0    # argument i = 0
 	  addi $s1, $0, 0    # asum= 0 
	  addi $s2, $0, 10   # argument 1 = 3
	  la $s1, mydata
	loop:  beq $s2, $s0, exit0    # argument 2 = 4
	  sw  $s0, 0($s1)
	  addi $s1, $s1, 4    # argument 3 = 5
	  addi $s0, $s0,1
	  j loop
  exit0:  la  $a0, str  # msg
	  li $v0 , 4
          syscall
     exit:
          li $v0, 10              #exit
	  syscall

    
