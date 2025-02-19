	ADDI    R8,R0,10		;; @INICIO:
	SUBI    R8,R8,1			;; @1@10:
	BNEZ    R8,FFFC			;; se R8 != 0 goto @1@10
	HALT
	:
	:
	:
