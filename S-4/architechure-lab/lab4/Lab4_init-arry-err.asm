
    .data
       str:  .asciiz " Array initialized "
      mydata: .word 1,2,3
    
      final: .word 1
        .text
          addi $s0, $0, 0    # argument i = 0
 	  addi $s1, $0, 0    # = 0 
	  addi $s2, $0, 10   # argument 
	  la $s0, mydata
	loop:  beq $s1, $s2, exit    # a
	  sw  $s1, 0($s0)
	  addi $s0, $s0, 4    # argument 
	  add  $s1, $s1, 1
	  j loop
	  add  $a0, $s1, $0  # 
	  li $v0 , 4
          #add  $a0, $v0,$0       # integer to print
     exit:
          li $v0, 10              #exit
	  syscall
