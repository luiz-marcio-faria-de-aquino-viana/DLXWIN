		ADDI	R30,R0,1000		;;	R30 <- @STACK
		ADD	R22,R0,R30
		XOR	R8,R8,R8
		J	24			;;	goto @1@20
		LF	F24,184[R8]		;; @1@10:
		JAL	30			;;	goto @SIN
		ADD	R0,R0,R0		;;		'NOP'
		SF	1B4[R8],F28
		JAL	58			;;	goto @COS
		ADD	R0,R0,R0		;;		'NOP'
		SF	1E4[R8],F28
		ADDI	R8,R8,4
		SLTI	R23,R8,1C		;; @1@20:
		BEQZ	R23,FFDC		;; se R8 < NITENS goto @1@10
		HALT
		:
		:
		SUBI	R30,R30,8		;; @SIN:
		SW	0[R30],R31
		SW	4[R30],R22
		SUBI	R30,R30,4
		SF	0[R30],F8
		LF	F8,16C[R0]		;;		n = 1	(C1)
		J	48			;;	goto @2@10

		:
		:
		:

		SUBI	R30,R30,8		;; @COS:
		SW	0[R30],R31
		SW	4[R30],R22
		SUBI	R30,R30,4
		SF	0[R30],F8
		LF	F8,168[R0]		;;		n = 0	(C0)
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
		LF	F13,16C[R0]		;;			(C1)
		LF	F14,168[R0]		;;			(C0)
		LF	F16,170[R0]		;;			(C)
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

		DF	0			;; @C0:
		DF	1			;; @C1:
		DF	0.0001			;; @C:	precision

		:
		:

		DF	0			;; @VANG:	( 0d)
		DF	0.261799388		;;		(15d)
		DF	0.523598776		;;		(30d)
		DF	0.785398163		;;		(45d)
		DF	1.047197551		;;		(60d)
		DF	1.308996939		;;		(75d)
		DF	1.570796327		;;		(90d)

		:
		:
		:

		DF	0			;; @VSIN:
		DF	0
		DF	0
		DF	0
		DF	0
		DF	0
		DF	0

		:
		:
		:

		DF	0			;; @VCOS:
		DF	0
		DF	0
		DF	0
		DF	0
		DF	0
		DF	0

		:
		:
		:
