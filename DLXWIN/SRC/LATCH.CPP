
/*
/* LATCH.cpp
/* por Luiz Marcio F A Viana, 11/17/96
*/

#include"h\latch.h"

/*******************************************
/* codgo do grupo de depuracao de error (=200)
/*******************************************/

/* implementacao da classe latches
*/
LATCH_T&
LATCH_T::operator=(WORD_T _val)
{
  x.W = _val;
  return *this;
};

LATCH_T&
LATCH_T::operator=(FLOAT_T _val)
{
  x.F = _val;
  return *this;
};

LATCH_T&
LATCH_T::operator=(DOUBLE_T _val)
{
  x.D = _val;
  return *this;
};

LATCH_T&
LATCH_T::operator=(LATCH_T _val)
{
  x.D = _val.x.D;
  return *this;
};

