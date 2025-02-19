
/*
/* TGpr.cpp
/* por Luiz Marcio F A Viana, 11/17/96
*/

#include"h\tgpr.h"

/********************************************
/* codigo do grupo de depuracao de erros (=106)
/********************************************/

/* implementacao da classe banco de registradores de proposito gerais
*/
TGpr::TGpr()
{
  try {
	 ptrGPR = new TRegs[(NRegs = NUMGPR)];
  }
  catch(xmsg& err) {
	 errmsg(GPR_ERRGROUP, 17, err);
  }
}

TGpr::~TGpr()
{
  delete[] ptrGPR;
}

void
TGpr::Flush()
{
  for(int i = 0; i < NRegs; i++)
	 ptrGPR[i].RestoreValue();
}

