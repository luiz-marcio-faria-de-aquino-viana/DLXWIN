
/*
/* TFpr.cpp
/* por Luiz Marcio F A Viana, 11/17/96
*/

#include"h\tfpr.h"

/********************************************
/* codigo do grupo de depuracao de erros (=107)
/********************************************/

/* implementacao da classe banco de registradores de ponto flutuante
*/
TFpr::TFpr()
{
  try {
	 ptrFPR = new TRegs[(NRegs = NUMFPR)];
  }
  catch(xmsg& err) {
	 errmsg(FPR_ERRGROUP, 68, err);
  }
}

TFpr::~TFpr()
{
  delete[] ptrFPR;
}

void
TFpr::Flush()
{
  for(int i = 0; i < NRegs; i++)
	 ptrFPR[i].RestoreValue();
}

