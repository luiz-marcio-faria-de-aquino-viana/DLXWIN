
/*
/* DLXWIN.h
/* por Luiz Marcio F A Viana, 21/4/97
*/

#ifndef __DLXWIN_H
#define __DLXWIN_H

#include<owl\except.h>
#include<owl\applicat.h>
#include<owl\framewin.h>
#include<owl\dc.h>
#include<owl\gdiobject.h>
#include<owl\dialog.h>
#include<owl\edit.h>
#include<owl\scroller.h>
#include<owl\opensave.h>
#include<stdlib.h>
#pragma hdrstop
#include"h\dlx.h"
#include"h\dlxwin.rh"
#include"h\tcpu.h"

#define W_STYLE ((WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS) & ~WS_SYSMENU)

/* classe dialogo Run-N (folha de opcoes)
*/
class TRunNDlg : public TDialog {
public:
  struct TDataBuff {
	 char szNumTicks[7];
  };
  TRunNDlg(TWindow* parent, TRunNDlg::TDataBuff* buff);
};

/* classe janela de visualizacao das unidades de execucao
*/
class TExecView : public TWindow {
public:
  TExecView(TWindow* parent, TCpu* cpuptr);

private:
  TFont fontStyle;
  TSize fontSize;

  TCpu* CpuPtr;

  char sbuf[81], ibuf[81];
protected:
  void SetupWindow();
  void Paint(TDC& dc, BOOL erase, TRect& rect);

  void EvMove(TPoint& clientOrigin);
  void EvSize(uint sizeType, TSize& size);

  DECLARE_RESPONSE_TABLE(TExecView);
};

/* classe janela de visualizacao das unidades virtuais
*/
class TVUView : public TWindow {
public:
  TVUView(TWindow* parent, TCpu* cpuptr);

private:
  TFont fontStyle;
  TSize fontSize;

  TCpu* CpuPtr;

  char sbuf[81], ibuf[81];
protected:
  void SetupWindow();
  void Paint(TDC& dc, BOOL erase, TRect& rect);

  void EvMove(TPoint& clientOrigin);
  void EvSize(uint sizeType, TSize& size);

  DECLARE_RESPONSE_TABLE(TVUView);
};

/* classe janela de visualizacao do Branch Target Buffer
*/
class TBTBView : public TWindow {
public:
  TBTBView(TWindow* parent, TCpu* cpuptr);

private:
  TFont fontStyle;
  TSize fontSize;

  TCpu* CpuPtr;

  char sbuf[81];
protected:
  void SetupWindow();
  void Paint(TDC& dc, BOOL erase, TRect& rect);

  void EvMove(TPoint& clientOrigin);
  void EvSize(uint sizeType, TSize& size);

  DECLARE_RESPONSE_TABLE(TBTBView);
};

/* classe janela de visualizacao do Buffer de Reordenacao
*/
class TROBView : public TWindow {
public:
  TROBView(TWindow* parent, TCpu* cpuptr);

private:
  TFont fontStyle;
  TSize fontSize;

  TCpu* CpuPtr;

  char sbuf[81], ibuf[81];
protected:
  void SetupWindow();
  void Paint(TDC& dc, BOOL erase, TRect& rect);

  void EvMove(TPoint& clientOrigin);
  void EvSize(uint sizeType, TSize& size);

  DECLARE_RESPONSE_TABLE(TROBView);
};

/* classe janela de visualizacao da fila de despacho
*/
class TDisqView : public TWindow {
public:
  TDisqView(TWindow* parent, TCpu* cpuptr);

private:
  TFont fontStyle;
  TSize fontSize;

  TCpu* CpuPtr;

  char sbuf[81], ibuf[81];
protected:
  void SetupWindow();
  void Paint(TDC& dc, BOOL erase, TRect& rect);

  void EvMove(TPoint& clientOrigin);
  void EvSize(uint sizeType, TSize& size);

  DECLARE_RESPONSE_TABLE(TDisqView);
};

/* classe janela de visualizacao da fila de instrucoes
*/
class TIQView : public TWindow {
public:
  TIQView(TWindow* parent, TCpu* cpuptr);

private:
  TFont fontStyle;
  TSize fontSize;

  TCpu* CpuPtr;

  char sbuf[81], ibuf[81];
protected:
  void SetupWindow();
  void Paint(TDC& dc, BOOL erase, TRect& rect);

  void EvMove(TPoint& clientOrigin);
  void EvSize(uint sizeType, TSize& size);

  DECLARE_RESPONSE_TABLE(TIQView);
};

/* classe janela de visualizacao dos registradores de controle
*/
class TRegsView : public TWindow {
public:
  TRegsView(TWindow* parent, TCpu* cpuptr);

private:
  TFont fontStyle;
  TSize fontSize;

  TCpu* CpuPtr;

  char sbuf[81];
protected:
  void SetupWindow();
  void Paint(TDC& dc, BOOL erase, TRect& rect);

  void EvMove(TPoint& clientOrigin);
  void EvSize(uint sizeType, TSize& size);

  DECLARE_RESPONSE_TABLE(TRegsView);
};

/* classe janela de visualizacao dos registradores GPR
*/
class TGprView : public TWindow {
public:
  TGprView(TWindow* parent, TCpu* cpuptr);

private:
  TFont fontStyle;
  TSize fontSize;

  TCpu* CpuPtr;

