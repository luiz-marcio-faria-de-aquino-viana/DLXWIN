
/*
/* ERROR.h
/* por Luiz Marcio F A Viana, 10/24/96
*/

#ifndef __ERROR_H
#define __ERROR_H

#include<except.h>
#include<stdio.h>
#include<stdlib.h>
#include<cstring.h>
#include<windows.h>
#pragma hdrstop

/* definicao da tabela de grupos de erros
*/
#define MEM_ERRGROUP       100
#define IQUEUE_ERRGROUP    101
#define DISQ_ERRGROUP      102
#define BTB_ERRGROUP       103
#define VU_ERRGROUP        104
#define ROB_ERRGROUP       105
#define GPR_ERRGROUP       106
#define FPR_ERRGROUP       107
#define CPU_ERRGROUP       108
#define DATA_ERRGROUP      109
#define STREAM_ERRGROUP    110

/* definicao da tabela de mensagens de erros
*/
#define ERR_ALLOCMEM			"Can't allocate memory"
#define ERR_OUTOFMEM			"Out of memory"
#define ERR_CANTOPENFILE   "Can't open file"
#define ERR_CANTREADFILE	"Can't read file"
#define ERR_ACCESSSIZE		"Memory access size failure"
#define ERR_DIV0				"Division by zero"
#define ERR_OVERFLOW			"Overflow"
#define ERR_UNEXISTINSTR	"Instruction unexist"
#define ERR_IQFULL         "Instruction queue is full"
#define ERR_IQEMPTY			"Instruction queue is empty"

/* declaracao da rotina de tratamento de erros
*/
void errmsg(int _grp, int _lin, xmsg& _err);

void errmsg(int _grp, int _lin, char* _err);

#endif  /* __ERROR_H */

