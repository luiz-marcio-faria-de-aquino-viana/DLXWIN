
/*
/* TIQUEUE.cpp
/* por Luiz Marcio F A Viana, 10/24/96
*/

#include"h\tiqueue.h"

/********************************************
/* codigo do grupo de depuracao de erros (=101)
/********************************************/

/* implementacao da classe fila de instrucoes
*/
TIQueue::TIQueue()
{
  try {
	 ptrQueue = new TData[(NEntries = IQUEUE_NENTRIES)];
	 NItens = 0;
  }
  catch(xmsg& err) {
	 errmsg(IQUEUE_ERRGROUP, 41, err);
  }
}

TIQueue::~TIQueue()
{
  delete[] ptrQueue;
}

void
TIQueue::RemoveItem(TData& _item)
{
  if( IsEmpty() ) return;
  _item = ptrQueue[0];
  for(int i = 1; i < NItens; i++)
	 ptrQueue[i - 1] = ptrQueue[i];
  NItens -= 1;
}

