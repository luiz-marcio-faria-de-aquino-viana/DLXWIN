
/*
/* CP.cpp
/* por Luiz Marcio Faria Viana, 9/25/96
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STRLN 256

#define NUMINSTR 91

#define MAXGPR 32
#define MAXFPR 32

#define SRC_FILE ".asm"
#define DST_FILE ".bin"
#define MAP_FILE ".map"

#define I_TYPE 0
#define J_TYPE 1
#define R_TYPE 2
#define D_TYPE 3

#define RQ_RS1     'A'
#define RQ_RS2     'B'
#define RQ_RD      'C'
#define RQ_FS1     'D'
#define RQ_FS2     'E'
#define RQ_FD      'F'
#define RQ_IMM     'G'
#define RQ_OFFSET  'H'
#define RQ_HEX     'I'
#define RQ_INT     'J'
#define RQ_FLOAT   'K'

typedef unsigned char uchar;
typedef unsigned      uint;
typedef unsigned long ulong;

typedef long  WORD_T;
typedef float FLOAT_T;

typedef struct ElemTabInstr {
  int TipoInstr;
  char* IdentInstr;
  char*  EstrutInstr;
  ulong CodigoBase;
} ElemTabInstr_t;

ElemTabInstr_t TabInstr[] = {
/* I-TYPE (BPU) */
  {I_TYPE, "BEQZ", "AG", 0x00000000L},
  {I_TYPE, "BNEZ", "AG", 0x04000000L},
  {I_TYPE, "JR",   "A",  0x08000000L},
  {I_TYPE, "JALR", "A",  0x0C000000L},
/* I-TYPE (LSU) */
  {I_TYPE, "LB",   "CGA", 0x10000000L},
  {I_TYPE, "LBU",  "CGA", 0x14000000L},
  {I_TYPE, "SB",   "GAC", 0x18000000L},
  {I_TYPE, "LH",   "CGA", 0x1C000000L},
  {I_TYPE, "LHU",  "CGA", 0x20000000L},
  {I_TYPE, "SH",   "GAC", 0x24000000L},
  {I_TYPE, "LW",   "CGA", 0x28000000L},
  {I_TYPE, "SW",   "GAC", 0x2C000000L},
  {I_TYPE, "LF",   "FGA", 0x30000000L},
  {I_TYPE, "LD",   "FGA", 0x34000000L},
  {I_TYPE, "SF",   "GAF", 0x38000000L},
  {I_TYPE, "SD",   "GAF", 0x3C000000L},
/* I-TYPE (ALU) */
  {I_TYPE, "ADDI",  "CAG", 0x40000000L},
  {I_TYPE, "SUBI",  "CAG", 0x44000000L},
  {I_TYPE, "MULTI", "CAG", 0x48000000L},
  {I_TYPE, "DIVI",  "CAG", 0x4C000000L},
  {I_TYPE, "ANDI",  "CAG", 0x50000000L},
  {I_TYPE, "ORI",   "CAG", 0x54000000L},
  {I_TYPE, "XORI",  "CAG", 0x58000000L},
  {I_TYPE, "LHI",   "CAG", 0x5C000000L},
  {I_TYPE, "SLLI",  "CAG", 0x60000000L},
  {I_TYPE, "SRLI",  "CAG", 0x64000000L},
  {I_TYPE, "SRAI",  "CAG", 0x68000000L},
  {I_TYPE, "SLTI",  "CAG", 0x6C000000L},
  {I_TYPE, "SGTI",  "CAG", 0x70000000L},
  {I_TYPE, "SLEI",  "CAG", 0x74000000L},
  {I_TYPE, "SGEI",  "CAG", 0x78000000L},
  {I_TYPE, "SEQI",  "CAG", 0x7C000000L},
  {I_TYPE, "SNEI",  "CAG", 0x80000000L},
/* J-TYPE (BPU) */
  {J_TYPE, "BFPT",  "H", 0xE0000000L},
  {J_TYPE, "BFPF",  "H", 0xE4000000L},
  {J_TYPE, "J",     "H", 0xE8000000L},
  {J_TYPE, "JAL",   "H", 0xEC000000L},
  {J_TYPE, "TRAP",  "H", 0xF0000000L},
  {J_TYPE, "RFE",   "",  0xF4000000L},
  {J_TYPE, "HALT",  "",  0xF8000000L},
