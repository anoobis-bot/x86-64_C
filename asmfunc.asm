section .data

section .text
bits 64
default rel

global asmSAXPY

; Z = RCX
; X = RDX
; Y = R8
; A = XMM3
; size = 5th param (SET TO EAX)

asmSAXPY:
	PUSH RBP
	MOV RBP, RSP
	ADD RBP, 16
	MOV RAX, [RBP + 32] 

	DEC RAX 

	LOOP:
		MOVSS XMM0, [RDX + RAX*4]
		MOVSS XMM1, [R8 + RAX*4]

		MULSS XMM0, XMM3
		ADDSS XMM0, XMM1

		MOVSS dword[RCX + RAX*4], XMM0

		DEC RAX
		CMP RAX, -1
		JNE LOOP

	POP RBP
	RET