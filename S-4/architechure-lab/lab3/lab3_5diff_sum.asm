      .data
  str:  .asciiz "the answer = "
        .text
          addi $a0, $0, -2    # argument 0 = 2
 	  addi $a0, $0, 2    # argument 0 = 2
	  addi $a1, $0, 3    # argument 1 = 3
	  addi $a2, $0, 4    # argument 2 = 4
	  addi $a3, $0, 5    # argument 3 = 5
	  jal  diffofsums    # call procedure
	  add  $a0, $v0, $0  # y = returned value
	  li $v0 , 4
          #add  $a0, $v0,$0       # integer to print
          syscall          # print it
          li $v0, 10              #exit
	  syscall


# $s0 = result
diffofsums:
  addi $sp, $sp, -4  # make space on stack to   # store one register
  sw  $s0, 0($sp)    # save $s0 on stack                      # no need to save $t0 or $t1
  add $t0, $a0, $a1  # $t0 = f + g
  add $t1, $a2, $a3  # $t1 = h + i
  sub $s0, $t0, $t1  # result = (f + g) - (h + i)
  add $v0, $s0, $0   # put return value in $v0
  lw  $s0, 0($sp)    # restore $s0 from stack
  addi $sp, $sp, 4   # deallocate stack space
  jr  $ra            # return to caller



       
