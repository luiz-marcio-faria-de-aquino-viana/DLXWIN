
/*
/* TDISQ.h
/* por Luiz Marcio F A Viana, 10/24/96
*/

#ifndef __TDISQ_H
#define __TDISQ_H

#include<except.h>
#pragma hdrstop
#include"h\dlx.h"
#include"h\error.h"
#include"h\tdata.h"

/* declaracao da classe fila de despacho
*/
class TDisq {
private:
  TData *ptrDisq;
  int NEntries;
  int NItens;

  int cbl;			// valor corrente do nivel de execucao expeculativa
public:
  TDisq();
  ~TDisq();

  int IsEmpty()
	 { return(NItens == 0); }
  int IsFull()
	 { return(NItens == NEntries); }

  int GetNumEntries()
	 { return NEntries; }

  int GetNumItens()
	 { return NItens; }

  TData* GetItemNum(int idx)
	 { return (idx < NItens) ? &ptrDisq[idx] : 0; }

  int CurrentBranchLevel()
	 { return cbl; }

  void IncrementBranchLevel()
	 { cbl += 1; }

  void AddItem(TData& _item)
	 { if( !IsFull() ) ptrDisq[NItens++] = _item; }
  void GetItem(TData& _item)
	 { if( !IsEmpty() ) _item = ptrDisq[0]; }

  void RemoveItem();

  int GetFirstBranchItem(TData& _item);
  void RemoveFirstBranchItem();

  void BranchSuccess(int _val);
  void BranchFailure(int _val);

  void Flush();
};

#endif  /* __TDISQ_H */

