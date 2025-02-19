
/*
/* TROB.cpp
/* por Luiz Marcio F A Viana, 11/17/96
*/

#include"h\trob.h"

/********************************************
/* codigo do grupo de depuracao de erros (=105)
/********************************************/

/* implementacao da classe buffer de ordenacao
*/
TROB::TROB()
{
  try {
	 ptrROB = new TData[(NEntries = ROB_NENTRIES)];
	 NItens = 0;
  }
  catch(xmsg& _err) {
	 errmsg(ROB_ERRGROUP, 55, _err);
  }
}

TROB::~TROB()
{
  delete[] ptrROB;
}

void
TROB::AddItem(TData _item)
{
  TData *p;
  if( !IsFull() ) {
	 p = &ptrROB[NItens];
	 p->SetItem(_item);
	 p->SetNotReady();
	 NItens += 1;
  }
}

void
TROB::UpdateItem(TData _data)
{
  TData* p;

  for(int i = 0; i < NItens; i++)
	 if(ptrROB[i].GetIdentifier() == _data.GetIdentifier()) {
		(p = &ptrROB[i])->SetItem(_data);
		p->SetReady();
		return;
	 }
}

void
TROB::RemoveItem()
{
  for(int i = 1; i < NItens; i++)
	 ptrROB[i - 1] = ptrROB[i];
  NItens -= 1;
}

void
TROB::BranchFailure(int _id)
{
  for(int i = 0; i < NItens; i++)
	 if(ptrROB[i].GetIdentifier() == _id) {
		NItens = i + 1;
		break;
	 }
}

