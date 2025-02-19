
/*
/* TRegs.cpp
/* por Luiz Marcio F A Viana, 11/17/96
*/

#include"h\tregs.h"

/* implementacao da classe registradores internos da cpu
*/
void
TRegs::UpdateValue()
{
  R = R1;
  SetFree();
}

void
TRegs::RestoreValue()
{
  R1 = R;
  SetFree();
}

TRegs&
TRegs::operator=(TRegs& _reg)
{
  BB = _reg.BB;

  ID = _reg.ID;

  R1 = _reg.R1;
  R  = _reg.R;

  return *this;
}

