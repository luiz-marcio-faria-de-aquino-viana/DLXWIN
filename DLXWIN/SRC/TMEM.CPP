
/*
/* TMem.cpp
/* por Luiz Marcio F A Viana, 11/23/96
*/

#include"h\tmem.h"

/********************************************
/* codigo do grupo de depuracao de erros (=100)
/********************************************/

/* implementacao da classe memoria principal
*/
TMem::TMem()
{
  try {
	 M = new UBYTE_T[(MemSz = MEMSZ)];
  }
  catch(xmsg& _err) {
	 errmsg(MEM_ERRGROUP, 16, _err);
  }
}

TMem::~TMem()
{
  delete[] M;
}

void
TMem::RD(WORD_T _addr, void* _ptr, int _nbytes)
{
  try {
	 if((_addr + _nbytes) > MemSz) throw ERR_OUTOFMEM;
	 memcpy(_ptr, &M[(int) _addr], _nbytes);
  }
  catch(char* _err) {
	 errmsg(MEM_ERRGROUP, 34, _err);
  }
}

void
TMem::WR(WORD_T _addr, void* _ptr, int _nbytes)
{
  try {
	 if((_addr + _nbytes) >= MemSz) throw ERR_OUTOFMEM;
	 memcpy(&M[(int) _addr], _ptr, _nbytes);
  }
  catch(char* _err) {
	 errmsg(MEM_ERRGROUP, 46, _err);
  }
}

void
TMem::LoadFile(const char* fname)
{
  FILE* fp;
  try {
    ClearMem();
	 if((fp = fopen(fname, "rb")) == 0) throw ERR_CANTOPENFILE;
	 fread(M, sizeof(BYTE_T), MemSz, fp);
	 fclose(fp);
  }
  catch(char* _err) {
	 errmsg(MEM_ERRGROUP, 57, _err);
  }
}

void
TMem::GetInstr(WORD_T _addr, char* _ibuf)
{
  Decode dec;
  WORD_T ir;

  RD(_addr, &ir, sizeof(WORD_T));
  sprintf(_ibuf, "%08lX  ", ir);

  dec.SetItem(ir);
  dec.StrUndecode(&_ibuf[10]);
}

void
TMem::ClearMem()
{
  memset(M, 0, MemSz);
}

