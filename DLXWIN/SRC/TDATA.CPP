
/*
/* TDATA.cpp
/* por Luiz Marcio F A Viana, 12/8/96
*/

#include"h\tdata.h"

/********************************************
/* codigo do grupo de depuracao de erros (=109)
/********************************************/

/* implementacao da classe de dados
*/
TData::TData()
{
  ClearBits();
  SetupItem();
}

void
TData::SetItem(WORD_T pc, WORD_T ir)
{
  PC = pc; IR = ir;
  BB = Decode(IR).IsBranch();
}

void
TData::SetItem(TData& d)
{
  RD = d.RD;

  BB = d.BB;
  BT = d.BT;
  BR = d.BR;

  BL = d.BL;

  DP = d.DP;

  ID = d.ID;

  HLT = d.HLT;

  PC = d.PC;
  IR = d.IR;

  PC0 = d.PC0;
  PC1 = d.PC1;

  MAR = d.MAR;
  MBR = d.MBR;

  VU  = d.VU;
  UF  = d.UF;
  Cmd = d.Cmd;

  R1   = d.R1;
  R2   = d.R2;
  Rd   = d.Rd;
  F1   = d.F1;
  F2   = d.F2;
  Fd   = d.Fd;
  Biar = d.Biar;
  Bfp  = d.Bfp;

  Qr1  = d.Qr1;
  Qr2  = d.Qr2;
  Qrd  = d.Qrd;
  Qf1  = d.Qf1;
  Qf2  = d.Qf2;
  Qfd  = d.Qfd;
  Qiar = d.Qiar;
  Qfp  = d.Qfp;

  Vr1  = d.Vr1;
  Vr2  = d.Vr2;
  Vrd  = d.Vrd;
  Vf1  = d.Vf1;
  Vf2  = d.Vf2;
  Vfd  = d.Vfd;
  Viar = d.Viar;
  Vfp  = d.Vfp;

  Imm    = d.Imm;
  Offset = d.Offset;
}

TData&
TData::operator=(TData& d)
{
  SetItem(d);
  return *this;
}

void
TData::Reset()
{
  ClearBits();
  SetupItem();
}

void
TData::DecodeData()
{
  Decode d(IR);

  SetupItem();

  UF     = d.UF;
  Cmd    = d.Cmd;
  Imm    = d.Imm;
  Offset = d.Offset;

  if(UF == UNIT_ALU) {
	 if((_ADDI <= Cmd) && (Cmd <= _SNEI)) {
		R1 = d.Rs1;
		Rd = d.Rd;
	 } else if(Cmd == _LHI) {
		Rd = d.Rd;
	 } else if((_ADD <= Cmd) && (Cmd <= _SNE)) {
		R1 = d.Rs1;
		R2 = d.Rs2;
		Rd = d.Rd;
	 }
  }
  else if(UF == UNIT_BPU) {
	 if((_BEQZ <= Cmd) && (Cmd <= _JR)) {
		R1 = d.Rs1;
	 } else if(Cmd == _JALR) {
		R1 = d.Rs1;
		Rd = 31;
	 } else if((_BFPT <= Cmd) && (Cmd <= _BFPF)) {
		Bfp = R_SRC;
	 } else if(Cmd == _JAL) {
		Rd = 31;
	 } else if(Cmd == _TRAP) {
		Biar = R_DST;
	 } else if(Cmd == _HALT) {
		HLT = 1;
	 }
  }
  else if(UF == UNIT_LSU) {
	 if( ((_LB <= Cmd) && (Cmd <= _LBU)) ||
		  ((_LH <= Cmd) && (Cmd <= _LHU)) || (Cmd == _LW) ) {
		R1 = d.Rs1;
		Rd = d.Rd;
	 } else if((Cmd == _SB) || (Cmd == _SH) || (Cmd == _SW)) {
		R1 = d.Rs1;
		R2 = d.Rd;
	 } else if((Cmd == _LF) || (Cmd == _LD)) {
		R1 = d.Rs1;
		Fd = d.Rd;
	 } else if((Cmd == _SF) || (Cmd == _SD)) {
		R1 = d.Rs1;
		F1 = d.Rd;
	 } else if(Cmd == _MOVI2S) {
		R1 = d.Rs1;
		Biar = R_DST;
	 } else if(Cmd == _MOVS2I) {
		Rd = d.Rs1;
		Biar = R_SRC;
	 } else if((Cmd == _MOVF) || (Cmd == _MOVD)) {
		F1 = d.Rs1;
		Fd = d.Rd;
	 } else if(Cmd == _MOVFP2I) {
		F1 = d.Rs1;
		Rd = d.Rd;
	 } else if(Cmd == _MOVI2FP) {
		R1 = d.Rs1;
		Fd = d.Rd;
	 }
  }
  else if(UF == UNIT_FPU) {
	 if((_ADDD <= Cmd) && (Cmd <= _DIVF)) {
		F1 = d.Rs1;
		F2 = d.Rs2;
		Fd = d.Rd;
	 } else if((_CVTF2D <= Cmd) && (Cmd <= _CVTI2D)) {
		F1 = d.Rs1;
		Fd = d.Rd;
	 } else if((_SLTD <= Cmd) && (Cmd <= _SNEF)) {
		F1 = d.Rs1;
		F2 = d.Rd;
		Bfp = R_DST;
	 }
  }
}

void
TData::GetInstStr(char* s)
{
  Decode(IR).StrUndecode(s);
}

void
TData::SetupItem()
{
  R1 = R2 = Rd = R_NONE;		// inicializa selecao dos regs com vazio
  F1 = F2 = Fd = R_NONE;
  Biar = Bfp = R_NONE;

  Qr1 = Qr2 = Qrd = VU_NDEF;	// inicializa unidade virtual fonte com ndef
  Qf1 = Qf2 = Qfd = VU_NDEF;
  Qiar = Qfp = VU_NDEF;
}

void
TData::ClearBits()
{
  RD = 0;

  BB = 0;
  BT = 0;
  BR = 0;

  BL = 0;

  DP = 0;

  ID = VU_NDEF;

  HLT = 0;
}

int
TData::GetDependenceType(TData d)
{
  int rst = 0;

  if(Rd != R_NONE) {
	 if( (Rd == d.R1) || (Rd == d.R2) )
		rst |= D_TRUE;
	 if( Rd == d.Rd )
		rst |= D_OUT;
  }

  if(d.Rd != R_NONE) {
	 if( (R1 == d.Rd) || (R2 == d.Rd) )
		rst |= D_FALSE;
  }

  if(Fd != R_NONE) {
	 if( (Fd == d.F1) || (Fd == d.F2) )
		rst |= D_TRUE;
	 if( Fd == d.Fd )
		rst |= D_OUT;
  }

  if(d.Fd != R_NONE) {
	 if( (F1 == d.Fd) || (F2 == d.Fd) )
		rst |= D_FALSE;
  }

  if( (Biar == R_DST) && (d.Biar == R_SRC) )
	 rst |= D_TRUE;
  if( (Biar == R_SRC) && (d.Biar == R_DST) )
	 rst |= D_FALSE;
  if( (Biar == R_DST) && (d.Biar == R_DST) )
	 rst |= D_OUT;

  if( (Bfp == R_DST) && (d.Bfp == R_SRC) )
	 rst |= D_TRUE;
  if( (Bfp == R_SRC) && (d.Bfp == R_DST) )
	 rst |= D_FALSE;
  if( (Bfp == R_DST) && (d.Bfp == R_DST) )
	 rst |= D_OUT;

  return rst;
}

