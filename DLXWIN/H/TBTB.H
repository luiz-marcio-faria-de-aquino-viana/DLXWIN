
/*
/* TBTB.h
/* por Luiz Marcio F A Viana, 10/25/96
*/

#ifndef __TBTB_H
#define __TBTB_H

#include<except.h>
#pragma hdrstop
#include"h\dlx.h"
#include"h\error.h"
#include"h\tbtb.h"

/* declaracao da classe item da tabela de destino de desvios
*/
class TBTBItem {
private:
  int Val;
  int B1, B2;			// bits para previsao do desvio
public:
  int Cnt;

  WORD_T Tag;
  WORD_T Dst;

  TBTBItem()
	 { SetupItem(); }

  int IsValid()
	 { return Val; }
  void SetInvalidBit()
	 { Val = 0; }

  int BranchPrediction()
	 { return((B1 == 1) ? BP_TAKEN : BP_NOTAKEN); }

  void SetBranchTaken()
	 { ((B1 == 0) && (B2 == 0)) ? B2 = 1 : B1 = B2 = 1; }
  void SetBranchNotTaken()
	 { ((B1 == 1) && (B2 == 1)) ? B2 = 0 : B1 = B2 = 0; }

  void SetPrediction(int _pred);

  void SetItem(WORD_T _tag, WORD_T _dst);
protected:
  void SetupItem();
};

/* declaracao da classe da tabela de destino de desvios
*/
class TBTB {
private:
  TBTBItem** ptrBTB;
  int NSlots;
  int NEntries;

  TBTBItem* cip;
public:
  TBTB();
  ~TBTB();

  int GetNumSlots()
	 { return NSlots; }

  int GetNumEntries()
	 { return NEntries; }

  TBTBItem* GetItem(int nslot, int nentry)
	 { return ((nslot < NSlots) && (nentry < NEntries)) ? &ptrBTB[nslot][nentry] : 0; }

  int ExistEntry(WORD_T _addr, WORD_T& _dst, int& _pred);
  void AddEntry(WORD_T _addr, WORD_T _dst, int _pred);

  void Flush();
private:
  WORD_T CalcTag(WORD_T _addr)
	 { return (_addr > 0) ? (_addr / NSlots) : (- _addr / NSlots); }
  int CalcSlot(WORD_T _addr)
	 { return (_addr > 0) ? ((int) (_addr % NSlots)) : ((int) (- _addr % NSlots)); }
};

#endif  /* __TBTB_H */

