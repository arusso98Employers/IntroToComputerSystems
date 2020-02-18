
;;; Five
    .global Five
Five:   
    ;;; uint16_t Five(): return 5 as a uint16_t
    ldi r24, 5		;; load immediate
    clr r25		;; load immediate or clear
    ret 		;; return

;;; Max
    .global Max
Max:
    ;;; uint8_t max(uint8_t x, uint8_t y): return the greater of the arguments
    cp r24, r22		;; compare x to y
    brge 1f		;; if x >= y, branch 1f
    mov r24, r22	;; copy y into return value / first param slot.
1:
    ret 		;; return
    
;;; Strlen
    .global Strlen
Strlen:
    ;;; uint16_t Strlen(char *arg)
    mov r26, r24
    mov r27, r25	;; copy argument to X (r27:26) pointer
    clr 24
    clr 25		;; initialize return value to zero
2:  
    ld r23, X+		;; load X with post-increment
    cp r23, 0
    breq 1f		;; if loaded value was zero, branch 1f(label 1, forward)
    adiw r24, 1		;; increment return value
    jmp 2b		;; jump 2b (label 2, backward)
1:
    ret 		;; return

