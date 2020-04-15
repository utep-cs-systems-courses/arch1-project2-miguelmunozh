	.arch msp430g2553

/*assembly for binary count 0-3 */
	
	.data			;in ram memory
state:				;state variable
	.word 0

	.text			;in read only memory for execution
jt:				;jump table
	.word case0
	.word case1
	.word case2
	.word case3
	.word case4

	
	.global toggle

toggle:
/*	cmp.b &state, #4	;if(state > 4)
	JHS case1		*/
	
	mov.b &state, r12	;moves state into r12
	add.b r12, r12		;r12 =  2 * state
	mov jt(r12), r0		;jmp jt[s], r0 is the program counter
	
case0:
	mov.b #1, &state		;set state to 1 to go to case1
	jmp end

case1:
	mov.b #0, &green_on	;set green led to be off
	mov.b #0, &red_on	;set red led to be off
	mov.b #2, &state		;set state to 2 so that it moves to case2
	jmp end			;return

case2:
	mov.b #1, &green_on
	mov.b #0, &red_on
	mov.b #3, &state
	jmp end

case3:
	mov.b #0, &green_on
	mov.b #1, &red_on
	mov.b #4, &state
	jmp end

case4:	
	mov.b #1, &green_on
	mov.b #1, &red_on
	mov.b #1, &state
	jmp end



end:	pop r0			;return


	/*
case1:

	mov.b #0, &red_on
	mov.b #1, &green_on
	jmp case1
	
case0:
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
