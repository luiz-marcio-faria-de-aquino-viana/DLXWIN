		ADDI	R30,R0,1000		;;	R30 <- @STACK
		ADD	R22,R0,R30
		LF	F1,374[R0]		;;	F1 <- @MAXSZ
		LF	F2,378[R0]		;;	F2 <- @MAXAN
		XOR	R8,R8,R8
		J	20			;;	goto @1@20
		JAL	74			;; @1@10: goto @RAND
		MULTF	F8,F1,F28
		JAL	6C			;;	  goto @RAND
		MULTF	F9,F2,F28
		ADDI	R8,R8,8
		SF	25C[R8],F8		;;	@VECT.R[R8] <- F8
		SF	260[R8],F9		;;	@VECT.A[R8] <- F8
		SLTI	R23,R8,80		;; @1@20:
		BEQZ	R23,FFE0		;; se R8 < NITENS goto @1@10
		XOR	R8,R8,R8
		J	2C			;;	goto @1@40
		LF	F8,264[R8]		;; @1@30:	F8 <- @VECT.R[R8]
		LF	F9,268[R8]		;;		F9 <- @VECT.A[R8]
		MOVF	F24,F9
		JAL	DC			;;	goto @COS
		MULTF	F10,F8,F28		;;	X <- R * COS(A)
		JAL	A4			;;	goto @SIN
		MULTF	F11,F8,F28		;;	Y <- R * SIN(A)
		ADDI	R8,R8,8
		SF	2E0[R8],F10		;;		@VECT.X[R8] <- F10
		SF	2E4[R8],F11		;;		@VECT.Y[R8] <- F11
		SLTI	R23,R8,80		;; @1@40
		BEQZ	R23,FFD4		;; se R8 < NITENS goto @1@30
		HALT

		:
		:
		:

		SUBI	R30,R30,14		;;@RAND
		SW	0[R30],R31
		SW	4[R30],R22
		SF	8[R30],F8
		SF	C[R30],F9
		SF	10[R30],F10
		ADD	R22,R0,R30
		LF	F8,228[R0]		;;	F8 <- @SEED
		LF	F9,22C[R0]		;;	F9 <- @C997
		MULTF	F8,F8,F9
		MOVF	F10,F8
		CVTF2I	F10,F10
		CVTI2F	F10,F10
		SUBF	F28,F8,F10
		SF	228[R0],F28		;;	@SEED <- F28
		LW	R31,0[R30]
		LW	R22,4[R30]
		LF	F8,8[R30]
		LF	F9,C[R30]
		LF	F10,10[R30]
		ADDI	R30,R30,14
		JR	R31

		:
		:
		:
		:

		SUBI	R30,R30,8		;; @SIN:
		SW	0[R30],R31
		SW	4[R30],R22
		SUBI	R30,R30,4
		SF	0[R30],F8
		LF	F8,248[R0]		;;		n = 1	(C1)
		J	48			;;	goto @2@10

		:
		:
		:

		SUBI	R30,R30,8		;; @COS:
		SW	0[R30],R31
		SW	4[R30],R22
		SUBI	R30,R30,4
		SF	0[R30],F8
		LF	F8,244[R0]		;;		n = 0	(C0)
		J	18			;;	goto @2@10

		:
		:
		:

		SUBI	R30,R30,20		;; @2@10:
		SF	0[R30],F9
		SF	4[R30],F10
		SF	8[R30],F11
		SF	C[R30],F12
		SF	10[R30],F13
		SF	14[R30],F14
		SF	18[R30],F15
		SF	1C[R30],F16
		ADD	R22,R0,R30
		LF	F13,248[R0]		;;			(C1)
		LF	F14,244[R0]		;;			(C0)
		LF	F16,24C[R0]		;;			(C)
		MOVF	F9,F14			;;		r = 0
		MOVF	F10,F13			;;		sign = 1
		MOVF	F11,F8			;; @2@20:	a = n
		MOVF	F12,F13			;;		b = 1
		J	10			;;	goto @2@40
		MULTF	F12,F12,F24		;; @2@30:	b *= ang
		DIVF	F12,F12,F11		;;		b /= a
		SUBF	F11,F11,F13		;;		a -= 1
		SGTF	F11,F14			;; @2@40:
		BFPT	FFFFFFF0		;; se a > 0 goto @2@30
		MULTF	F15,F10,F12		;;		tmp = sign * b
		ADDF	F9,F9,F15		;;		r += b
		SUBF	F10,F14,F10		;;		sign = -sign
		ADDF	F8,F8,F13		;;
		ADDF	F8,F8,F13		;;		n += 2
		SGTF	F12,F16
		BFPT	FFFFFFC8		;; se b > 0 goto @2@20
		MOVF	F28,F9
		LF	F9,0[R30]
		LF	F10,4[R30]
		LF	F11,8[R30]
		LF	F12,C[R30]
		LF	F13,10[R30]
		LF	F14,14[R30]
		LF	F15,18[R30]
		LF	F16,20[R30]
		ADDI	R30,R30,20
		LF	F8,0[R30]
		ADDI	R30,R30,4
		LW	R31,0[R30]
		LW	R22,4[R30]
		ADDI	R30,R30,8
		JR	R31

		:
		:
		:

		DF	0.528416312342		;; @SEED:
		DF	997.0			;; @C977:

		:
		:
		:

		DF	0			;; @C0:
		DF	1			;; @C1:
		DF	0.0001			;; @C:	precision

		:
		:
		:

		DF	0			;; @VECT.R:
		DF	0			;; @VECT.A:
		:
		:
		R
		A
		:
		:
		R
		A
		:
		:
		R
		A
		:
		:
		R
		A
		:
		:
		R
		A
		:
		:
		R
		A
		:
		:
		R
		A
		:
		:

		DF	0			;; @VECT.X:
		DF	0			;; @VECT.Y:
		:
		:
		X
		Y
		:
		:
		X
		Y
		:
		:
		X
		Y
		:
		:
		X
		Y
		:
		:
		X
		Y
		:
		:
		X
		Y
		:
		:
		X
		Y

		:
		:
		:

		DF	100.0			;; @MAXSZ:
		DF	6.283185307		;; @MAXAN:

		:
		:
		:
