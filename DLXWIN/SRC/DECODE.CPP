
/*
/* Decode.cpp
/* por Luiz Marcio F A Viana, 12/9/96
*/

#include"h\decode.h"

/********************************************
/* codigo do grupo de depuracao de erros (=110)
/********************************************/

/* definicao das tabelas de formato das instrucoes
*/
const ITABLE ITYPE_ARRAY[] = {
	{ _BEQZ,  "BEQZ     R%d, %X",      FORM_A, UNIT_BPU },
	{ _BNEZ,  "BNEZ     R%d, %X",      FORM_A, UNIT_BPU },
	{ _JR,    "JR       R%d",          FORM_B, UNIT_BPU },
	{ _JAL,   "JAL      R%d",          FORM_B, UNIT_BPU },
	{ _LB,    "LB       R%d, %X[R%d]", FORM_C, UNIT_LSU },
	{ _LBU,   "LBU      R%d, %X[R%d]", FORM_C, UNIT_LSU },
	{ _SB,    "SB       %X[R%d], R%d", FORM_D, UNIT_LSU },
	{ _LH,    "LH       R%d, %X[R%d]", FORM_C, UNIT_LSU },
	{ _LHU,   "LHU      R%d, %X[R%d]", FORM_C, UNIT_LSU },
	{ _SH,    "SH       %X[R%d], R%d", FORM_D, UNIT_LSU },
	{ _LW,    "LW       R%d, %X[R%d]", FORM_C, UNIT_LSU },
	{ _SW,    "SW       %X[R%d], R%d", FORM_D, UNIT_LSU },
	{ _LF,    "LF       F%d, %X[R%d]", FORM_C, UNIT_LSU },
	{ _LD,    "LD       F%d, %X[R%d]", FORM_C, UNIT_LSU },
	{ _SF,    "SF       %X[R%d], F%d", FORM_D, UNIT_LSU },
	{ _SD,    "SD       %X[R%d], F%d", FORM_D, UNIT_LSU },
	{ _ADDI,  "ADDI     R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _SUBI,  "SUBI     R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _MULTI, "MULTI    R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _DIVI,  "DIVI     R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _ANDI,  "ANDI     R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _ORI,   "ORI      R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _XORI,  "XORI     R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _LHI,   "LHI      R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _SLLI,  "SLLI     R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _SRLI,  "SRLI     R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _SRAI,  "SRAI     R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _SLTI,  "SLTI     R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _SGTI,  "SGTI     R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _SLEI,  "SLEI     R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _SGEI,  "SGEI     R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _SEQI,  "SEQI     R%d, R%d, %X", FORM_E, UNIT_ALU },
	{ _SNEI,  "SNEI     R%d, R%d, %X", FORM_E, UNIT_ALU },
};

const ITABLE JTYPE_ARRAY[] = {
	{ _BFPT,  "BFPT     %X",           FORM_F, UNIT_BPU },
	{ _BFPF,  "BFPF     %X",           FORM_F, UNIT_BPU },
	{ _J,     "J        %X",           FORM_F, UNIT_BPU },
	{ _JAL,   "JAL      %X",           FORM_F, UNIT_BPU },
	{ _TRAP,  "TRAP     %X",           FORM_F, UNIT_BPU },
	{ _RFE,   "RFE",                   FORM_G, UNIT_BPU },
	{ _HALT,  "HALT",                  FORM_G, UNIT_BPU },
};

const ITABLE RTYPE_ARRAY[] = {
	{ _MOVI2S,  "MOVI2S   R%d",           FORM_B, UNIT_LSU },
	{ _MOVS2I,  "MOVS2I   R%d",           FORM_B, UNIT_LSU },
	{ _MOVF,    "MOVF     F%d, F%d",      FORM_H, UNIT_LSU },
	{ _MOVD,    "MOVD     F%d, F%d",      FORM_H, UNIT_LSU },
	{ _MOVFP2I, "MOVFP2I  R%d, F%d",      FORM_H, UNIT_LSU },
	{ _MOVI2FP, "MOVI2FP  F%d, R%d",      FORM_H, UNIT_LSU },
	{ _ADD,     "ADD      R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _SUB,     "SUB      R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _MULT,    "MULT     R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _DIV,     "DIV      R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _AND,     "AND      R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _OR,      "OR       R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _XOR,     "XOR      R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _SLL,     "SLL      R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _SRL,     "SRL      R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _SRA,     "SRA      R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _SLT,     "SLT      R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _SGT,     "SGT      R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _SLE,     "SLE      R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _SGE,     "SGE      R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _SEQ,     "SEQ      R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _SNE,     "SNE      R%d, R%d, R%d", FORM_I, UNIT_ALU },
	{ _ADDD,    "ADDD     F%d, F%d, F%d", FORM_I, UNIT_FPU },
	{ _ADDF,    "ADDF     F%d, F%d, F%d", FORM_I, UNIT_FPU },
	{ _SUBD,    "SUBD     F%d, F%d, F%d", FORM_I, UNIT_FPU },
	{ _SUBF,    "SUBF     F%d, F%d, F%d", FORM_I, UNIT_FPU },
	{ _MULTD,   "MULTD    F%d, F%d, F%d", FORM_I, UNIT_FPU },
	{ _MULTF,   "MULTF    F%d, F%d, F%d", FORM_I, UNIT_FPU },
	{ _DIVD,    "DIVD     F%d, F%d, F%d", FORM_I, UNIT_FPU },
	{ _DIVF,    "DIVF     F%d, F%d, F%d", FORM_I, UNIT_FPU },
	{ _CVTF2D,  "CVTF2D   F%d, F%d",      FORM_H, UNIT_FPU },
	{ _CVTF2I,  "CVTF2I   F%d, F%d",      FORM_H, UNIT_FPU },
	{ _CVTD2F,  "CVTD2F   F%d, F%d",      FORM_H, UNIT_FPU },
	{ _CVTD2I,  "CVTD2I   F%d, F%d",      FORM_H, UNIT_FPU },
	{ _CVTI2F,  "CVTI2F   F%d, F%d",      FORM_H, UNIT_FPU },
	{ _CVTI2D,  "CVTI2D   F%d, F%d",      FORM_H, UNIT_FPU },
	{ _SLTD,    "SLTD     F%d, F%d",      FORM_J, UNIT_FPU },
	{ _SGTD,    "SGTD     F%d, F%d",      FORM_J, UNIT_FPU },
	{ _SLED,    "SLED     F%d, F%d",      FORM_J, UNIT_FPU },
	{ _SGED,    "SGED     F%d, F%d",      FORM_J, UNIT_FPU },
	{ _SEQD,    "SEQD     F%d, F%d",      FORM_J, UNIT_FPU },
	{ _SNED,    "SNED     F%d, F%d",      FORM_J, UNIT_FPU },
	{ _SLTF,    "SLTF     F%d, F%d",      FORM_J, UNIT_FPU },
	{ _SGTF,    "SGTF     F%d, F%d",      FORM_J, UNIT_FPU },
	{ _SLEF,    "SLEF     F%d, F%d",      FORM_J, UNIT_FPU },
	{ _SGEF,    "SGEF     F%d, F%d",      FORM_J, UNIT_FPU },
	{ _SEQF,    "SEQF     F%d, F%d",      FORM_J, UNIT_FPU },
	{ _SNEF,    "SNEF     F%d, F%d",      FORM_J, UNIT_FPU },
};

/* implementacao da classe decodificacao de instrucoes
*/
Decode::Decode(WORD_T _ir)
{
  IR = _ir;
  SetupItem();
}

void
Decode::SetItem(WORD_T _ir)
{
  IR = _ir;
  SetupItem();
}

int
Decode::IsBranch()
{
  if(UF == UNIT_BPU)
	 return 1;
  return 0;
}

void
Decode::SetupItem()
{
  Op = (int) ((IR >> 26) & 0x3FL);
  if((Op & 0x3F) == 0x3F) {					// R-Type
	 Typ = R_TYPE;
	 // campos de operandos
	 Rs1 = (int) ((IR >> 21) & 0x1FL);
	 Rs2 = (int) ((IR >> 16) & 0x1FL);
	 Rd  = (int) ((IR >> 11) & 0x1FL);
	 Func = (int) (IR & 0x7FFL);
	 Offset = 0L;
	 Imm = 0;
	 // unidade de execucao
	 switch((Func & 0x600) >> 9) {
		case 0x00 :
		  UF = UNIT_LSU;
		  break;
		case 0x01 :
		  UF = UNIT_ALU;
		  break;
		case 0x02 :
		  UF = UNIT_FPU;
	 };
	 // comando requerido
	 Cmd = Func & 0x7F;
  }
  else if((Op & 0x38) == 0x38) {				// J-Type
	 Typ = J_TYPE;
	 // campos de operandos
	 Rs1 = Rs2 = 0;
	 Rd = 0;
	 Func = 0;
	 Offset = IR & 0x3FFFFFFL;
	 if((IR & 0x2000000L) > 0)
		Offset = Offset | 0xFC000000L;
	 Imm = 0;
	 // unidade de execucao
	 UF = UNIT_BPU;
	 // comando requerido
	 Cmd = Op & 0x3F;
  }
  else {												// I-Type
	 Typ = I_TYPE;
	 // campo de operandos
	 Rs1 = (int) ((IR >> 21) & 0x1FL);
	 Rs2 = 0;
	 Rd  = (int) ((IR >> 16) & 0x1FL);
	 Func = 0;
	 Offset = 0L;
	 Imm = (int) (IR & 0xFFFFL);
	 // unidade de execucao
	 if((Op & 0x3C) == 0)
		UF = UNIT_BPU;
	 else if((Op & 0x30) == 0)
		UF = UNIT_LSU;
	 else
		UF = UNIT_ALU;
	 // comando requerido
	 Cmd = Op & 0x3F;
  }
}

char*
Decode::StrFormat(char* s, char* instrForm, int instrFormTyp)
{
  switch(instrFormTyp) {
	 case FORM_A :
		sprintf(s, instrForm, Rs1, Imm);
		break;
	 case FORM_B :
		sprintf(s, instrForm, Rs1);
		break;
	 case FORM_C :
		sprintf(s, instrForm, Rd, Imm, Rs1);
		break;
	 case FORM_D :
		sprintf(s, instrForm, Imm, Rs1, Rd);
		break;
	 case FORM_E :
		sprintf(s, instrForm, Rd, Rs1, Imm);
		break;
	 case FORM_F :
		sprintf(s, instrForm, Offset);
		break;
	 case FORM_G :
		sprintf(s, instrForm);
		break;
	 case FORM_H :
		sprintf(s, instrForm, Rd, Rs1);
		break;
	 case FORM_I :
		sprintf(s, instrForm, Rd, Rs1, Rs2);
		break;
	 case FORM_J :
		sprintf(s, instrForm, Rs1, Rd);
  };
  return s;
}

char*
Decode::StrUndecode(char* s)
{
  const ITABLE* ptr;
  int i;

  switch(Typ) {
	 case R_TYPE :
		ptr = RTYPE_ARRAY;
		for(i = 0; i < MAX_RTYPE; i++) {
		  if((Cmd == ptr->InstrCode) && (UF == ptr->ExecUnit)) {
			 StrFormat(s, ptr->InstrForm, ptr->InstrFormType);
			 return s;
		  }
		  ptr++;
		}
		break;
	 case I_TYPE :
		ptr = ITYPE_ARRAY;
		for(i = 0; i < MAX_ITYPE; i++) {
		  if((Cmd == ptr->InstrCode) && (UF == ptr->ExecUnit)) {
			 StrFormat(s, ptr->InstrForm, ptr->InstrFormType);
			 return s;
		  }
		  ptr++;
		}
		break;
	 case J_TYPE :
		ptr = JTYPE_ARRAY;
		for(i = 0; i < MAX_JTYPE; i++) {
		  if((Cmd == ptr->InstrCode) && (UF == ptr->ExecUnit)) {
			 StrFormat(s, ptr->InstrForm, ptr->InstrFormType);
			 return s;
		  }
		  ptr++;
		}
		break;
  };
  sprintf(s, "??");
  return s;
}

