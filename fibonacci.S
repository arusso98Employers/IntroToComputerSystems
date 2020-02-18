;;; Alex Russo
;;; 114602275
;;; arusso98

;;; Implementation that computes the nth fibonacci number.

    .global fib                 ; exposes fib as a label for the linker
fib:                            ; the label: the next instruction 						; starts fib() function.

	;;; uint8_t max(uint8_t n): returns the fibonacci sequence
	tst r24			; if n is 0
	breq 1f			; break to 1 and return 0
	cpi r24, 1		; if n is 1
	breq 2f			; break to 2 and return 1
	
	push r30		; save values (low)
	push r31		; save values (high)
	sbiw r24, 1		; n - 1
	push r24		; save values (low)
	push r25		; save values (high)

	call fib		; calling recursive function
	movw r30, r24		; place in dummy register
	pop r25			; restoring value (high)
	pop r24			; restoring value (low)
	sbiw r24, 1		; decrement n again

	call fib		; calling function again
	add r24, r30		; adding values together to get F(n)
	adc r25, r31		; add additional bits
	pop r31			; restoring value (high)
	pop r30			; restoring value (low)
	ret			; return 

1:
	ldi r24, 0		; return FAILURE
	ret			; return
2:
	ldi r24, 1		; return SUCCESS
	ret			; return 
	
