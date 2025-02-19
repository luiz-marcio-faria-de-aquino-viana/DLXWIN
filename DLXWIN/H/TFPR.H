
/*
/* TFpr.h
/* por Luiz Marcio F A Viana, 11/17/96
*/

#ifndef __TFPR_H
#define __TFPR_H

#include<except.h>
#pragma hdrstop
#include"h\dlx.h"
#include"h\error.h"
#include"h\latch.h"
#include"h\tregs.h"

/* declaracao da classe banco de registradores de ponto flutuante
*/
class TFpr {
private:
  TRegs* ptrFPR;
  int NRegs;
public:
  TFpr();
  ~TFpr();

  TRegs* GetRegister(int _reg)
	 { return( (_reg < NRegs) ? & ptrFPR[_reg] : 0); }

  void Flush();
};

#endif  /* __TFPR_H */

