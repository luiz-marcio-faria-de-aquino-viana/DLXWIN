
/*
/* TVU.cpp
/* por Luiz Marcio F A Viana, 11/16/96
*/

#include"h\tvu.h"

/********************************************
/* codigo do grupo de depuracao de erros (=104)
/********************************************/

/* implementacao da classe grupo de unidades virtuais
*/
TVUGR::TVUGR(int id)
{
  try {
	 iptrVU = new TVU*[(NEntries = VU_NENTRIES)];
	 for(int i = 0; i < NEntries; i++)
		iptrVU[i] = new TVU(id++);
	 NItens = 0;
  }
  catch(xmsg& _err) {
	 errmsg(VU_ERRGROUP, 37, _err);
  }
}

TVUGR::~TVUGR()
{
  for(int i = 0; i < NEntries; i++)
	 delete iptrVU[i];
  delete[] iptrVU;
}

int
TVUGR::AddItem(TData _item)
{
  if( IsFull() ) return -1;
  _item.SetIdentifier(iptrVU[NItens]->GetIdentifier());
  iptrVU[NItens]->SetItem(_item);
  iptrVU[NItens]->SetNotInExecution();
  return iptrVU[NItens++]->GetIdentifier();
}

void
TVUGR::UpdateItem(TData _item)
{
  TData ci;

  for(int i = 0; i < NItens; i++)
  {

	 iptrVU[i]->GetItem(ci);

	 //
	 // atualiza se espera registrador de controle
	 //
	 if((ci.Biar == R_SRC) && (_item.Biar == R_DST))
		if(ci.Qiar == _item.GetIdentifier())
		{
		  ci.Viar = _item.Viar;
		  ci.Qiar = VU_NDEF;
		}

	 if((ci.Bfp == R_SRC) && (_item.Bfp == R_DST))
		if(ci.Qfp == _item.GetIdentifier())
		{
		  ci.Vfp = _item.Vfp;
		  ci.Qfp = VU_NDEF;
		}

	 //
	 // atualiza se espera registrador de proposito geral
	 //
	 if((ci.R1 != R_NONE) && (_item.Rd != R_NONE))
		if(ci.Qr1 == _item.GetIdentifier())
		{
		  ci.Vr1 = _item.Vrd;
		  ci.Qr1 = VU_NDEF;
		}

	 if((ci.R2 != R_NONE) && (_item.Rd != R_NONE))
		if(ci.Qr2 == _item.GetIdentifier())
		{
		  ci.Vr2 = _item.Vrd;
		  ci.Qr2 = VU_NDEF;
		}

	 //
	 // atualiza se espera registrador de ponto flutuante
	 //
	 if((ci.F1 != R_NONE) && (_item.Fd != R_NONE))
		if(ci.Qf1 == _item.GetIdentifier())
		{
		  ci.Vf1 = _item.Vfd;
		  ci.Qf1 = VU_NDEF;
		}

	 if((ci.F2 != R_NONE) && (_item.Fd != R_NONE))
		if(ci.Qf2 == _item.GetIdentifier())
		{
		  ci.Vf2 = _item.Vfd;
		  ci.Qf2 = VU_NDEF;
		}

	 if( (ci.Qr1  == VU_NDEF) && (ci.Qr2 == VU_NDEF) &&
		  (ci.Qf1  == VU_NDEF) && (ci.Qf2 == VU_NDEF) &&
		  (ci.Qiar == VU_NDEF) && (ci.Qfp == VU_NDEF) )
		ci.SetReady();

	 iptrVU[i]->SetItem(ci);
  }
}

int
TVUGR::GetFirstItem(TData& _item)
{
  if( IsEmpty() ) return -1;
  if( iptrVU[0]->IsReady() && !iptrVU[0]->IsInExecution() ) {
	 iptrVU[0]->GetItem(_item);
	 iptrVU[0]->SetInExecution();
	 return iptrVU[0]->GetIdentifier();
  }
  return 0;
}

int
TVUGR::GetReadyItem(TData& _item)
{
  for(int i = 0; i < NItens; i++) {
	 if( iptrVU[i]->IsReady() && !iptrVU[i]->IsInExecution() ) {
		iptrVU[i]->GetItem(_item);
		iptrVU[i]->SetInExecution();
		return iptrVU[i]->GetIdentifier();
	 }
  }
  return 0;
}

void
TVUGR::RemoveItem(int _id)
{
  TVU* ip;
  int i, j;

  for(i = 0; i < NItens; i++)
	 if(iptrVU[i]->GetIdentifier() == _id) {
		ip = iptrVU[i];
		for(j = i + 1; j < NItens; j++)
		  iptrVU[j - 1] = iptrVU[j];
		iptrVU[--NItens] = ip;
		break;
	 }
}

void
TVUGR::BranchSuccess(int _bl)
{
  TData ci;
  for(int i = 0; i < NItens; i++) {
	 iptrVU[i]->GetItem(ci);
	 if(ci.GetBranchLevel() > _bl)
		ci.SetBranchLevel(ci.GetBranchLevel() - 1);
  }
}

void
TVUGR::BranchFailure(int _bl)
{
  TData item1;
  TVU *ip1;

  int i, j;

  for(i = 0; i < NItens; )
  {
	 (ip1 = iptrVU[i])->GetItem(item1);
	 if(item1.GetBranchLevel() > _bl)
	 {
		for(j = i + 1; j < NItens; j++)
		  iptrVU[j - 1] = iptrVU[j];
		iptrVU[--NItens] = ip1;
	 }
	 else
	 {
		i++;
	 }
  }

}

