
/*
/* DLX.h
/* por Luiz Marcio Faria Viana, 9/3/96
*/

#ifndef __DLX_H
#define __DLX_H

/* definicao dos identificadores de status de retorno das rotinas
*/

#define RTERR  0
#define RTNORM 1

/* definicao dos tipos de dados manipulados pelo simulador
*/

typedef unsigned char uchar;
typedef unsigned      uint;
typedef unsigned long ulong;

typedef char   BYTE_T;
typedef uchar  UBYTE_T;
typedef int    HWORD_T;
typedef uint   UHWORD_T;
typedef long   WORD_T;
typedef ulong  UWORD_T;
typedef float  FLOAT_T;
typedef double DOUBLE_T;

/* definicao do tamanho do buffer das janelas
*/
#define STREAM_BUFFSZ 400

/* definicao dos identificadores de estado da cpu
*/
#define RUNNING 1
#define STOPPED 0

/* definicao dos identificadores do tipo da instrucao
*/
#define I_TYPE 0
#define R_TYPE 1
#define J_TYPE 2

/* definicao dos identificadores das unidades de execucao
*/
#define UNIT_NON 0	// nenhuma unidade de execucao
#define UNIT_LSU 1
#define UNIT_ALU 2
#define UNIT_BPU 3
#define UNIT_FPU 4

/* definicao dos identificadores de previsao de desvios
*/
#define BP_NOTAKEN 0		// desvio nao tomado
#define BP_TAKEN   1		// desvio tomado

/* definicao das caracteristicas do simulador
*/
#define MEMSZ 8*1024		// tamanho da memoria principal

#define NUMGPR 32			// numero de registradores de proposito geral
#define NUMFPR 32			// numero de registradores de ponto flutuante

#define IQUEUE_NENTRIES 8		// total de entradas na fila de instrucoes
#define DISQ_NENTRIES	8		// total de entradas na fila de despacho
#define VU_NENTRIES     3     // total de unidades virtuais por unidade real
#define ROB_NENTRIES    8		// total de entradas no buffer de ordenacao

#define BTB_NSLOTS   16		// total de slots no branch target buffer
#define BTB_NENTRIES  8		// numero de entradas por slot no BTB

#define NUMINST 4			// numero maximo de instrucoes acessadas por ciclo
#define NUMDEC  2			// numero maximo de instrucoes decodificadas por ciclo

#define MAXBLEVEL 2		// numero maximo de desvios processados expeculativamente

#define NUM_ALU 2			// quantidade de cada unidades funcionais
#define NUM_FPU 1
#define NUM_BPU 1
#define NUM_LSU 1

#define NUM_UNIT (NUM_ALU+NUM_FPU+NUM_LSU+NUM_BPU)		// total de unidades funcionais

/* definicao dos tipos de algoritimos de despacho simulado
*/
#define ESCALAR 0
#define PENTIUM 1
#define POWERPC 2
#define ALPHA   3

/* definicao dos identificadores do tipo de uso dos registradores
*/
#define R_NONE     -1
#define R_SRC      -2
#define R_DST      -3

/* definicao dos grupos identificadores das unidades virtuais
*/
#define VU_NDEF    0
#define VU_ALU   100
#define VU_BPU   200
#define VU_FPU   300
#define VU_LSU   400

/* definicao das constantes que expressao a relacao de dependencia
*/
#define D_TRUE  0x0001
#define D_FALSE 0x0002
#define D_OUT   0x0004

/* definicao dos identificadores de formatacao das instrucoes
*/
#define FORM_A 0
#define FORM_B 1
#define FORM_C 2
#define FORM_D 3
#define FORM_E 4
#define FORM_F 5
#define FORM_G 6
#define FORM_H 7
#define FORM_I 8
#define FORM_J 9

/* definicao do numero maximo de instrucoes por tipo nas tabelas
*/
#define MAX_ITYPE 33
#define MAX_JTYPE  7
#define MAX_RTYPE 48

/* definicao dos identificadores dos comandos
*/
enum {			// Load and Store Unit
  _LB = 0x04,
  _LBU,
  _SB,
  _LH,
  _LHU,
  _SH,
  _LW,
  _SW,
  _LF,
  _LD,
  _SF,
  _SD,
  _MOVI2S,
  _MOVS2I,
  _MOVF,
  _MOVD,
  _MOVFP2I,
  _MOVI2FP
};

enum {			// Arithmetic and Logic Unit
  _ADDI = 0x10,
  _SUBI,
  _MULTI,
  _DIVI,
  _ANDI,
  _ORI,
  _XORI,
  _LHI,
  _SLLI,
  _SRLI,
  _SRAI,
  _SLTI,
  _SGTI,
  _SLEI,
  _SGEI,
  _SEQI,
  _SNEI,
  _ADD = 0x40,
  _SUB,
  _MULT,
  _DIV,
  _AND,
  _OR,
  _XOR,
  _SLL,
  _SRL,
  _SRA,
  _SLT,
  _SGT,
  _SLE,
  _SGE,
  _SEQ,
  _SNE
};

enum {			// Branch Processor Unit
  _BEQZ = 0,
  _BNEZ,
  _JR,
  _JALR,
  _BFPT = 0x38,
  _BFPF,
  _J,
  _JAL,
  _TRAP,
  _RFE,
  _HALT
};

enum {			// Floating Point Unit
  _ADDD = 0,
  _ADDF,
  _SUBD,
  _SUBF,
  _MULTD,
  _MULTF,
  _DIVD,
  _DIVF,
  _CVTF2D,
  _CVTF2I,
  _CVTD2F,
  _CVTD2I,
  _CVTI2F,
  _CVTI2D,
  _SLTD,
  _SGTD,
  _SLED,
  _SGED,
  _SEQD,
  _SNED,
  _SLTF,
  _SGTF,
  _SLEF,
  _SGEF,
  _SEQF,
  _SNEF
};

#endif  /* __DLX_H */

