
/*
/* TDISQ.cpp
/* por Luiz Marcio F A Viana, 10/24/96
*/

#include"h\tdisq.h"

/********************************************
/* codigo do grupo de depuracao de erros (=102)
/********************************************/

/* implementacao da classe fila de despacho
*/
TDisq::TDisq()
{
  try {
	 ptrDisq = new TData[(NEntries = DISQ_NENTRIES)];
	 NItens = 0;
	 cbl = 0;
  }
  catch(xmsg& err) {
	 errmsg(DISQ_ERRGROUP, 334, err);
  }
}

TDisq::~TDisq()
{
  delete[] ptrDisq;
}

void
TDisq::RemoveItem()
{
  if( IsEmpty() ) return;
  for(int i = 1; i < NItens; i++)
	 ptrDisq[i - 1] = ptrDisq[i];
  NItens -= 1;
}

int
TDisq::GetFirstBranchItem(TData& _item)
{
  for(int i = 0; i < NItens; i++)
	 if( ptrDisq[i].IsBranch() ) {
		_item = ptrDisq[i];
		return i;
	 }
  return -1;
}

void
TDisq::RemoveFirstBranchItem()
{
  int i, j;
  for(i = 0; i < NItens; i++)
	 if( ptrDisq[i].IsBranch() ) {
		for(j = i + 1; j < NItens; j++)
		  ptrDisq[j - 1] = ptrDisq[j];
		NItens -= 1;
	 }
}

void
TDisq::BranchSuccess(int _val)
{
  for(int i = 0; i < NItens; i++)
	 if(ptrDisq[i].GetBranchLevel() >= _val)
		ptrDisq[i].SetBranchLevel(ptrDisq[i].GetBranchLevel() - 1);
  cbl -= 1;
}

void
TDisq::BranchFailure(int _val)
{
  for(int i = 0; i < NItens; i++)
	 if(ptrDisq[i].GetBranchLevel() > _val) {
		NItens = i;
		break;
	 }
  cbl = _val;
}

void
TDisq::Flush()
{
  NItens = 0;
  cbl = 0;
}

