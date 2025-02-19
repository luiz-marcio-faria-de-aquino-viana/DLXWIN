
/*
/* TBTB.cpp
/* por Luiz Marcio F A Viana, 10/25/96
*/

#include"h\tbtb.h"

/********************************************
/* codigo do grupo de depuracao de erros (=103)
/********************************************/

/* implementacao da classe item da tabela de destino de desvios
*/
void
TBTBItem::SetPrediction(int _pred)
{
  if(_pred == BP_TAKEN)
	 SetBranchTaken();
  else if(_pred == BP_NOTAKEN)
	 SetBranchNotTaken();
}

void
TBTBItem::SetItem(WORD_T _tag, WORD_T _dst)
{
  SetupItem();
  Tag = _tag;
  Dst = _dst;
  Val = 1;
}

void
TBTBItem::SetupItem()
{
  Val = 0;
  Cnt = 0;
  B1 = B2 = 0;
}

/* implementacao da classe da tabela de destino de desvios
*/
TBTB::TBTB()
{
  try {
	 ptrBTB = new TBTBItem*[(NSlots = BTB_NSLOTS)];
	 for(int i = 0; i < NSlots; i++)
		ptrBTB[i] = new TBTBItem[(NEntries = BTB_NENTRIES)];
  }
  catch(xmsg& err) {
	 errmsg(BTB_ERRGROUP, 42, err);
  }
}

TBTB::~TBTB()
{
  for(int i = 0; i < NSlots; i++)
	 delete[] ptrBTB[i];
  delete[] ptrBTB;
}

int
TBTB::ExistEntry(WORD_T _addr, WORD_T& _dst, int& _pred)
{
  WORD_T tag = CalcTag(_addr);
  int slot = CalcSlot(_addr);

  cip = ptrBTB[slot];
  for(int i = 0; i < NEntries; i++)
  {
	 if( !cip->IsValid() ) break;
	 if(cip->Tag == tag) {
		_pred = cip->BranchPrediction();
		_dst = cip->Dst;
		return 1;
	 }
	 cip++;
  }
  cip = 0;
  return 0;
}

void
TBTB::AddEntry(WORD_T _addr, WORD_T _dst, int _pred)
{
  WORD_T tag = CalcTag(_addr);
  int slot = CalcSlot(_addr);

  TBTBItem *ip;
  int pred = 0;
  int i, n = 0;

  ip = ptrBTB[slot];
  if(ExistEntry(_addr, _dst, pred))
  {
	 for(i = 0; i < NEntries; i++) {
		if( !ip->IsValid() ) break;
		if(ip->Cnt < cip->Cnt) (ip->Cnt)++;
	 }
	 cip->SetPrediction(_pred);
	 cip->Dst = _dst;
	 cip->Cnt = 0;
  }
  else
  {
	 for(i = 0; i < NEntries; i++) {
		if( !ip->IsValid() ) {
		  ip->SetItem(tag, _dst);
		  ip->SetPrediction(_pred);
		  return;
		}
		if(ip->Cnt >= n) {
		  n = ip->Cnt;
		  cip = ip;
		}
		(ip->Cnt)++;
		ip++;
	 }
	 cip->SetItem(tag, _dst);
	 cip->SetPrediction(_pred);
  }
}

void
TBTB::Flush()
{
  for(int i = 0; i < NSlots; i++)
	 for(int j = 0; j < NEntries; j++)
		ptrBTB[i][j].SetInvalidBit();
}

