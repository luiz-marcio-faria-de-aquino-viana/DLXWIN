
/*
/* TROB.h
/* por Luiz Marcio F A Viana, 11/17/96
*/

#ifndef __TROB_H
#define __TROB_H

#include<except.h>
#pragma hdrstop
#include"h\dlx.h"
#include"h\error.h"
#include"h\tdata.h"
#include"h\latch.h"

/* declaracao da classe buffer de ordenacao
*/
class TROB {
private:
  TData* ptrROB;
  int NEntries;
  int NItens;
public:
  TROB();
  ~TROB();

  int IsEmpty()
	 { return(NItens == 0); }
  int IsFull()
	 { return(NItens == NEntries); }

  int GetNumEntries()
	 { return NEntries; }

  int GetNumItens()
	 { return NItens; }

  TData* GetItemNum(int idx)
    { return (idx < NItens) ? &ptrROB[idx] : 0; }

  void AddItem(TData _item);

  void UpdateItem(TData _data);

  void GetItem(TData& _item)
	 { if( !IsEmpty() ) _item = ptrROB[0]; }

  void RemoveItem();

  void BranchFailure(int _id);

  void Flush()
	 { NItens = 0; }
};

#endif  /* __TROB_H */

