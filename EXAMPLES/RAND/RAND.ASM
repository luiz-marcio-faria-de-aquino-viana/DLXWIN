		ADDI	R30,R0,1000		;; @INICIO: R30 <- @STACK
		ADD	R22,R0,R30
		LF	F8,54[R0]		;; F8 <- @SEED
		ADDI	R8,R0,3E5		;; R8 <- RNDGEN
		SUBI	R30,R30,4
		SW	0[R30],R8
		LF	F9,0[R30]
		ADDI	R30,R30,4
		CVTI2F	F9,F9
		MULTF	F8,F8,F9
		SF	8C[R0],F8
		LW	R8,8C[R0]
		ANDI	R8,R8,0FF
		SW	54[R0],R8		;; @SEED <- R8
		ADD	R28,R0,R8
		HALT

		:
		:
		:

		DF	0.528416312342		;; @SEED:
		DW	0			;; @ARRAY:

		:
		:
		:
