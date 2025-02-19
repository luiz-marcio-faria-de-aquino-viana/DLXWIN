		ADDI	R30,R0,1000		;; @INICIO: R30 <- @STACK
		ADD	R22,R0,R30
		XOR	R8,R8,R8
		J	10			;; goto @1@20
		JAL	68			;; @1@10:
		ADDI	R8,R8,1
		SB	FF[R8],R28		;;	@ARRAY-1[R8] <- R28
		SLTI	R23,R8,A		;; @1@20:
		BEQZ	R23,FFF0		;; se R8 < 10 goto @1@10
		ADDI	R10,R0,9
		XOR	R8,R8,R8		;; @1@30:
		XOR	R9,R9,R9
		J	28			;; goto @1@60
		LBU	R11,100[R8]		;; @1@40:
		LBU	R12,101[R8]
		SLE	R23,R11,R12
		BEQZ	R23,14			;; se R11 <= R12 goto @1@50
		ADD	R0,R0,R0		;;		'NOP'
		SB	100[R8],R12
		SB	101[R8],R11
		ADDI	R9,R0,1
		ADDI	R8,R8,1			;; @1@50:
		SLT	R23,R8,R10		;; @1@60:
		BEQZ	R23,FFD8		;; se R8 < R10 goto @1@40
		SUBI	R10,R10,1
		BNEZ	R9,FFC4			;; se R9 != 0 goto @1@30
		HALT

		:

		SUBI	R30,R30,8		;; @RAND:
		SW	0[R30],R31
		SW	4[R30],R22
		SUBI	R30,R30,14
		SW	0[R30],R8
		SD	4[R30],F8
		SD	C[R30],F9
		SUBI	R30,R30,4
		ADD	R22,R0,R30
		LF	F8,FC[R0]		;; F8 <- @SEED
		ADDI	R8,R0,3E5		;; R8 <- 997
		SW	0[R22],R8
		LF	F9,0[R22]
		CVTI2F	F9,F9
		MULTF	F8,F8,F9
		SF	0[R22],F8
		LW	R8,0[R22]
		ANDI	R8,R8,0FF
		SW	FC[R0],R8		;; @SEED <- R8
		ADD	R28,R0,R8
		ADDI	R30,R30,4
		LD	F9,C[R30]
		LD	F8,4[R30]
		LW	R8,0[R30]
		ADDI	R30,R30,14
		LW	R22,4[R30]
		LW	R31,0[R30]
		ADDI	R30,R30,8
		JR	R31

		:
		:

		DF	0.528416312342		;; @SEED:
		DW	0			;; @ARRAY:

		:
		:
