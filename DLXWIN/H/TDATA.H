
/*
/* TDATA.h
/* por Luiz Marcio F A Viana, 12/8/96
*/

#ifndef __TDATA_H
#define __TDATA_H

#include<except.h>
#pragma hdrstop
#include"h\dlx.h"
#include"h\error.h"
#include"h\decode.h"
#include"h\latch.h"

/* declaracao da classe de dados
*/
class TData {
protected:

  int BB;		// bit indicador de instrucao de desvio
  int BT;		// bit indicador de desvio tomado
  int BR;      // bit indicador do resultado do desvio

  int BL;		// indicador do nivel de execucao expeculativa

  int RD;		// bit indicador de instrucao pronta
  int DP;		// bit indicador de instrucao de controle do despacho

  int ID;		// identificador da unidade virtual

  int HLT;		// bit indicador de instrucao de parada de processamento

public:

  WORD_T PC; 		// endereco da instrucao
  WORD_T IR;		// codigo da instrucao

  WORD_T PC0;		// endereco alvo previsto
  WORD_T PC1;		// endereco alvo do desvio

  WORD_T MAR;		// endereco para acesso a memoria
  LATCH_T MBR;		// registrador de acesso a memoria

  int VU;		// identificador do tipo da unidade virtual
  int UF;		// identificador da unidade funcional
  int Cmd;		// identificador da operacao

  int R1, R2, Rd;		// bits identificadores dos registros
  int F1, F2, Fd;

  int Biar, Bfp;		// bits indicadores da utilizacao dos registradores

  int Qr1, Qr2, Qrd;		// indicadores da unidade virtual fonte dos valores
  int Qf1, Qf2, Qfd;
  int Qiar, Qfp;

  LATCH_T Vr1, Vr2, Vrd;		// armazena os valores dos registradores
  LATCH_T Vf1, Vf2, Vfd;
  LATCH_T Viar, Vfp;

  WORD_T Imm;   		// valor imediato
  WORD_T Offset;		// valor do deslocamento

  TData();

  int IsBranch()
	 { return BB; }

  int IsBranchTake()
	 { return BT; }

  void SetBranchTake()
	 { BT = 1; }
  void SetBranchNotTake()
	 { BT = 0; }

  int IsBranchResultTake()
	 { return BR; }

  void SetBranchResultTake()
	 { BR = 1; }
  void SetBranchResultNotTake()
	 { BR = 0; }

  int GetBranchLevel()
	 { return BL; }
  void SetBranchLevel(int _val)
	 { BL = _val; }

  int IsReady()
	 { return RD; }

  void SetReady()
	 { RD = 1; }
  void SetNotReady()
	 { RD = 0; }

  int IsDispatchController()
	 { return DP; }

  void SetDispatchController()
	 { DP = 1; }

  int GetIdentifier()
	 { return ID; }

  void SetIdentifier(int id)
	 { ID = id; }

  int IsHaltInstruction()
	 { return HLT; }

  void SetItem(WORD_T pc, WORD_T ir);
  void SetItem(TData& d);

  TData& operator=(TData& d);

  void Reset();

  void DecodeData();

  int GetDependenceType(TData d);

  void GetInstStr(char* s);

protected:
  void SetupItem();
  void ClearBits();
};

#endif  /* __TDATA_H */

