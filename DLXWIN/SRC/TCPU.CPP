
/*
/* TCPU.cpp
/* por Luiz Marcio F A Viana, 11/3/96
*/

#include"h\tcpu.h"

/********************************************
/* codigo do grupo de depuracao de erros (=108)
/********************************************/

/* implementacao da classe unidade de controle
*/
void
TCpu::Escalar()
{
  TData item;

  if( Disq.IsEmpty() ) return;
  Disq.GetItem(item);

  //
  // verifica dependencia de recursos
  //
  if((item.R1  != R_NONE) && ((R.GetRegister(item.R1))->IsBusy())) return;
  if((item.R2  != R_NONE) && ((R.GetRegister(item.R2))->IsBusy())) return;
  if((item.Rd  != R_NONE) && ((R.GetRegister(item.Rd))->IsBusy())) return;

  if((item.F1  != R_NONE) && ((F.GetRegister(item.F1))->IsBusy())) return;
  if((item.F2  != R_NONE) && ((F.GetRegister(item.F2))->IsBusy())) return;
  if((item.Fd  != R_NONE) && ((F.GetRegister(item.Fd))->IsBusy())) return;

  if((item.Bfp  != R_NONE) && (FP.IsBusy())) return;
  if((item.Biar != R_NONE) && (IAR.IsBusy())) return;

  //
  // despacha a instrucao a unidade virtual correspondente
  //
  switch(item.UF) {
	 case UNIT_BPU :
		if( VBPU.IsFull() ) return;
		CheckIfIsReady(item);
		GetRegs(item);
		item.SetIdentifier(VBPU.AddItem(item));
		break;
	 case UNIT_FPU :
		if( VFPU.IsFull() ) return;
		CheckIfIsReady(item);
		GetRegs(item);
		item.SetIdentifier(VFPU.AddItem(item));
		break;
	 case UNIT_LSU :
		if( VLSU.IsFull() ) return;
		CheckIfIsReady(item);
		GetRegs(item);
		item.SetIdentifier(VLSU.AddItem(item));
		break;
	 case UNIT_ALU :
		if( VALU.IsFull() ) return;
		CheckIfIsReady(item);
		GetRegs(item);
		item.SetIdentifier(VALU.AddItem(item));
  };

  //
  // marca recursos em uso e adiciona item ao buffer de ordenacao
  //
  SetRegs(item);
  ROB.AddItem(item);

  Disq.RemoveItem();
  SendToDispatchBuff(item);
}

void
TCpu::Pentium()
{
  TData item1, item2;

  // processa para a primeira instrucao da fila
  if( Disq.IsEmpty() ) return;
  Disq.GetItem(item1);

  //
  // despacha a instrucao a unidade virtual correspondente
  //
  switch(item1.UF) {
	 case UNIT_BPU :
		if( VBPU.IsFull() ) return;
		item1.SetDispatchController();
		DispStopped = TRUE;
		CheckIfIsReady(item1);
		GetRegs(item1);
		item1.SetIdentifier(VBPU.AddItem(item1));
		break;
	 case UNIT_FPU :
		if( VFPU.IsFull() ) return;
		CheckIfIsReady(item1);
		GetRegs(item1);
		item1.SetIdentifier(VFPU.AddItem(item1));
		break;
	 case UNIT_LSU :
		if( VLSU.IsFull() ) return;
		CheckIfIsReady(item1);
		GetRegs(item1);
		item1.SetIdentifier(VLSU.AddItem(item1));
		break;
	 case UNIT_ALU :
		if( VALU.IsFull() ) return;
		CheckIfIsReady(item1);
		GetRegs(item1);
		item1.SetIdentifier(VALU.AddItem(item1));
  };

  //
  // marca recursos em uso e adiciona item ao buffer de ordenacao
  //
  SetRegs(item1);
  ROB.AddItem(item1);

  Disq.RemoveItem();
  SendToDispatchBuff(item1);

  if(( DispStopped ) || ( ROB.IsFull() )) return;

  // processa para a segunda instrucao da fila
  if( Disq.IsEmpty() ) return;
  Disq.GetItem(item2);

  //
  // verifica dependencia de recursos
  //
  if((item1.GetDependenceType(item2) & (D_FALSE | D_TRUE)) != 0) return;

  //
  // despacha a instrucao a unidade virtual correspondente
  //
  switch(item2.UF) {
	 case UNIT_BPU :
		if( VBPU.IsFull() ) return;
		item2.SetDispatchController();
		DispStopped = TRUE;
		CheckIfIsReady(item2);
		GetRegs(item2);
		item2.SetIdentifier(VBPU.AddItem(item2));
		break;
	 case UNIT_FPU :
		if( VFPU.IsFull() ) return;
		CheckIfIsReady(item2);
		GetRegs(item2);
		item2.SetIdentifier(VFPU.AddItem(item2));
		break;
	 case UNIT_LSU :
		if( VLSU.IsFull() ) return;
		CheckIfIsReady(item2);
		GetRegs(item2);
		item2.SetIdentifier(VLSU.AddItem(item2));
		break;
	 case UNIT_ALU :
		if( VALU.IsFull() ) return;
		CheckIfIsReady(item2);
		GetRegs(item2);
		item2.SetIdentifier(VALU.AddItem(item2));
  };

  //
  // marca recursos em uso e adiciona item ao buffer de ordenacao
  //
  SetRegs(item2);
  ROB.AddItem(item2);

  Disq.RemoveItem();
  SendToDispatchBuff(item2);
}

void
TCpu::PowerPC()
{
  TData item1, item2, item3;

  //
  // processa primeira instrucao da fila de despacho
  //

  if( ROB.IsFull() ) return;

  if( Disq.IsEmpty() ) return;
  Disq.GetItem(item1);

  switch(item1.UF) {
	 case UNIT_FPU :
		if( VFPU.IsFull() ) return;
		CheckIfIsReady(item1);
		GetRegs(item1);
		item1.SetIdentifier(VFPU.AddItem(item1));
		break;
	 case UNIT_LSU :
		if( VLSU.IsFull() ) return;
		CheckIfIsReady(item1);
		GetRegs(item1);
		item1.SetIdentifier(VLSU.AddItem(item1));
		break;
	 case UNIT_ALU :
		if( VALU.IsFull() ) return;
		CheckIfIsReady(item1);
		GetRegs(item1);
		item1.SetIdentifier(VALU.AddItem(item1));
		break;
	 case UNIT_BPU :
		if( VBPU.IsFull() ) return;
		CheckIfIsReady(item1);
		GetRegs(item1);
		item1.SetIdentifier(VBPU.AddItem(item1));
  };

  SetRegs(item1);
  ROB.AddItem(item1);

  Disq.RemoveItem();
  SendToDispatchBuff(item1);

  //
  // processa segunda instrucao da fila de despacho
  //

  if( ROB.IsFull() ) return;

  if( Disq.IsEmpty() ) return;
  Disq.GetItem(item2);

  if(( !item2.IsBranch() ) && (item1.UF == item2.UF)) return;

  switch(item2.UF) {
	 case UNIT_FPU :
		if( VFPU.IsFull() ) return;
		CheckIfIsReady(item2);
		GetRegs(item2);
		item2.SetIdentifier(VFPU.AddItem(item2));
		break;
	 case UNIT_LSU :
		if( VLSU.IsFull() ) return;
		CheckIfIsReady(item2);
		GetRegs(item2);
		item2.SetIdentifier(VLSU.AddItem(item2));
		break;
	 case UNIT_ALU :
		if( VALU.IsFull() ) return;
		CheckIfIsReady(item2);
		GetRegs(item2);
		item2.SetIdentifier(VALU.AddItem(item2));
		break;
	 case UNIT_BPU :
		if( VBPU.IsFull() ) return;
		CheckIfIsReady(item2);
		GetRegs(item2);
		item2.SetIdentifier(VBPU.AddItem(item2));
  };

  SetRegs(item2);
  ROB.AddItem(item2);

  Disq.RemoveItem();
  SendToDispatchBuff(item2);

  //
  // processa terceira instrucao da fila de despacho
  //

  if( ROB.IsFull() ) return;

  if( Disq.IsEmpty() ) return;
  Disq.GetItem(item3);

  if(( !item3.IsBranch() ) &&
	  ((item1.UF == item3.UF) || (item2.UF == item3.UF)) ) return;

  switch(item3.UF) {
	 case UNIT_FPU :
		if( VFPU.IsFull() ) return;
		CheckIfIsReady(item3);
		GetRegs(item3);
		item3.SetIdentifier(VFPU.AddItem(item3));
		break;
	 case UNIT_LSU :
		if( VLSU.IsFull() ) return;
		CheckIfIsReady(item3);
		GetRegs(item3);
		item3.SetIdentifier(VLSU.AddItem(item3));
		break;
	 case UNIT_ALU :
		if( VALU.IsFull() ) return;
		CheckIfIsReady(item3);
		GetRegs(item3);
		item3.SetIdentifier(VALU.AddItem(item3));
		break;
	 case UNIT_BPU :
		if( VBPU.IsFull() ) return;
		CheckIfIsReady(item3);
		GetRegs(item3);
		item3.SetIdentifier(VBPU.AddItem(item3));
  };

  SetRegs(item3);
  ROB.AddItem(item3);

  Disq.RemoveItem();
  SendToDispatchBuff(item3);
}

void
TCpu::Alpha()
{
  TData item1, item2;

  if( ROB.IsFull() ) return;

  // processa para a primeira instrucao da fila
  if( Disq.IsEmpty() ) return;
  Disq.GetItem(item1);

  //
  // despacha a instrucao a unidade virtual correspondente
  //
  switch(item1.UF) {
	 case UNIT_BPU :
		if( VBPU.IsFull() ) return;
		item1.SetDispatchController();
		CheckIfIsReady(item1);
		GetRegs(item1);
		item1.SetIdentifier(VBPU.AddItem(item1));
		break;
	 case UNIT_FPU :
		if( VFPU.IsFull() ) return;
		item1.SetDispatchController();
		CheckIfIsReady(item1);
		GetRegs(item1);
		item1.SetIdentifier(VFPU.AddItem(item1));
		break;
	 case UNIT_LSU :
		if( VLSU.IsFull() ) return;
		item1.SetDispatchController();
		CheckIfIsReady(item1);
		GetRegs(item1);
		item1.SetIdentifier(VLSU.AddItem(item1));
		break;
	 case UNIT_ALU :
		if( VALU.IsFull() ) return;
		item1.SetDispatchController();
		CheckIfIsReady(item1);
		GetRegs(item1);
		item1.SetIdentifier(VALU.AddItem(item1));
  };

  //
  // marca recursos em uso e adiciona item ao buffer de ordenacao
  //
  SetRegs(item1);
  ROB.AddItem(item1);

  Disq.RemoveItem();
  SendToDispatchBuff(item1);

  if( ROB.IsFull() ) return;

  // processa a segunda instrucao lida
  if( Disq.IsEmpty() ) return;
  Disq.GetItem(item2);

  //
  // verifica dependencia de recursos
  //
  if((item1.GetDependenceType(item2) & (D_FALSE | D_TRUE)) != 0) return;

  //
  // despacha a instrucao a unidade virtual correspondente
  //
  switch(item2.UF) {
	 case UNIT_BPU :
		if( VBPU.IsFull() ) return;
		item2.SetDispatchController();
		CheckIfIsReady(item2);
		GetRegs(item2);
		item2.SetIdentifier(VBPU.AddItem(item2));
		break;
	 case UNIT_FPU :
		if( VFPU.IsFull() ) return;
		item2.SetDispatchController();
		CheckIfIsReady(item2);
		GetRegs(item2);
		item2.SetIdentifier(VFPU.AddItem(item2));
		break;
	 case UNIT_LSU :
		if( VLSU.IsFull() ) return;
		item2.SetDispatchController();
		CheckIfIsReady(item2);
		GetRegs(item2);
		item2.SetIdentifier(VLSU.AddItem(item2));
		break;
	 case UNIT_ALU :
		if( VALU.IsFull() ) return;
		item2.SetDispatchController();
		CheckIfIsReady(item2);
		GetRegs(item2);
		item2.SetIdentifier(VALU.AddItem(item2));
  };

  //
  // marca recursos em uso e adiciona item ao buffer de ordenacao
  //
  SetRegs(item2);
  ROB.AddItem(item2);

  Disq.RemoveItem();
  SendToDispatchBuff(item2);
}

void
TCpu::IF()
{
  TData data;

  WORD_T dest;
  int pred;

  for(int i = 0; i < NUMINST; i++)
  {
	 if( IQ.IsFull() ) return;

	 Mem.RD(PC, &IR, sizeof(WORD_T));

	 data.SetItem(PC, IR);
	 data.SetBranchLevel(Disq.CurrentBranchLevel());

	 if( data.IsBranch() )
	 {
		if(Disq.CurrentBranchLevel() >= MAXBLEVEL) return;
		Disq.IncrementBranchLevel();

		if(( BTB.ExistEntry(PC, dest, pred) ) && (pred == BP_TAKEN))
		{
		  data.SetBranchTake();
		  data.PC0 = PC = dest;
		}
		else
		{
		  data.SetBranchNotTake();
		  PC += 4;
		}
	 }
	 else
	 {
		PC += 4;
	 }

	 IQ.AddItem(data);
  }
}

void
TCpu::ID()
{
  TData data;

  for(int i = 0; i < NUMDEC; i++)
  {
	 if(( Disq.IsFull() ) || ( IQ.IsEmpty() )) return;
	 IQ.RemoveItem(data);
	 data.DecodeData();
	 Disq.AddItem(data);
  }
}

void
TCpu::DS()
{
  if(( DispStopped ) || ( ROB.IsFull() )) return;

  switch( CpuType ) {
	 case ESCALAR :
		Escalar();
		break;
	 case PENTIUM :
		Pentium();
		break;
	 case POWERPC :
		PowerPC();
		break;
	 case ALPHA :
		Alpha();
  };
}

void
TCpu::EX()
{
  int i;

  for(i = 0; i < NUM_ALU; i++)
	 if(( !VALU.IsEmpty() ) && ( !Temp_ALU[i].IsReady() )) EX_ALU(Temp_ALU[i]);

  for(i = 0; i < NUM_FPU; i++)
	 if(( !VFPU.IsEmpty() ) && ( !Temp_FPU[i].IsReady() )) EX_FPU(Temp_FPU[i]);

  for(i = 0; i < NUM_LSU; i++)
	 if(( !VLSU.IsEmpty() ) && ( !Temp_LSU[i].IsReady() )) EX_LSU(Temp_LSU[i]);

  for(i = 0; i < NUM_BPU; i++)
	 if(( !VBPU.IsEmpty() ) && ( !Temp_BPU[i].IsReady() )) EX_BPU(Temp_BPU[i]);
}

void
TCpu::MEM()
{
  int j, i = 0;

  for(j = 0; j < NUM_ALU; j++)
	 if( Temp_ALU[j].IsReady() )
	 {
		MEM_ALU(Temp_ALU[j]);
		i++;
	 }

  for(j = 0; j < NUM_FPU; j++)
	 if( Temp_FPU[j].IsReady() )
	 {
		MEM_FPU(Temp_FPU[j]);
		i++;
	 }

  for(j = 0; j < NUM_LSU; j++)
	 if( Temp_LSU[j].IsReady() )
	 {
		MEM_LSU(Temp_LSU[j]);
		i++;
	 }

  for(j = 0; j < NUM_BPU; j++)
	 if( Temp_BPU[j].IsReady() )
	 {
		MEM_BPU(Temp_BPU[j]);
		i++;
	 }

  cont[i] += 1;
}

void
TCpu::WB()
{
  TData item;

  while( !ROB.IsEmpty() ) {
	 ROB.GetItem(item);
	 if( !item.IsReady() )
		break;
	 if( item.IsHaltInstruction() )
		CpuState = STOPPED;
	 UpdRRegs(item);
	 ROB.RemoveItem();
	 Tempo_seq += 6;
	 Tempo_paralelo = Cicle;
  };
}

void
TCpu::EX_ALU(TData &tempdat)
{
  LATCH_T A, B;
  LATCH_T C;

  WORD_T Temp;
  TData d;

  if( !VALU.GetReadyItem(d) ) return;
  SendToExecBuff(d);

  A = d.Vr1;
  B = d.Vr2;

  Temp = d.Imm;
  switch( d.Cmd ) {
	 case _ADD :
		Temp = B.x.W;
	 case _ADDI :
		C = A.x.W + Temp;
		break;
	 case _SUB :
		Temp = B.x.W;
	 case _SUBI :
		C = A.x.W - Temp;
		break;
	 case _MULT :
		Temp = B.x.W;
	 case _MULTI :
		C = A.x.W * Temp;
		break;
	 case _DIV :
		Temp = B.x.W;
	 case _DIVI :
		C = A.x.W / Temp;
		break;
	 case _AND :
		Temp = B.x.W;
	 case _ANDI :
		C = A.x.W & Temp;
		break;
	 case _OR :
		Temp = B.x.W;
	 case _ORI :
		C = A.x.W | Temp;
		break;
	 case _XOR :
		Temp = B.x.W;
	 case _XORI :
		C = A.x.W ^ Temp;
		break;
	 case _SLL :
		Temp = B.x.W;
	 case _SLLI :
		C = A.x.W << (int) Temp;
		break;
	 case _SRL :
		Temp = B.x.W;
	 case _SRLI :
		C = A.x.W;
		for( ; Temp > 0; Temp-- )
		  C = (C.x.W >> 1) & 0x7FFFFFFFL;
		break;
	 case _SRA :
		Temp = B.x.W;
	 case _SRAI :
		C = A.x.W >> (int) Temp;
		break;
	 case _SEQ :
		Temp = B.x.W;
	 case _SEQI :
		C = (A.x.W == Temp) ? 0L : 1L;
		break;
	 case _SNE :
		Temp = B.x.W;
	 case _SNEI :
		C = (A.x.W != Temp) ? 0L : 1L;
		break;
	 case _SLT :
		Temp = B.x.W;
	 case _SLTI :
		C = (A.x.W < Temp) ? 0L : 1L;
		break;
	 case _SGE :
		Temp = B.x.W;
	 case _SGEI :
		C = (A.x.W >= Temp) ? 0L : 1L;
		break;
	 case _SGT :
		Temp = B.x.W;
	 case _SGTI :
		C = (A.x.W > Temp) ? 0L : 1L;
		break;
	 case _SLE :
		Temp = B.x.W;
	 case _SLEI :
		C = (A.x.W <= Temp) ? 0L : 1L;
		break;
	 case _LHI :
		C = (WORD_T) ((Temp << 16) | (A.x.W & 0x0000FFFFL));
  };
  d.Vrd = C;

  tempdat.SetItem(d);
  tempdat.SetReady();
}

void
TCpu::MEM_ALU(TData &tempdat)
{
  // remove item da unidade virtual
  VALU.RemoveItem(tempdat.GetIdentifier());

  // atualiza registradores futuros
  UpdFRegs(tempdat);

  // atualiza entradas nas unidades virtuais
  VALU.UpdateItem(tempdat);
  VFPU.UpdateItem(tempdat);
  VLSU.UpdateItem(tempdat);
  VBPU.UpdateItem(tempdat);

  ROB.UpdateItem(tempdat);

  // libera registrador temporario
  tempdat.SetNotReady();

  // libera despacho bloqueado pela instrucao
  if( tempdat.IsDispatchController() )
	 DispStopped = FALSE;

}

void
TCpu::EX_FPU(TData &tempdat)
{
  LATCH_T A, B;
  LATCH_T C;

  TData d;

  if( !VFPU.GetReadyItem(d) ) return;
  SendToExecBuff(d);

  A = d.Vf1;
  B = d.Vf2;

  switch( d.Cmd ) {
	 case _ADDF :
		C = A.x.F + B.x.F;
		d.Vfd = C;
		break;
	 case _ADDD :
		C = A.x.D + B.x.D;
		d.Vfd = C;
		break;
	 case _SUBF :
		C = A.x.F - B.x.F;
		d.Vfd = C;
		break;
	 case _SUBD :
		C = A.x.D - B.x.D;
		d.Vfd = C;
		break;
	 case _MULTF :
		C = A.x.F * B.x.F;
		d.Vfd = C;
		break;
	 case _MULTD :
		C = A.x.D * B.x.D;
		d.Vfd = C;
		break;
	 case _DIVF :
		C = A.x.F / B.x.F;
		d.Vfd = C;
		break;
	 case _DIVD :
		C = A.x.D / B.x.D;
		d.Vfd = C;
		break;
	 case _CVTF2D :
		C = (DOUBLE_T) A.x.F;
		d.Vfd = C;
		break;
	 case _CVTF2I :
		C = (DOUBLE_T) 0;			// limpa a parte alta do registrador
		C = (WORD_T) A.x.F;
		d.Vfd = C;
		break;
	 case _CVTI2D :
		C = (DOUBLE_T) A.x.W;
		d.Vfd = C;
		break;
	 case _CVTI2F :
		C = (DOUBLE_T) 0;			// limpa a parte alta do registrador
		C = (FLOAT_T) A.x.W;
		d.Vfd = C;
		break;
	 case _CVTD2I :
		C = (DOUBLE_T) 0;			// limpa a parte alta do registrador
		C = (WORD_T) A.x.D;
		d.Vfd = C;
		break;
	 case _CVTD2F :
		C = (DOUBLE_T) 0;   		// limpa a parte alta do registrador
		C = (FLOAT_T) A.x.D;
		d.Vfd = C;
		break;
	 case _SEQF :
		C = (A.x.F == B.x.F) ? 0L : 1L;
		d.Vfp = C;
		break;
	 case _SNEF :
		C = (A.x.F != B.x.F) ? 0L : 1L;
		d.Vfp = C;
		break;
	 case _SLTF :
		C = (A.x.F < B.x.F) ? 0L : 1L;
		d.Vfp = C;
		break;
	 case _SLEF :
		C = (A.x.F <= B.x.F) ? 0L : 1L;
		d.Vfp = C;
		break;
	 case _SGTF :
		C = (A.x.F > B.x.F) ? 0L : 1L;
		d.Vfp = C;
		break;
	 case _SGEF :
		C = (A.x.F >= B.x.F) ? 0L : 1L;
		d.Vfp = C;
		break;
	 case _SEQD :
		C = (A.x.D == B.x.D) ? 0L : 1L;
		d.Vfp = C;
		break;
	 case _SNED :
		C = (A.x.D != B.x.D) ? 0L : 1L;
		d.Vfp = C;
		break;
	 case _SLTD :
		C = (A.x.D < B.x.D) ? 0L : 1L;
		d.Vfp = C;
		break;
	 case _SLED :
		C = (A.x.D <= B.x.D) ? 0L : 1L;
		d.Vfp = C;
		break;
	 case _SGTD :
		C = (A.x.D > B.x.D) ? 0L : 1L;
		d.Vfp = C;
		break;
	 case _SGED :
		C = (A.x.D >= B.x.D) ? 0L : 1L;
		d.Vfp = C;
  };

  tempdat.SetItem(d);
  tempdat.SetReady();
}

void
TCpu::MEM_FPU(TData &tempdat)
{
  // remove item da unidade virtual
  VFPU.RemoveItem(tempdat.GetIdentifier());

  // atualiza registradores futuros
  UpdFRegs(tempdat);

  // atualiza entradas nas unidades virtuais
  VALU.UpdateItem(tempdat);
  VFPU.UpdateItem(tempdat);
  VLSU.UpdateItem(tempdat);
  VBPU.UpdateItem(tempdat);

  ROB.UpdateItem(tempdat);

  // libera registrador temporario
  tempdat.SetNotReady();

  // libera despacho bloqueado pela instrucao
  if( tempdat.IsDispatchController() )
	 DispStopped = FALSE;
}

void
TCpu::EX_BPU(TData &tempdat)
{
  LATCH_T A, C;

  TData d;

  WORD_T Imm, Offset;

  WORD_T IAR0, FP0;
  WORD_T PC0;

  if( !VBPU.GetReadyItem(d) ) return;
  SendToExecBuff(d);

  A = d.Vr1;

  PC0 = d.PC;

  IAR0 = d.Viar.x.W;
  FP0 = d.Vfp.x.W;

  Imm = d.Imm;
  Offset = d.Offset;

  switch( d.Cmd ) {
	 case _JAL :
		C = PC0;
		d.Vrd = C;
	 case _J :
		d.PC1 = PC0 + Offset;
		d.SetBranchResultTake();
		break;
	 case _JALR :
		C = PC0;
		d.Vrd = C;
	 case _JR :
		d.PC1 = A.x.W + 4;
		d.SetBranchResultTake();
		break;
	 case _TRAP :
		C = PC0;
		d.PC1 = Offset;
		d.Viar = C;
		d.SetBranchResultTake();
		break;
	 case _RFE :
		d.PC1 = IAR0 + 4;
		d.SetBranchResultTake();
		break;
	 case _BEQZ :
		if(A.x.W == 0)
		  d.SetBranchResultTake();
		d.PC1 = PC0 + Imm;
		break;
	 case _BNEZ :
		if(A.x.W != 0)
		  d.SetBranchResultTake();
		d.PC1 = PC0 + Imm;
		break;
	 case _BFPT :
		if(FP0 == 0)
		  d.SetBranchResultTake();
		d.PC1 = PC0 + Offset;
		break;
	 case _BFPF :
		if(FP0 == 0)
		  d.SetBranchResultTake();
		d.PC1 = PC0 + Offset;
		break;
	 case _HALT :
		break;
  };

  tempdat.SetItem(d);
  tempdat.SetReady();
}

void
TCpu::MEM_BPU(TData &tempdat)
{
  if( !tempdat.IsHaltInstruction() )
  {
	 // atualiza tabela de destino dos desvios
	 if( tempdat.IsBranchResultTake() )
	 {
		BTB.AddEntry(tempdat.PC, tempdat.PC1, BP_TAKEN);

		if( ( tempdat.IsBranchTake() ) && (tempdat.PC0 == tempdat.PC1) )
		{
		  Disq.BranchSuccess(tempdat.GetBranchLevel());

		  VALU.BranchSuccess(tempdat.GetBranchLevel());
		  VFPU.BranchSuccess(tempdat.GetBranchLevel());
		  VLSU.BranchSuccess(tempdat.GetBranchLevel());
		  VBPU.BranchSuccess(tempdat.GetBranchLevel());
		}
		else
		{
		  IQ.Flush();

		  Disq.BranchFailure(tempdat.GetBranchLevel());

		  R.Flush();
		  F.Flush();
		  IAR.RestoreValue();
		  FP.RestoreValue();

		  ROB.BranchFailure(tempdat.GetIdentifier());

		  VALU.BranchFailure(tempdat.GetBranchLevel());
		  VFPU.BranchFailure(tempdat.GetBranchLevel());
		  VLSU.BranchFailure(tempdat.GetBranchLevel());
		  VBPU.BranchFailure(tempdat.GetBranchLevel());

		  PC = tempdat.PC1;
		}
	 }
	 else
	 {
		BTB.AddEntry(tempdat.PC, tempdat.PC1, BP_NOTAKEN);

		if( !tempdat.IsBranchTake() )
		{
		  Disq.BranchSuccess(tempdat.GetBranchLevel());

		  VALU.BranchSuccess(tempdat.GetBranchLevel());
		  VFPU.BranchSuccess(tempdat.GetBranchLevel());
		  VLSU.BranchSuccess(tempdat.GetBranchLevel());
		  VBPU.BranchSuccess(tempdat.GetBranchLevel());
		}
		else
		{
		  IQ.Flush();

		  Disq.BranchFailure(tempdat.GetBranchLevel());

		  R.Flush();
		  F.Flush();
		  IAR.RestoreValue();
		  FP.RestoreValue();

		  ROB.BranchFailure(tempdat.GetIdentifier());

		  VALU.BranchFailure(tempdat.GetBranchLevel());
		  VFPU.BranchFailure(tempdat.GetBranchLevel());
		  VLSU.BranchFailure(tempdat.GetBranchLevel());
		  VBPU.BranchFailure(tempdat.GetBranchLevel());

		  PC = tempdat.PC + 4;
		}
	 }
  }

  // remove item da unidade virtual
  VBPU.RemoveItem(tempdat.GetIdentifier());

  // atualiza registradores futuros
  UpdFRegs(tempdat);

  // atualiza entradas nas unidades virtuais
  VALU.UpdateItem(tempdat);
  VFPU.UpdateItem(tempdat);
  VLSU.UpdateItem(tempdat);
  VBPU.UpdateItem(tempdat);

  ROB.UpdateItem(tempdat);

  // libera registrador temporario
  tempdat.SetNotReady();

  // libera despacho bloqueado pela instrucao
  if( tempdat.IsDispatchController() )
	 DispStopped = FALSE;
}

void
TCpu::EX_LSU(TData &tempdat)
{
  LATCH_T A, B;
  LATCH_T C;

  WORD_T Temp;

  TData d;

  if( !VLSU.GetFirstItem(d) ) return;
  SendToExecBuff(d);

  A = d.Vr1;
  B = d.Vr2;

  Temp = d.Imm;
  switch( d.Cmd ) {
	 case _SF :
	 case _SD :
		B = d.Vf1;
	 case _SB :
	 case _SH :
	 case _SW :
		d.MBR = B;
	 case _LB :
	 case _LBU :
	 case _LH :
	 case _LHU :
	 case _LW :
	 case _LF :
	 case _LD :
		d.MAR = A.x.W + Temp;
		break;
	 case _MOVI2S :
		C = A.x.W;
		d.Viar = C;
		break;
	 case _MOVS2I :
		C = d.Viar;
		d.Vrd  = C;
		break;
	 case _MOVFP2I :
		C = d.Vfp;
		d.Vrd = C;
		break;
	 case _MOVI2FP :
		C = A.x.W;
		d.Vfp = C;
		break;
	 case _MOVF :
		C = d.Vf1;
		d.Vfd = C;
		break;
	 case _MOVD :
		C = d.Vf1;
		d.Vfd = C;
  };

  tempdat.SetItem(d);
  tempdat.SetReady();
}

void
TCpu::MEM_LSU(TData &tempdat)
{
  LATCH_T C;

  // conclui o acesso a memoria
  switch( tempdat.Cmd ) {
	 case _SB :
		Mem.WR(tempdat.MAR, &(tempdat.MBR.x.W), sizeof(BYTE_T));
		break;
	 case _SH :
		Mem.WR(tempdat.MAR, &(tempdat.MBR.x.W), sizeof(HWORD_T));
		break;
	 case _SW :
		Mem.WR(tempdat.MAR, &(tempdat.MBR.x.W), sizeof(WORD_T));
		break;
	 case _SF :
		Mem.WR(tempdat.MAR, &(tempdat.MBR.x.F), sizeof(FLOAT_T));
		break;
	 case _SD :
		Mem.WR(tempdat.MAR, &(tempdat.MBR.x.D), sizeof(DOUBLE_T));
		break;
	 case _LB :
		Mem.RD(tempdat.MAR, &(tempdat.MBR.x.W), sizeof(BYTE_T));
		C = (tempdat.MBR).x.W & 0x000000FFL;
		if((tempdat.MBR.x.W & 0x00000080L) != 0)
		  C = (long) (0xFFFFFF00L + C.x.W);
		tempdat.Vrd = C;
		break;
	 case _LBU :
		Mem.RD(tempdat.MAR, &(tempdat.MBR.x.W), sizeof(BYTE_T));
		C = (tempdat.MBR).x.W & 0x000000FFL;
		tempdat.Vrd = C;
		break;
	 case _LH :
		Mem.RD(tempdat.MAR, &(tempdat.MBR.x.W), sizeof(HWORD_T));
		C = (tempdat.MBR).x.W & 0x0000FFFFL;
		if((tempdat.MBR.x.W & 0x00008000L) != 0)
		  C = (long) (0xFFFF0000L + C.x.W);
		tempdat.Vrd = C;
		break;
	 case _LHU :
		Mem.RD(tempdat.MAR, &(tempdat.MBR.x.W), sizeof(HWORD_T));
		C = (tempdat.MBR).x.W & 0x0000FFFFL;
		tempdat.Vrd = C;
		break;
	 case _LW :
		Mem.RD(tempdat.MAR, &(tempdat.MBR.x.W), sizeof(WORD_T));
		C = (tempdat.MBR).x.W;
		tempdat.Vrd = C;
		break;
	 case _LF :
		Mem.RD(tempdat.MAR, &(tempdat.MBR.x.F), sizeof(FLOAT_T));
		C = (tempdat.MBR).x.F;
		tempdat.Vfd = C;
		break;
	 case _LD :
		Mem.RD(tempdat.MAR, &(tempdat.MBR.x.D), sizeof(DOUBLE_T));
		C = (tempdat.MBR).x.D;
		tempdat.Vfd = C;
  };

  // remove item da unidade virtual
  VLSU.RemoveItem(tempdat.GetIdentifier());

  // atualiza registradores futuros
  UpdFRegs(tempdat);

  // atualiza entradas nas unidades virtuais
  VALU.UpdateItem(tempdat);
  VFPU.UpdateItem(tempdat);
  VLSU.UpdateItem(tempdat);
  VBPU.UpdateItem(tempdat);

  ROB.UpdateItem(tempdat);

  // libera registrador temporario
  tempdat.SetNotReady();

  // libera despacho bloqueado pela instrucao
  if( tempdat.IsDispatchController() )
	 DispStopped = FALSE;
}

