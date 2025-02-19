	ADDI	R1,R0,0			;; @INICIO:
	ADDI	R2,R0,20
	LW	R3,0[R1]		;; @1@10:
	SW	40[R1],R3
	SUBI    R2,R2,1
	ADDI	R1,R1,4
	BNEZ	R2,FFF0			;; se R2 != 0 goto @1@10
	HALT
	:
	:
	:
