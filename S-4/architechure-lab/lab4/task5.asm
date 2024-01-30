.data
arr1: .word 1,2,3,4,5,6,7,8,9,10
arr2: .word 10,9,8,7,6,5,4,3,2,1
n: .word 10
.text

la $a0,arr1
la $a1,arr2
lw $a2,n

li $t0,0
beq $a2,$0, skip
loop: lw $t1, 0($a1)
      ble $t0, 2, else
      lw $t2, -8($a0)
      lw $t3, -4($a0)
      addu $t2, $t2, $t3
      addu $t1,$t2,$t1
    else : sw $t1, 0($a0)
      addiu $a0,$a0,4
      addiu $a1,$a1,4
      addiu $t0,$t0,1
      bne $t0,$a2,loop
skip: