	.arch msp430g2553

	.data
state:				;state
	.word 0

	.text
jt:				;jump table
	.word case0
	.word case1
	.word case2
	.word case3
	.word case4

	
	.global toggle

toggle:
	cmp #8, &state 		;range check
	mov &state, r12		;moves state into r12
	add r12, r12		;add r12 into r12 
	mov jt(r12), r0		;start at first in jt

case0:

/*	mov.b #0, &green_on		
	mov.b #0, &red_on*/
	mov #1, &state			;set state to 1 to go to case1
	jmp end

case1:
	mov.b #0, &green_on		;set green led to be off
	mov.b #0, &red_on		;set red led to be off
	mov #2, &state			;set state to 2 so that it moves to case2
	jmp end

case2:
	mov.b #1, &green_on
	mov.b #0, &red_on
	mov #3, &state
	jmp end

case3:
	mov.b #0, &green_on
	mov.b #1, &red_on
	mov #4, &state
	jmp end

case4:	
	mov.b #1, &green_on
	mov.b #1, &red_on
	mov #1, &state
	jmp end



end:	 ret		
/*
case_zero:

	mov.b #0, &red_on
	mov.b #1, &green_on
	jmp case1
	
case_one:
	mov.b #1, &red_on
	mov.b #0, &green_on
	jmp case0
	
*/

	/*some functions in assembly*/
	.global togger_red
toggle_red:
	xor.b #1, red_on
	mov.b #0, green_on
	jmp end
	.global togge_green
toggle_green:
	xor.b #1, green_on
	mov.b #0, red_on
	jmp end
