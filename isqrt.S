;;; Alex Russo
;;; 114602275
;;; arusso98

;;; Implementation that computes the square root

	.global isqrt		; exposes isqrt as a label for the linker
isqrt:				; the label: the next instuction

	cpi r24, 2		; checking if its less than 2
	brlo 1f			; return n
	push r24		; saving value (low)
	push r25		; saving value (high)
	lsr r24			; shift r24 right (1)
	lsr r24			; shift r24 right (2)
	clr r25			; clear r25
	call isqrt		; calling the recursive function
	lsl r24			; shift r24 left
	
	movw r30, r24		; move n to r30
	inc r30			; increment r30
	mul r30, r30 		; large * large stored in r0
	movw r12, r0		; placing large * large in dummy
	clr r1			; clear r1

	pop r19			; restoring value (high)
	pop r18			; restoring value (low)
	cp r18, r12		; comparing large * large and n
	brlt 1f			; if n is less return small
	movw r24, r30		; set r24 to r30 (large)
	ret			; now return large
	
1:
	ret			; return n
	

	
	
	