/* R-TYPE (LSU) */
  {R_TYPE, "MOVI2S",  "A",  0xFC000010L},
  {R_TYPE, "MOVS2I",  "A",  0xFC000011L},
  {R_TYPE, "MOVF",    "FD", 0xFC000012L},
  {R_TYPE, "MOVD",    "FD", 0xFC000013L},
  {R_TYPE, "MOVFP2I", "CD", 0xFC000014L},
  {R_TYPE, "MOVI2FP", "FA", 0xFC000015L},
/* R-TYPE (ALU) */
  {R_TYPE, "ADD",  "CAB", 0xFC000240L},
  {R_TYPE, "SUB",  "CAB", 0xFC000241L},
  {R_TYPE, "MULT", "CAB", 0xFC000242L},
  {R_TYPE, "DIV",  "CAB", 0xFC000243L},
  {R_TYPE, "AND",  "CAB", 0xFC000244L},
  {R_TYPE, "OR",   "CAB", 0xFC000245L},
  {R_TYPE, "XOR",  "CAB", 0xFC000246L},
  {R_TYPE, "SLL",  "CAB", 0xFC000247L},
  {R_TYPE, "SRL",  "CAB", 0xFC000248L},
  {R_TYPE, "SRA",  "CAB", 0xFC000249L},
  {R_TYPE, "SLT",  "CAB", 0xFC00024AL},
  {R_TYPE, "SGT",  "CAB", 0xFC00024BL},
  {R_TYPE, "SLE",  "CAB", 0xFC00024CL},
  {R_TYPE, "SGE",  "CAB", 0xFC00024DL},
  {R_TYPE, "SEQ",  "CAB", 0xFC00024EL},
  {R_TYPE, "SNE",  "CAB", 0xFC00024FL},
/* R-TYPE (FPU) */
  {R_TYPE, "ADDD",   "FDE", 0xFC000400L},
  {R_TYPE, "ADDF",   "FDE", 0xFC000401L},
  {R_TYPE, "SUBD",   "FDE", 0xFC000402L},
  {R_TYPE, "SUBF",   "FDE", 0xFC000403L},
  {R_TYPE, "MULTD",  "FDE", 0xFC000404L},
  {R_TYPE, "MULTF",  "FDE", 0xFC000405L},
  {R_TYPE, "DIVD",   "FDE", 0xFC000406L},
  {R_TYPE, "DIVF",   "FDE", 0xFC000407L},
  {R_TYPE, "CVTF2D", "DF",  0xFC000408L},
  {R_TYPE, "CVTF2I", "DF",  0xFC000409L},
  {R_TYPE, "CVTD2F", "DF",  0xFC00040AL},
  {R_TYPE, "CVTD2I", "DF",  0xFC00040BL},
  {R_TYPE, "CVTI2F", "DF",  0xFC00040CL},
  {R_TYPE, "CVTI2D", "DF",  0xFC00040DL},
  {R_TYPE, "SLTD",   "DF",  0xFC00040EL},
  {R_TYPE, "SGTD",   "DF",  0xFC00040FL},
  {R_TYPE, "SLED",   "DF",  0xFC000410L},
  {R_TYPE, "SGED",   "DF",  0xFC000411L},
  {R_TYPE, "SEQD",   "DF",  0xFC000412L},
  {R_TYPE, "SNED",   "DF",  0xFC000413L},
  {R_TYPE, "SLTF",   "DF",  0xFC000414L},
  {R_TYPE, "SGTF",   "DF",  0xFC000415L},
  {R_TYPE, "SLEF",   "DF",  0xFC000416L},
  {R_TYPE, "SGEF",   "DF",  0xFC000417L},
  {R_TYPE, "SEQF",   "DF",  0xFC000418L},
  {R_TYPE, "SNEF",   "DF",  0xFC000419L},
