
/*
/* TCPU.h
/* por Luiz Marcio F A Viana, 11/3/96
*/

#ifndef __TCPU_H
#define __TCPU_H

#include<except.h>
#include<cstring.h>
#include<windows.h>
#pragma hdrstop
#include"h\dlx.h"
#include"h\error.h"
#include"h\tmem.h"
#include"h\decode.h"
#include"h\tdata.h"
#include"h\tiqueue.h"
#include"h\tdisq.h"
#include"h\tbtb.h"
#include"h\latch.h"
#include"h\tregs.h"
#include"h\tgpr.h"
#include"h\tfpr.h"
#include"h\tvu.h"
#include"h\trob.h"
#include"h\tstream.h"

/* declaracao da classe unidade de controle
*/
class TCpu {
public:

  long Cicle;				// contador de ciclos executados

  WORD_T PC;		// declaracao dos registradores internos a cpu
  WORD_T IR;

  TRegs FP;
  TRegs IAR;

  TGpr R;
  TFpr F;

  double Tempo_seq;			// contador do numero de ciclos sequencial
  double Tempo_paralelo;  	// contador do numero de ciclos paralelo

  long cont[NUM_UNIT + 1];	// contador da taxa de utilizacao das unidedes de execucao

  TMem    Mem;		// unidades funcionais reais da cpu
  TIQueue IQ;
  TBTB    BTB;
  TDisq   Disq;
  TROB    ROB;

  TVUGR VALU;		// unidades funcionais virtuais da cpu
  TVUGR VBPU;
  TVUGR VFPU;
  TVUGR VLSU;

  TData Temp_ALU[NUM_ALU];		// registradores temporarios para comunicacao
  TData Temp_BPU[NUM_BPU];		//       entre os estagios EX e MEM
  TData Temp_FPU[NUM_FPU];
  TData Temp_LSU[NUM_LSU];

  //
  // declaracao dos buffers de saida do fluxo de despacho e execucao
  //

  TStreamBuff DispBuff;
  TStreamBuff ExecBuff;

private:

  int CpuType;				// indicador do algoritimo de despacho
  int CpuState;  			// bit indicador do estado da cpu

  int DispStopped;		// bit indicador de despacho interrompido

  int ExecStreamBit;				// bit de depuracao do fluxo de execucao
  int DispatchStreamBit;		// bit de depuracao do fluxo de despacho

  // algoritiomos de despacho implementados

  void Escalar();		// algoritimo sequencial simples
  void Pentium();		// algoritimo do Pentium
  void PowerPC();		// algoritimo do PowerPC 603
  void Alpha();		// algoritimo do Alpha AXP21064

  // declaracao dos estagios de execucao das instrucoes

  void IF();		// estagio de busca
  void ID();		// estagio de decodificacao
  void DS();		// estagio de despacho
  void EX();		// estagio de execucao
  void MEM();		// estagio de acesso a memoria
  void WB();		// estagio de atualizacao dos resultados

  // declaracao dos estagios de execucao das unidades funcionais reais

  void EX_ALU(TData &tempdat);	// estagio de execucao da unidade logica e aritimetica
  void MEM_ALU(TData &tempdat); // estagio de conclusao da unidade logica e aritimetica

  void EX_FPU(TData &tempdat);  // estagio de execucao da unidade de ponto-flutuante
  void MEM_FPU(TData &tempdat); // estagio de conclusao da unidade de ponto-flutuante

  void EX_BPU(TData &tempdat);  // estagio de execucao da unidade de desvios
  void MEM_BPU(TData &tempdat);	// estagio de conclusao da unidade de desvios

  void EX_LSU(TData &tempdat);	// estagio de busca aos operandos da unidade load/store
  void MEM_LSU(TData &tempdat); // estagio de acesso a memoria da unidade load/store

  void CheckIfIsReady(TData& item);		// analisa se instrucao pronta para exec

  void GetRegs(TData& item);		// obtem valores dos registradores
  void SetRegs(TData& item);		// seleciona registradores

  void UpdFRegs(TData& item);	  	// atualiza registradores futuros
  void UpdRRegs(TData& item);		// atualiza registradores reais

  void Tick();		// executa um ciclo da cpu

  void SendToExecBuff(TData item);
  void SendToDispatchBuff(TData item);

public:

  TCpu();

  void OpenFile(const char* fname);

  void SetCpuType(int _typ)
	 { CpuType = _typ; }

  int IsExecStreamEnable()
	 { return ExecStreamBit; }

  void DisableExecStream()
	 { ExecStreamBit = 0; }
  void EnableExecStream()
	 { ExecStreamBit = 1; }

  int IsDispatchStreamEnable()
	 { return DispatchStreamBit; }

  void DisableDispatchStream();
  void EnableDispatchStream();

  void Reset();

  void Run();

  void Runn(long ncicles);

  void Step();

  WORD_T GetCurrentAddress()
    { return PC; }

};

#endif  /* __TCPU_H */

