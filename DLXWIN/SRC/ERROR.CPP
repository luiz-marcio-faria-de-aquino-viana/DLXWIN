
/*
/* ERROR.cpp
/* por Luiz Marcio F A Viana, 10/24/96
*/

#include"h\error.h"

/* implementacao da rotina de tratamento de erros
*/
void errmsg(int _grp, int _lin, xmsg& _err)
{
  char s[256];

  sprintf(s, "(G%03d, L%04d): %s", _grp, _lin, _err.why().c_str());
  ::MessageBox(0, s, "E R R O R", MB_OK);
  exit(1);
}

void errmsg(int _grp, int _lin, char* _err)
{
  char s[256];

  sprintf(s, "(G%03d, L%04d): %s", _grp, _lin, _err);
  ::MessageBox(0, s, "E R R O R", MB_OK);
  exit(1);
}

