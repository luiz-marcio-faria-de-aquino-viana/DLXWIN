
/*
/* TRegs.h
/* por Luiz Marcio F A Viana, 11/17/96
*/

#ifndef __TREGS_H
#define __TREGS_H

#include<except.h>
#pragma hdrstop
#include"h\dlx.h"
#include"h\error.h"
#include"h\latch.h"

/* declaracao da classe registradores internos da cpu
*/
class TRegs {
private:

  int BB;				// bit indicador de registrador em ocupado

  int ID;				// indicador da unidade virtual que usa o registrador

public:

  LATCH_T R1, R;		// registrador futuro e registrador real

  TRegs()
	 { SetFree(); }

  int IsBusy()
	 { return BB; }

  void SetBusy()
	 { BB = 1; }
  void SetFree()
	 { BB = 0; }

  int GetIdentifier()
	 { return ID; }
  void SetIdentifier(int id)
	 { ID = id; }

  void UpdateValue();
  void RestoreValue();

  TRegs& operator=(TRegs& _reg);
};

#endif  /* __TREGS_H */

