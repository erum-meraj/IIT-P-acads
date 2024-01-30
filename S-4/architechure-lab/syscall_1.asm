.data
    str:  .asciiz "Enter dividend: "
    str1: .asciiz "Enter divisor: "
    str2: .asciiz "\nResult (dividend % divisor): "

.text
    # Prompt for the dividend
    li $v0, 4
    la $a0, str
    syscall

    # Read the dividend
    li $v0, 5
    syscall
    move $t0, $v0

    # Prompt for the divisor
    li $v0, 4
    la $a0, str1
    syscall

    # Read the divisor
    li $v0, 5
    syscall
    move $t1, $v0


    # Perform division and get the remainder (modulo)
    div $t2, $t0, $t1
    mfhi $t2  # Move the remainder to $t2

    # Display the result
    li $v0, 4
    la $a0, str2
    syscall

    # Print the remainder
    li $v0, 1
    move $a0, $t2
    syscall

    # Exit the program
    li $v0, 10
    syscall



