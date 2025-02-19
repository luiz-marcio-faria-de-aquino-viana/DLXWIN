
/*
/* Decode.h
/* por Luiz Marcio F A Viana, 12/9/96
*/

#ifndef __DECODE_H
#define __DECODE_H

#include<except.h>
#pragma hdrstop
#include"h\dlx.h"
#include"h\error.h"

/* declaracao do tipo de dado tabela de instrucoes
*/
struct ITABLE {
  int   InstrCode;
  char* InstrForm;
  int   InstrFormType;
  int   ExecUnit;
};

/* declaracao da classe decodificacao de instrucoes
*/
class Decode {
public:
  WORD_T IR;

  int Typ;

  int UF;
  int Cmd;

  int Op;
  int Func;
  int Rs1, Rs2;
  int Rd;
  int Imm;
  WORD_T Offset;

  Decode() { }
  Decode(WORD_T _ir);

  int IsBranch();

  void SetItem(WORD_T _ir);
  char* StrUndecode(char* s);
protected:
  char* StrFormat(char* s, char* instrForm, int instrFormTyp);
  virtual void SetupItem();
};

#endif  /* __DECODE_H */

