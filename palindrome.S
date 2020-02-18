;;; Alex Russo
;;; 114602275
;;; arusso98

;;; Implementation that determines if a word is a palindrome

;;; Palindrome
	.global is_palindrome
is_palindrome:
	push r30		; save value (low)
	push r31		; save value (high)
	movw r26, r24		; copyng X over to the register
	movw r30, r24		; copying Z over to the register

	call strlen		; calling string length function
	sbiw r30, 2		; minus 2 from r20
	cpi r20, 1		; comparing r20 to 1
	ldi r24, 1		; load 1 into r24
	clr r25			; clear r25
1:
	tst r20			; if X equals NULL 
	breq 3f			; break loop
	ld r20, X		; load X into dummy
	ld r22, Z		; load Z into dummy
	cp r20, r22		; if equal 
	breq 2f			; redirect to increment function
	jmp 4f			; else return fail
2:	
	adiw r26, 1   		; increment X
	sbiw r30, 1		; increment Z
	jmp 1b			; return to loop

3:	ldi r24, 1		; return SUCCESS
	pop r30			; restore value (low)
	pop r31			; restore value (high)
	ret			; return 

4:
	ldi r24, 0		; return FAILURE
	pop r30			; restore value (low)
	pop r31			; restore value (high)
	ret			; return 
	