/* DATA MANIPULATION */
  {D_TYPE, "DV",     "I",             0},
  {D_TYPE, "DW",     "J",             0},
  {D_TYPE, "DF",     "K",             0}
};

long expt(int a, int b);

class CompLinha {
  char* InstrLn;
  char* Token;
  int Ptr;
  ElemTabInstr_t* Elem;
  void SetInstrLn(char* instr);
  void LerToken();
  int ProcPalavraChave();
  int ProcGprIdent(ulong& r);
  int ProcFprIdent(ulong& r);
  int ProcValor(ulong& val);
  int ProcInt(WORD_T& val);
  int ProcReal(FLOAT_T& val);
public:
  CompLinha();
  ~CompLinha();
  int Processa(ulong& codigo, char* instr);
};

CompLinha::CompLinha()
{
  Token = new char[STRLN];
}

CompLinha::~CompLinha()
{
  delete[] Token;
}

void
CompLinha::SetInstrLn(char* instr)
{
  InstrLn = instr;
  Ptr = 0;
}

void
CompLinha::LerToken()
{
  char* p1;
  char* p2;

  p1 = & InstrLn[Ptr];

  p2 = Token;
  *p2 = '\0';

  while(*p1 != '\0') {
	 if( ((*p1 >= '0') && (*p1 <= '9')) ||
	     ((*p1 >= 'A') && (*p1 <= 'Z')) ||
	      (*p1 == '.') )
		break;
	 Ptr += 1;
	 p1++;
  }

  while(*p1 != '\0') {
	 *p2 = *p1;
	 if( ((*p1 < '0') || (*p1 > '9')) &&
	     ((*p1 < 'A') || (*p1 > 'Z')) && (*p1 != '.') ) {
		*p2 = '\0';
		break;
	 }
	 Ptr += 1;
	 p1++;
    p2++;
  }
  *p2 = '\0';
}

int
CompLinha::ProcPalavraChave()
{
  int i;
  Elem = TabInstr;
  for(i = 0; i < NUMINSTR; i++) {
	 if(!strcmpi(Token, Elem->IdentInstr))
		return 0;
	 Elem++;
  }
  return -1;
}

int
CompLinha::ProcGprIdent(ulong& r)
{
  char ident[19];

  ident[0] = 'R';
  for(r = 0; r < (ulong) MAXGPR; r++) {
	 ltoa(r, & ident[1], 10);
	 if(!strcmpi(Token, ident))
		return 0;
  }
  return -1;
}

int
CompLinha::ProcFprIdent(ulong& r)
{
  char ident[19];

  ident[0] = 'F';
  for(r = 0; r < (ulong) MAXFPR; r++) {
	 ltoa(r, & ident[1], 10);
	 if(!strcmpi(Token, ident))
		return 0;
  }
  return -1;
}

int
CompLinha::ProcValor(ulong& val)
{
  int max = strlen(Token);
  int i;

  strupr(Token);

  val = 0;
  for(i = 0; i < max; i++) {
    if(((Token[i] < '0') || (Token[i] > '9')) &&
      ((Token[i] < 'A') || (Token[i] > 'F')) )
	return -1;
    if((Token[i] >= '0') && (Token[i] <= '9'))
	val += (Token[i] - '0') * expt(16, (max - 1) - i);
    if((Token[i] >= 'A') && (Token[i] <= 'F'))
	val += (Token[i] - 'A' + 10) * expt(16, (max - 1) - i);
  }
  return 0;
}

int
CompLinha::ProcInt(WORD_T& val)
{
  val = atol(Token);
  return 0;
}

int
CompLinha::ProcReal(FLOAT_T& val)
{
  val = atof(Token);
  return 0;
}

