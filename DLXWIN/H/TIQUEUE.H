
/*
/* TIQUEUE.h
/* por Luiz Marcio F A Viana, 10/23/96
*/

#ifndef __TIQUEUE_H
#define __TIQUEUE_H

#include<except.h>
#pragma hdrstop
#include"h\dlx.h"
#include"h\error.h"
#include"h\tdata.h"

/* declaracao da classe fila de instrucoes
*/
class TIQueue {
  TData* ptrQueue;

  int NEntries;
  int NItens;
public:
  TIQueue();
  ~TIQueue();

  int IsEmpty()
	 { return(NItens == 0); }
  int IsFull()
	 { return(NItens == NEntries); }

  int GetNumEntries()
	 { return NEntries; }

  int GetNumItens()
	 { return NItens; }

  TData* GetItem(int idx)
	 { return (idx < NItens) ? &ptrQueue[idx] : 0; }

  void AddItem(TData& _item)
	 { if( !IsFull() ) ptrQueue[NItens++] = _item; }

  void RemoveItem(TData& _item);

  void Flush()
	 { NItens = 0; }
};

#endif  /* __TIQUEUE_H */