void
TCpu::CheckIfIsReady(TData& item)
{
  item.SetReady();

  if((item.Biar == R_SRC) && ( IAR.IsBusy() ))
	 item.SetNotReady();
  else if((item.Bfp  == R_SRC) && ( FP.IsBusy() ))
	 item.SetNotReady();
  else if((item.R1 != R_NONE) && ( R.GetRegister(item.R1)->IsBusy() ))
	 item.SetNotReady();
  else if((item.R2 != R_NONE) && ( R.GetRegister(item.R2)->IsBusy() ))
	 item.SetNotReady();
  else if((item.F1 != R_NONE) && ( F.GetRegister(item.F1)->IsBusy() ))
	 item.SetNotReady();
  else if((item.F2 != R_NONE) && ( F.GetRegister(item.F2)->IsBusy() ))
	 item.SetNotReady();
}

void
TCpu::GetRegs(TData& item)
{
  TRegs* r;
  TRegs* f;

  if(item.Biar == R_SRC)
	 if( !IAR.IsBusy() )
		item.Viar = IAR.R1;
	 else
		item.Qiar = IAR.GetIdentifier();

  if(item.Bfp == R_SRC)
	 if( !FP.IsBusy() )
		item.Vfp = FP.R1;
	 else
		item.Qfp = FP.GetIdentifier();

  if(item.R1 != R_NONE)
	 if( !(r = R.GetRegister(item.R1))->IsBusy() )
		item.Vr1 = r->R1;
	 else
		item.Qr1 = r->GetIdentifier();

  if(item.R2 != R_NONE)
	 if( !(r = R.GetRegister(item.R2))->IsBusy() )
		item.Vr2 = r->R1;
	 else
		item.Qr2 = r->GetIdentifier();

  if(item.F1 != R_NONE)
	 if( !(f = F.GetRegister(item.F1))->IsBusy() )
		item.Vf1 = f->R1;
	 else
		item.Qf1 = f->GetIdentifier();

  if(item.F2 != R_NONE)
	 if( !(f = F.GetRegister(item.F2))->IsBusy() )
		item.Vf2 = f->R1;
	 else
		item.Qf2 = f->GetIdentifier();
}

void
TCpu::SetRegs(TData& item)
{
  TRegs* r;
  TRegs* f;

  //
  // ativa bit ocupado dos registradores de controle destino
  // obtem o valor dos registradores de controle fonte
  //
  if(item.Biar == R_DST)
  {
	 IAR.SetBusy();
	 IAR.SetIdentifier(item.GetIdentifier());
  }

  if(item.Bfp == R_DST)
  {
	 FP.SetBusy();
	 FP.SetIdentifier(item.GetIdentifier());
  }

  //
  // ativa bit ocupado para os registradores de proposito geral destino
  //
  if(item.Rd != R_NONE)
  {
	 (r = R.GetRegister(item.Rd))->SetBusy();
	 r->SetIdentifier(item.GetIdentifier());
  }

  //
  // ativa bit ocupado para os registradores de proposito geral destino
  //
  if(item.Fd != R_NONE)
  {
	 (f = F.GetRegister(item.Fd))->SetBusy();
	 f->SetIdentifier(item.GetIdentifier());
  }
}

void
TCpu::UpdFRegs(TData& item)
{
  TRegs* r;
  TRegs* f;

  //
  // atualizando registradores de controle
  //
  if( (item.Biar == R_DST) && (IAR.GetIdentifier() == item.GetIdentifier()) )
  {
	 IAR.R1 = item.Viar;
	 IAR.SetFree();
  }

  if((item.Bfp == R_DST) && (FP.GetIdentifier() == item.GetIdentifier()))
  {
	 FP.R1 = item.Vfp;
	 FP.SetFree();
  }

  //
  // atualiza os valores dos registradores de proposito gerais (reais)
  //
  if(item.Rd != R_NONE)
	 if((r = R.GetRegister(item.Rd))->GetIdentifier() == item.GetIdentifier())
	 {
		if(item.Rd != 0)
		  r->R1 = item.Vrd;
		r->SetFree();
	 }

  //
  // atualiza os valores dos registradores de ponto flutuante (reais)
  //
  if(item.Fd != R_NONE)
	 if((f = F.GetRegister(item.Fd))->GetIdentifier() == item.GetIdentifier())
	 {
		f->R1 = item.Vfd;
		f->SetFree();
	 }
}