int
CompLinha::Processa(ulong& codigo, char* instr)
{
  char* cmd;
  int tip;

  ulong rd;
  ulong rs1, rs2;
  ulong imm;
  ulong offset;

  ulong    hval;
  WORD_T   wval;
  FLOAT_T  fval;

  SetInstrLn(instr);

  LerToken();
  if(ProcPalavraChave() != 0)
	 return -1;

  codigo = Elem->CodigoBase;
  tip = Elem->TipoInstr;

  cmd = Elem->EstrutInstr;
  while((*cmd) != '\0') {
    LerToken();
    switch(*cmd) {
      case RQ_RS1 :
	if(ProcGprIdent(rs1) != 0)
	  return -1;
	codigo |= (rs1 << 21);
	break;
      case RQ_FS1 :
	if(ProcFprIdent(rs1) != 0)
	  return -1;
	codigo |= (rs1 << 21);
	break;
      case RQ_RD :
	if(ProcGprIdent(rd) != 0)
	  return -1;
	codigo |= (tip == I_TYPE) ? (rd << 16) : (rd << 11);
	break;
      case RQ_FD :
	if(ProcFprIdent(rd) != 0)
	  return -1;
	codigo |= (tip == I_TYPE) ? (rd << 16) : (rd << 11);
	break;
      case RQ_RS2 :
	if(ProcGprIdent(rs2) != 0)
	  return -1;
	codigo |= (rs2 << 16);
	break;
      case RQ_FS2 :
	if(ProcFprIdent(rs2) != 0)
	  return -1;
	codigo |= (rs2 << 16);
	break;
      case RQ_IMM :
	if(ProcValor(imm) != 0)
	  return -1;
	codigo += (imm & 0xFFFF);
	break;
      case RQ_OFFSET :
	if(ProcValor(offset) != 0)
	  return -1;
	codigo += offset & 0x3FFFFFFL;
	break;
      case RQ_HEX :
	if(ProcValor(hval) != 0)
	  return - 1;
	codigo = hval;
	break;
      case RQ_INT :
	if(ProcInt(wval) != 0)
	  return - 1;
	codigo = wval;
	break;
      case RQ_FLOAT :
	if(ProcReal(fval) != 0)
	  return - 1;
	memcpy(&codigo, &fval, sizeof(WORD_T));
    }
    cmd++;
  }
  return 0;
}

class CompArqv {
  char* SrcName;
  char* DstName;
  char* MapName;
  CompLinha Ln;
public:
  CompArqv(char* fileName);
  ~CompArqv();
  int Processa();
};

CompArqv::CompArqv(char* fileName)
{
  SrcName = new char[strlen(fileName) + 5];
  strcat(strcpy(SrcName, fileName), SRC_FILE);
  DstName = new char[strlen(fileName) + 5];
  strcat(strcpy(DstName, fileName), DST_FILE);
  MapName = new char[strlen(fileName) + 5];
  strcat(strcpy(MapName, fileName), MAP_FILE);
}

CompArqv::~CompArqv()
{
  delete[] SrcName;
  delete[] DstName;
  delete[] MapName;
}

int
CompArqv::Processa()
{
  FILE* srcFile;
  FILE* dstFile;
  FILE* mapFile;

  char strbuff[STRLN];
  ulong codigo;
  ulong cnt = 0;

  int rst = 0;

  if((srcFile = fopen(SrcName, "r")) == NULL)
	 return -1;
  if((dstFile = fopen(DstName, "wb")) == NULL)
	 return -1;
  if((mapFile = fopen(MapName, "w")) == NULL)
	 return -1;

  while(fgets(strbuff, STRLN, srcFile) != NULL) {
	 strbuff[strlen(strbuff) - 1] = '\0';
	 if(Ln.Processa(codigo, strbuff) < 0) {
		fprintf(mapFile, "%08lX   *ERRO*   %s\n", cnt, strbuff);
		rst = -1;
	 }
	 else
		fprintf(mapFile, "%08lX  %08lX  %s\n", cnt, codigo, strbuff);
	 fwrite(& codigo, sizeof(ulong), 1, dstFile);
	 cnt += 4;
  }

  fclose(srcFile);
  fclose(dstFile);
  fclose(mapFile);

  return rst;
}

long expt(int a, int b)
{
  long r = 1;
  while(b > 0) {
	 r *= a;
	 b -= 1;
  }
  return r;
}

main(int argc, char* argv[])
{
  CompArqv* appl;
  if(argc < 2) return 1;
  appl = new CompArqv(argv[1]);
  return appl->Processa();
}

