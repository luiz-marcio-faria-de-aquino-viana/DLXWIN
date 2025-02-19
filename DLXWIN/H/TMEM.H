
/*
/* TMem.h
/* por Luiz Marcio F A Viana, 11/23/96
*/

#ifndef __TMEM_H
#define __TMEM_H

#include<except.h>
#include<mem.h>
#pragma hdrstop
#include"h\dlx.h"
#include"h\error.h"
#include"h\decode.h"

/* declaracao da classe memoria principal
*/
class TMem {
private:
  UBYTE_T *M;
  int MemSz;
public:
  TMem();
  ~TMem();

  void RD(WORD_T _addr, void* _ptr, int _nbytes);
  void WR(WORD_T _addr, void* _ptr, int _nbytes);

  void LoadFile(const char* fname);

  void ClearMem();

  int GetMemSz()
    { return MemSz; }

  void GetInstr(WORD_T _addr, char* _ibuf);
};

#endif  /* __TMEM_H */