  char sbuf[81];
protected:
  void SetupWindow();
  void Paint(TDC& dc, BOOL erase, TRect& rect);

  void EvMove(TPoint& clientOrigin);
  void EvSize(uint sizeType, TSize& size);

  DECLARE_RESPONSE_TABLE(TGprView);
};

/* classe janela de visualizacao dos registradores FPR
*/
class TFprView : public TWindow {
public:
  TFprView(TWindow* parent, TCpu* cpuptr);

private:
  TFont fontStyle;
  TSize fontSize;

  TCpu* CpuPtr;

  char sbuf[81];
protected:
  void SetupWindow();
  void Paint(TDC& dc, BOOL erase, TRect& rect);

  void EvMove(TPoint& clientOrigin);
  void EvSize(uint sizeType, TSize& size);

  DECLARE_RESPONSE_TABLE(TFprView);
};

/* classe janela de visualizacao da memoria
*/
class TMemView : public TWindow {
public:
  TMemView(TWindow* parent, TMem* memptr);

private:
  TFont fontStyle;
  TSize fontSize;

  TMem* MemPtr;

  char sbuf[81], ibuf[81];
protected:
  void SetupWindow();
  void Paint(TDC& dc, BOOL erase, TRect& rect);

  void EvMove(TPoint& clientOrigin);
  void EvSize(uint sizeType, TSize& size);

  DECLARE_RESPONSE_TABLE(TMemView);
};

/* classe janela de visualizacao do programa
*/
class TProgView : public TWindow {
public:
  TProgView(TWindow* parent, TMem* memptr);

  void SetCurrentAddress(WORD_T addr)
	 { currAddr = addr; }
private:
  WORD_T topAddr, bottomAddr;
  WORD_T currAddr;

  TFont fontStyle;
  TSize fontSize;

  TMem* MemPtr;

  char sbuf[81], ibuf[81];
protected:
  void SetupWindow();
  void Paint(TDC& dc, BOOL erase, TRect& rect);

  void EvMove(TPoint& clientOrigin);
  void EvSize(uint sizeType, TSize& size);

  DECLARE_RESPONSE_TABLE(TProgView);
};

/* classe janela de execucao das instrucoes
*/
class TExecWindow : public TWindow {
public:
  TExecWindow(TWindow* parent, TCpu* cpuptr);

  TCpu* CpuPtr;
private:
  int startRow;
  int endRow;

  TFont fontStyle;
  TSize fontSize;

protected:
  void SetupWindow();
  void Paint(TDC& dc, BOOL erase, TRect& rect);

  void EvMove(TPoint& clientOrigin);
  void EvSize(uint sizeType, TSize& size);

  DECLARE_RESPONSE_TABLE(TExecWindow);
};

/* classe janela de despacho das instrucoes
*/
class TDispatchWindow : public TWindow {
public:
  TDispatchWindow(TWindow* parent, TCpu* cpuptr);

  TCpu* CpuPtr;
private:
  int startRow;
  int endRow;

  TFont fontStyle;
  TSize fontSize;

protected:
  void SetupWindow();
  void Paint(TDC& dc, BOOL erase, TRect& rect);

  void EvMove(TPoint& clientOrigin);
  void EvSize(uint sizeType, TSize& size);

  DECLARE_RESPONSE_TABLE(TDispatchWindow);
};

/* classe janela principal do aplicativo windows
*/
class TDlxFrameWindow : public TFrameWindow {
public:
  TDlxFrameWindow(TWindow* parent, const char* title);
  ~TDlxFrameWindow();

  TCpu Cpu;

  TExecWindow*     ExecWindow;
  TDispatchWindow* DispatchWindow;

  TProgView*       ProgViewWindow;
  TMemView*        MemViewWindow;
  TRegsView*       RegsViewWindow;
  TGprView*        GprViewWindow;
  TFprView*        FprViewWindow;

  TIQView*         IQViewWindow;
  TDisqView*       DisqViewWindow;
  TROBView*        ROBViewWindow;
  TBTBView*        BTBViewWindow;
  TVUView*         VUViewWindow;
  TExecView*       ExecViewWindow;

private:
  string* WinTitle;
  string* NumTicks;

  string* fileName;
  TOpenSaveDialog::TData fileNameData;
protected:
  void SetupWindow();

  void SetMenuItem(uint mnuItem);
  void ResetMenuItem(uint mnuItem);

  int IsMenuItemChecked(uint mnuItem);

  void ResetAllCpuMenuItem();

  void CmFileOpen();

  void CmReset();
  void CmRun();
  void CmRunn();
  void CmStep();

  void CmExecStream();
  void CmDispatchStream();

  void CmProgView();
  void CmMemoryView();
  void CmRegsView();
  void CmGprView();
  void CmFprView();

  void CmIQView();
  void CmDisqView();
  void CmROBView();
  void CmBTBView();
  void CmVUView();
  void CmExecView();

  void CmCpuEscalar();
  void CmCpuPentium();
  void CmCpuPowerPC();
  void CmCpuAlpha();

  void CmAbout();

  DECLARE_RESPONSE_TABLE(TDlxFrameWindow);
};

/* classe aplicativo windows
*/
class TDlxAppl : public TApplication {
public:
  TDlxAppl(const char* title)
	 : TApplication(title) {};

  void InitMainWindow();
};

#endif  /* __DLXWIN_H */

