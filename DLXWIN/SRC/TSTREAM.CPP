
/*
/* TStream.h
/* por Luiz Marcio F A Viana, 5/30/97
*/

#include"h\tstream.h"

/********************************************
/* codigo do grupo de depuracao de erros (=110)
/********************************************/

TStreamBuff::TStreamBuff(int buffsz)
{
  try {
	 Buff = new char* [(BuffSz = buffsz)];
	 for(int i = 0; i < BuffSz; i++)
		Buff[i] = new char[81];
	 NItens = 0;
  }
  catch(xmsg& _err) {
	 errmsg(STREAM_ERRGROUP, 14, _err);
  }
}

TStreamBuff::~TStreamBuff()
{
  for(int i = 0; i < BuffSz; i++)
	 delete[] Buff[i];
  delete[] Buff;
}

void
TStreamBuff::AddStrToBuff(char* s)
{
  char *p;
  int i;
  if(NItens < BuffSz)
  {
	 strncpy(Buff[NItens], s, 80);
	 Buff[NItens++][80] = '\0';
  }
  else
  {
	 p = Buff[0];
	 for(i = 0; i < NItens - 1; i++)
		Buff[i] = Buff[i + 1];
	 Buff[i] = p;
	 strncpy(Buff[i], s, 80);
	 Buff[i][80] = '\0';
  }
}

