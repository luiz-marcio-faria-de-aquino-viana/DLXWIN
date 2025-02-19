
/*
/* TVU.h
/* por Luiz Marcio F A Viana, 11/16/96
*/

#ifndef __TVU_H
#define __TVU_H

#include<except.h>
#pragma hdrstop
#include"h\dlx.h"
#include"h\error.h"
#include"h\latch.h"
#include"h\tdata.h"

/* declaracao da classe unidade virtual
*/
class TVU {
private:

  int Id;		// identificador da unidade virtual

  int Ex;		// identificador de unidade virtual com
					// instrucao em execucao

  TData Data;

public:

  TVU(int id = VU_NDEF)
	 { Id = id; }

  int IsReady()
	 { return Data.IsReady(); }

  int IsInExecution()
	 { return Ex; }

  void SetNotInExecution()
	 { Ex = 0; }
  void SetInExecution()
	 { Ex = 1; }

  int GetIdentifier()
	 { return Id; }

  void SetItem(TData _data)
	 { Data = _data; }
  void GetItem(TData& _data)
	 { _data = Data; }
};

/* declaracao da classe grupo de unidades virtuais
*/
class TVUGR {
private:
  TVU** iptrVU;
  int NEntries;
  int NItens;
public:
  TVUGR(int id);
  ~TVUGR();

  int IsEmpty()
	 { return(NItens == 0); }
  int IsFull()
	 { return(NItens == NEntries); }

  int GetNumEntries()
	 { return NEntries; }

  int GetNumItens()
	 { return NItens; }

  void GetItemNum(int idx, TData& item)
	 { if(idx < NItens) iptrVU[idx]->GetItem(item); }

  int AddItem(TData item);
  void UpdateItem(TData _item);

  int GetFirstItem(TData& _item);		// obtem primeiro item se pronto
  int GetReadyItem(TData& _item);		// obtem o primeiro item pronto

  void RemoveItem(int _id);

  void BranchSuccess(int _bl);
  void BranchFailure(int _bl);

  void Flush()
	 { NItens = 0; }
};

#endif  /* __TVU_H */

