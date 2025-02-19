
/*
/* TStream.h
/* por Luiz Marcio F A Viana, 5/30/97
*/

#ifndef __TSTREAM_H
#define __TSTREAM_H

#pragma hdrstop
#include"h\error.h"

class TStreamBuff {
public:
  TStreamBuff(int buffsz);
  ~TStreamBuff();

  int GetNumItens()
	 { return NItens; }

  char* GetBuffItem(int idx)
	 { return (idx < NItens) ? Buff[idx] : 0; }

  void AddStrToBuff(char* s);

  void FlushBuff()
	 { NItens = 0; }
private:
  char** Buff;
  int BuffSz;
  int NItens;
};

#endif  /* __TSTREAM_H */
