/*
 * LED.s
 *
 *  Created on: Sep 11, 2024
 *      Author: ijk95
 */

	.text
	.thumb
	.align 2
	.global ToggleGreenLED
	.global ToggleGreenLEDUsingBSRR
	.type ToggleGreenLEDUsingBSRR, %function
	.type ToggleGreenLED, %function

ToggleGreenLED:
	MOVS	r1, #32 //r1에 0x0020
	MOVS	r2,#160
	LSL     r2,r2,#23
	LDRH	r3,[r2,#20]
	EOR		r3, r1
	STRH	r3,[r2,#20]
	BX   	LR


ToggleGreenLEDUsingBSRR:
	MOVS	r1,#32 //bit mask
	LDR 	r2, =0x50000000 //Loading value from Base Address

    LDRH    r3,[r2,#20] //Loading Value from the ODR address

    TST     r3, r1// AND operation
    BEQ     bit_is_zero // bit5==0 -> move to bit_is_zero
    LDR 	r4, =0x200000 // bit 21->1
    B bit_done
bit_is_zero:
    MOVS    r4,#(1<<5)
bit_done:
    STR     r4,[r2,#24] //store r4 value in BSRR register
    BX   	LR // end function
