	ADDI    R1,R0,5			;; @INICIO:
	ADDI    R2,R0,10		;; @1@10:
	SUBI    R2,R2,1			;; @1@20:
	BNEZ    R2,FFFC			;; se R2 != 0 goto @1@20
	SUBI    R1,R1,1
	BNEZ    R1,FFF0			;; se R1 != 0 goto @1@10
	HALT
	:
	:
	:
