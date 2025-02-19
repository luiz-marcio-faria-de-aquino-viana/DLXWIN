
/*
/* TGpr.h
/* por Luiz Marcio F A Viana, 11/17/96
*/

#ifndef __TGPR_H
#define __TGPR_H

#include<except.h>
#pragma hdrstop
#include"h\dlx.h"
#include"h\error.h"
#include"h\latch.h"
#include"h\tregs.h"

/* declaracao da classe banco de registradores de proposito gerais
*/
class TGpr {
private:
  TRegs* ptrGPR;
  int NRegs;
public:
  TGpr();
  ~TGpr();

  TRegs* GetRegister(int _reg)
	 { return( (_reg < NRegs) ? & ptrGPR[_reg] : 0); }

  void Flush();
};

#endif  /* __TGPR_H */

