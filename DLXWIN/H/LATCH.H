
/*
/* LATCH.h
/* por Luiz Marcio F A Viana, 11/17/96
*/

#ifndef __LATCH_H
#define __LATCH_H

#include"h\dlx.h"

/* declaracao da classe latches
*/
class LATCH_T {
public:
  union {
	 WORD_T   W;
	 FLOAT_T  F;
	 DOUBLE_T D;
  } x;

  LATCH_T()
    { x.D = 0; }

  LATCH_T& operator=(WORD_T _val);
  LATCH_T& operator=(FLOAT_T _val);
  LATCH_T& operator=(DOUBLE_T _val);

  LATCH_T& operator=(LATCH_T _val);
};

#endif  /* __LATCH_H */