void
TCpu::UpdRRegs(TData& item)
{
  //
  // atualiza valores dos registradores de controle
  //
  if(item.Biar == R_DST)
  {
	 IAR.R = item.Viar;
	 IAR.R1 = item.Viar;
  }

  if(item.Bfp == R_DST)
  {
	 FP.R = item.Vfp;
	 FP.R1 = item.Vfp;
  }

  //
  // atualiza os valores dos registradores de proposito gerais (reais)
  //
  if((item.Rd != R_NONE) && (item.Rd != 0))
  {
	 R.GetRegister(item.Rd)->R = item.Vrd;
	 R.GetRegister(item.Rd)->R1 = item.Vrd;
  }

  //
  // atualiza os valores dos registradores de ponto flutuante (reais)
  //
  if(item.Fd != R_NONE)
  {
	 F.GetRegister(item.Fd)->R = item.Vfd;
	 F.GetRegister(item.Fd)->R1 = item.Vfd;
  }
}

void
TCpu::Tick()
{
  WB();
  MEM();
  EX();
  DS();
  ID();
  IF();
  Cicle++;
}

TCpu::TCpu()
  : VALU(VU_ALU),
	 VBPU(VU_BPU),
	 VLSU(VU_LSU),
	 VFPU(VU_FPU),
	 DispBuff(STREAM_BUFFSZ),
	 ExecBuff(STREAM_BUFFSZ)
{
  Reset();
}

void
TCpu::SendToDispatchBuff(TData item)
{
  char ibuf[40], sbuf[80];
  if( !IsDispatchStreamEnable() ) return;
  item.GetInstStr(ibuf);
  sprintf(sbuf, "cicle(%08lX):  %08lX %s", Cicle, item.PC, ibuf);
  DispBuff.AddStrToBuff(sbuf);
}

void
TCpu::SendToExecBuff(TData item)
{
  char ibuf[40], sbuf[80];
  if( !IsExecStreamEnable() ) return;
  item.GetInstStr(ibuf);
  switch(item.UF) {
	 case UNIT_LSU :
		sprintf(sbuf, "cicle(%08lX): [ LSU ]  %08lX %s", Cicle, item.PC, ibuf);
		break;
	 case UNIT_BPU :
		sprintf(sbuf, "cicle(%08lX): [ BPU ]  %08lX %s", Cicle, item.PC, ibuf);
		break;
	 case UNIT_FPU :
		sprintf(sbuf, "cicle(%08lX): [ FPU ]  %08lX %s", Cicle, item.PC, ibuf);
		break;
	 case UNIT_ALU :
		sprintf(sbuf, "cicle(%08lX): [ ALU ]  %08lX %s", Cicle, item.PC, ibuf);
  };

  ExecBuff.AddStrToBuff(sbuf);
}

void
TCpu::OpenFile(const char* fname)
{
  Mem.LoadFile(fname);
  Reset();
}

void
TCpu::DisableDispatchStream()
{
  DispatchStreamBit = 0;
}

void
TCpu::EnableDispatchStream()
{
  DispatchStreamBit = 1;
}

void
TCpu::Reset()
{
  int i;

  Cicle = 0L;

  PC = 0L;

  Tempo_seq = 0;
  Tempo_paralelo = 0;

  for(i = 0; i < NUM_UNIT + 1; i++)
	 cont[i] = 0;

  FP.SetFree();
  IAR.SetFree();

  R.Flush();
  F.Flush();

  IQ.Flush();
  Disq.Flush();
  BTB.Flush();
  ROB.Flush();

  VALU.Flush();
  VBPU.Flush();
  VFPU.Flush();
  VLSU.Flush();

  for(i = 0; i < NUM_ALU; i++)
	 Temp_ALU[i].Reset();
  for(i = 0; i < NUM_BPU; i++)
	 Temp_BPU[i].Reset();
  for(i = 0; i < NUM_FPU; i++)
	 Temp_FPU[i].Reset();
  for(i = 0; i < NUM_LSU; i++)
	 Temp_LSU[i].Reset();

  DispStopped = FALSE;

  CpuState = RUNNING;

  ExecBuff.FlushBuff();
  DispBuff.FlushBuff();
}

void
TCpu::Run()
{
  if(CpuState == STOPPED) {
	 ::MessageBox(0, "CPU State = (HALTED)", "Atention!", MB_OK);
	 return;
  }

  while(CpuState == RUNNING)
	 Tick();
}

void
TCpu::Runn(long ncicles)
{
  if(CpuState == STOPPED) {
	 ::MessageBox(0, "CPU State = (HALTED)", "Atention!", MB_OK);
	 return;
  }

  while((CpuState == RUNNING) && (ncicles-- > 0))
	 Tick();
}

void
TCpu::Step()
{
  if(CpuState == RUNNING)
	 Tick();
  else
	 ::MessageBox(0, "CPU State = (HALTED)", "Atention!", MB_OK);
}

