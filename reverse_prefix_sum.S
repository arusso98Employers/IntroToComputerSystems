;;; Alex Russo
;;; 114602275
;;; arusso98

;;; Implementation that returns the reverse prefix sum
.data 
pctd_1:  .asciz "%d"		;

pctd_2:	 .asciz " %d"  		;

	.text
	
	.global reverse_prefix_sum
reverse_prefix_sum:
	movw r26, r24		; move first number in the array over
	clr r23			; clearing r23
	clr r24			; clear r24
	clr r25			; clear r25
	ld r20, X+		; loading into dummy variable

	cpi r20, -1		; checks if its the last value
	breq 1f			; jump to return
	push r26		; saving value (low)
	push r27		; saving value (high)
	push r20		; saving value (low)
	push r21		; saving value (high)
	movw r24, r26		; copy X over to r24
	
	call reverse_prefix_sum	; calls the recursive function
	pop r21			; restoring value (high)
	pop r20			; restoring value (low)
	pop r27			; restoring value (high)
	pop r26			; restoring value (low)
	

	add r24, r20		; current + saved value
	adc r25, r21		; adding additional bits
	st -X, r24		; save back into array
	ret			; return r24
	
1:
	ret			; return r24

pint_1:
        ;; prints an integer value, r22/r23 have the format string
	
        ldi r22, lo8(pctd_1)      ; lower byte of the string address
        ldi r23, hi8(pctd_1)      ; higher byte of the string address
	push r27
	push r26
        push r25		  ;
        push r24		  ;
        push r23		  ;
        push r22		  ;
        call printf		  ;
        pop r22			  ;
        pop r23			  ;
        pop r24			  ;
        pop r25			  ;
	pop r26
	pop r27

        ret			

pint_2:
        ;; prints an integer value, r22/r23 have the format string
	
        ldi r22, lo8(pctd_2)      ; lower byte of the string address
        ldi r23, hi8(pctd_2)      ; higher byte of the string address
	push r27
	push r26
        push r25		  ;
        push r24		  ;
        push r23		  ;
        push r22		  ;
        call printf		  ;
        pop r22			  ;
        pop r23			  ;
        pop r24			  ;
        pop r25			  ;
	pop r26
	pop r27

        ret

;;; Implementation that prints output
	
	.global print_array
print_array:
	push r26		; saving X (low)
	push r27		; saving X (high)
	movw r26, r24		; storing the input pair
	ld r24, X+		; incrementing X then loading		
	cpi r24, -1		; end case, if its at the end of the line new
	breq 1f			; line is inserted and characters are placed

	clr r25
	call pint_1		; calling first print function
	ld r24, X+ 		; incrementing X pointer		
	jmp 2f			; jump to loop
	
	
1:
	clr r25			; clearing register
	ldi r24, 10 		; 10 is the new line character
	call putchar		; calling charavter placment function
	pop r26			; restore value (high)
	pop r25			; restore value (low)
	
	ret			; restor r24

2:
	cpi r24, -1 		; start of loop checks if empty
	breq 1b			; if true, breaks to end case
	clr r25			; clear r25
	call pint_2		; calling the alternate print function
	ld r24, X+		; loading the now incremented X
	jmp 2b			; restart loop
	
	
