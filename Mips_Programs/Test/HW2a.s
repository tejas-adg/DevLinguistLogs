.text
## Main is a test case for the SumFunc internal function. 
# In memory, are the value A and the value B. 
# The compute sum will be stored in memory at Result.

main:	la $t0, A 		#loads address of A
		la $t1, B		#loads address of B
		la $t3, Result	#loads address of Result
		move $a0, $t0	#address of A is input to SumFunc
		move $a1, $t1	#address of B input to SumFunc
		addi $sp, $sp, -4
		jal SumFunc		#calls SumFunc
		addi $sp, $sp, 4
		sw $v0, 0($t3)	#saves sum into Result

##SumFunc takes two inputs
# ($a0 –address of A, $a1- address of B) 
# and returns a value in $v0 
# returned is the sum of the values at those memory locations

SumFunc:
		sw $ra, 0($sp)
		move $s0, $a0 	#moves addr of A into saved register
		move $s1, $a1	#moves addr of B into saved register
		move $a0, $s0	#addr of A is input to 1st LoadFunc call

		jal LoadFunc	#call LoadFunc to get value of A

		move $s0, $v0	#moves returned value to $s0 
						#(this is now the value of A)
		move $a0, $s1 	#base addr of array is AddressFunc input

		jal LoadFunc	#call LoadFunc to get value of B

		move $s1, $v0	#moves returned value to $s0 
						#(this is now the value of B)
		add $s1, $s1, $s0	#adds the two values together 
		move $v0, $s1		#return sum as output of SumFunc 
		lw $ra, 0($sp)
		jr $ra			# return to main

## AddressFunc takes one input ($a0 – address of value) 
# and returns a value in $v0 – the value at addr passed in

LoadFunc:
		lw $v0, 0($a0)	#loads value of address 
		jr $ra			#return to SumFunc

.data		# User Data segment
A: 		.word 5
B: 		.word 7
Result:	.word 0
