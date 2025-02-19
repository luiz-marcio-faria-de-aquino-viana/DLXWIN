
/*
/* DLXWIN.cpp
/* por Luiz Marcio F A Viana, 12/7/96
*/

#include"h\dlxwin.h"

/* classe dialogo Run-N (folha de opcoes)
*/
TRunNDlg::TRunNDlg(TWindow* parent, TRunNDlg::TDataBuff* buff)
  : TDialog(parent, IDDLG_RUNN)
{
  new TEdit(this, IDC_NUMTICKS, 7);
  SetTransferBuffer(buff);
}

/* classe janela de visualizacao das unidades de execucao
*/
TExecView::TExecView(TWindow* parent, TCpu* cpuptr)
  : TWindow(parent),
	 fontStyle("Courier New", 14, 8)
{
  Attr.Style = W_STYLE | WS_HSCROLL | WS_VSCROLL;
  Attr.X = Parent->Attr.W * 3 / 4;
  Attr.Y = Parent->Attr.H * 3 / 4 - 27;
  Attr.W = Parent->Attr.W / 4;
  Attr.H = Parent->Attr.H / 4 - 27;

  CpuPtr = cpuptr;

  Scroller = new TScroller(this, 0, 0, 0, 0);

  SetCaption("Exec Units");
}

void
TExecView::SetupWindow()
{
  TWindow::SetupWindow();
  TClientDC dc(*this);
  dc.SelectObject(fontStyle);
  fontSize = dc.GetTextExtent("M", 1);
  dc.RestoreFont();

  Scroller->SetUnits(fontSize.cx, fontSize.cy);
  Scroller->SetRange(80, 4);
}

void
TExecView::Paint(TDC& dc, BOOL /* erase */, TRect& /* rect */)
{
  int i, ypos = 0;

  dc.SelectObject(fontStyle);

  for(i = 0; i < NUM_ALU; i++)
  {
	 if(CpuPtr->Temp_ALU[i].IsReady())
	 {
		CpuPtr->Temp_ALU[i].GetInstStr(ibuf);
		sprintf(sbuf, " ALU[%02d]:  %s", i, ibuf);
	 }
	 else
		sprintf(sbuf, " ALU[%02d]:  * * * FREE * * *", i);
	 dc.TextOut(0, ypos, sbuf);
	 ypos += fontSize.cy;
  }

  for(i = 0; i < NUM_BPU; i++)
  {
	 if(CpuPtr->Temp_BPU[i].IsReady())
	 {
		CpuPtr->Temp_BPU[i].GetInstStr(ibuf);
		sprintf(sbuf, " BPU[%02d]:  %s", i, ibuf);
	 }
	 else
		sprintf(sbuf, " BPU[%02d]:  * * * FREE * * *", i);
	 dc.TextOut(0, ypos, sbuf);
	 ypos += fontSize.cy;
  }

  for(i = 0; i < NUM_FPU; i++)
  {
	 if(CpuPtr->Temp_FPU[i].IsReady())
	 {
		CpuPtr->Temp_FPU[i].GetInstStr(ibuf);
		sprintf(sbuf, " FPU[%02d]:  %s", i, ibuf);
	 }
	 else
		sprintf(sbuf, " FPU[%02d]:  * * * FREE * * *", i);
	 dc.TextOut(0, ypos, sbuf);
	 ypos += fontSize.cy;
  }

  for(i = 0; i < NUM_LSU; i++)
  {
	 if(CpuPtr->Temp_LSU[i].IsReady())
	 {
		CpuPtr->Temp_LSU[i].GetInstStr(ibuf);
		sprintf(sbuf, " LSU[%02d]:  %s", i, ibuf);
	 }
	 else
		sprintf(sbuf, " LSU[%02d]:  * * * FREE * * *", i);
	 dc.TextOut(0, ypos, sbuf);
  }

  dc.RestoreFont();
}

void
TExecView::EvMove(TPoint& /* clientOrigin */)
{
  Parent->Invalidate();
}

void
TExecView::EvSize(uint /* sizeType */, TSize& /* size */)
{
  Parent->Invalidate();
}

DEFINE_RESPONSE_TABLE1(TExecView, TWindow)
  EV_WM_MOVE,
  EV_WM_SIZE,
END_RESPONSE_TABLE;

/* classe janela de visualizacao das unidades virtuais
*/
TVUView::TVUView(TWindow* parent, TCpu* cpuptr)
  : TWindow(parent),
	 fontStyle("Courier New", 14, 8)
{
  Attr.Style = W_STYLE | WS_HSCROLL | WS_VSCROLL;
  Attr.X = Parent->Attr.W / 2;
  Attr.Y = Parent->Attr.H * 3 / 4 - 27;
  Attr.W = Parent->Attr.W / 4;
  Attr.H = Parent->Attr.H / 4 - 27;

  CpuPtr = cpuptr;

  Scroller = new TScroller(this, 0, 0, 0, 0);

  SetCaption("Virtual Units");
}

void
TVUView::SetupWindow()
{
  TWindow::SetupWindow();
  TClientDC dc(*this);
  dc.SelectObject(fontStyle);
  fontSize = dc.GetTextExtent("M", 1);
  dc.RestoreFont();

  Scroller->SetUnits(fontSize.cx, fontSize.cy);
  Scroller->SetRange(80, 4 * CpuPtr->VALU.GetNumEntries());
}

void
TVUView::Paint(TDC& dc, BOOL /* erase */, TRect& /* rect */)
{
  TData ci;
  int i, ypos = 0;

  dc.SelectObject(fontStyle);

  dc.TextOut(0, ypos, " ALU:  ");
  for(i = 0; i < CpuPtr->VALU.GetNumEntries(); i++)
  {
	  if(i < CpuPtr->VALU.GetNumItens())
	  {
		 CpuPtr->VALU.GetItemNum(i, ci);
		 ci.GetInstStr(ibuf);
		 if( ci.IsReady() )
			sprintf(sbuf, " R %d. %s", i, ibuf);
		 else
			sprintf(sbuf, "   %d. %s", i, ibuf);
	  }
	  else
		 sprintf(sbuf, "   %d. * * * FREE * * *", i);
	  dc.TextOut(6 * fontSize.cx, ypos, sbuf);
	  ypos += fontSize.cy;
  }
  ypos += fontSize.cy;

  dc.TextOut(0, ypos, " BPU:  ");
  for(i = 0; i < CpuPtr->VBPU.GetNumEntries(); i++)
  {
	  if(i < CpuPtr->VBPU.GetNumItens())
	  {
		 CpuPtr->VBPU.GetItemNum(i, ci);
		 ci.GetInstStr(ibuf);
		 if( ci.IsReady() )
			sprintf(sbuf, " R %d. %s", i, ibuf);
		 else
			sprintf(sbuf, "   %d. %s", i, ibuf);
	  }
	  else
		 sprintf(sbuf, "   %d. * * * FREE * * *", i);
	  dc.TextOut(6 * fontSize.cx, ypos, sbuf);
	  ypos += fontSize.cy;
  }
  ypos += fontSize.cy;

  dc.TextOut(0, ypos, " FPU:  ");
  for(i = 0; i < CpuPtr->VFPU.GetNumEntries(); i++)
  {
	  if(i < CpuPtr->VFPU.GetNumItens())
	  {
		 CpuPtr->VFPU.GetItemNum(i, ci);
		 ci.GetInstStr(ibuf);
		 if( ci.IsReady() )
			sprintf(sbuf, " R %d. %s", i, ibuf);
		 else
			sprintf(sbuf, "   %d. %s", i, ibuf);
	  }
	  else
		 sprintf(sbuf, "   %d. * * * FREE * * *", i);
	  dc.TextOut(6 * fontSize.cx, ypos, sbuf);
	  ypos += fontSize.cy;
  }
  ypos += fontSize.cy;

  dc.TextOut(0, ypos, " LSU: ");
  for(i = 0; i < CpuPtr->VLSU.GetNumEntries(); i++)
  {
	  if(i < CpuPtr->VLSU.GetNumItens())
	  {
		 CpuPtr->VLSU.GetItemNum(i, ci);
		 ci.GetInstStr(ibuf);
		 if( ci.IsReady() )
			sprintf(sbuf, " R %d. %s", i, ibuf);
		 else
			sprintf(sbuf, "   %d. %s", i, ibuf);
	  }
	  else
		 sprintf(sbuf, "   %d. * * * FREE * * *", i);
	  dc.TextOut(6 * fontSize.cx, ypos, sbuf);
	  ypos += fontSize.cy;
  }
  ypos += fontSize.cy;

  dc.RestoreFont();
}

void
TVUView::EvMove(TPoint& /* clientOrigin */)
{
  Parent->Invalidate();
}

void
TVUView::EvSize(uint /* sizeType */, TSize& /* size */)
{
  Parent->Invalidate();
}

DEFINE_RESPONSE_TABLE1(TVUView, TWindow)
  EV_WM_MOVE,
  EV_WM_SIZE,
END_RESPONSE_TABLE;

/* classe janela de visualizacao do Branch Target Buffer
*/
TBTBView::TBTBView(TWindow* parent, TCpu* cpuptr)
  : TWindow(parent),
	 fontStyle("Courier New", 14, 8)
{
  Attr.Style = W_STYLE | WS_HSCROLL | WS_VSCROLL;
  Attr.Y = Parent->Attr.H * 3 / 4;
  Attr.W = Parent->Attr.W;
  Attr.H = Parent->Attr.H / 4;

  CpuPtr = cpuptr;

  Scroller = new TScroller(this, 0, 0, 0, 0);

  SetCaption("Branch Target Buffer");
}

void
TBTBView::SetupWindow()
{
  TWindow::SetupWindow();
  TClientDC dc(*this);
  dc.SelectObject(fontStyle);
  fontSize = dc.GetTextExtent("M", 1);
  dc.RestoreFont();

  Scroller->SetUnits(fontSize.cx, fontSize.cy);
  Scroller->SetRange(80, CpuPtr->BTB.GetNumSlots());
}

void
TBTBView::Paint(TDC& dc, BOOL /* erase */, TRect& /* rect */)
{
  TBTBItem* p;

  dc.SelectObject(fontStyle);
  for(int i = 0; i < CpuPtr->BTB.GetNumSlots(); i++)
  {
	 for(int j = 0; j < CpuPtr->BTB.GetNumEntries(); j++)
	 {
		p = CpuPtr->BTB.GetItem(i, j);
		if( p->IsValid() )
		  sprintf(sbuf, " %08lX:%08lX |", p->Tag, p->Dst);
		else
		  sprintf(sbuf, " ***EMPTY ENTRY*** |");
		dc.TextOut(20 * j * fontSize.cx, i * fontSize.cy, sbuf);
	 }
  }
  dc.RestoreFont();
}

void
TBTBView::EvMove(TPoint& /* clientOrigin */)
{
  Parent->Invalidate();
}

void
TBTBView::EvSize(uint /* sizeType */, TSize& /* size */)
{
  Parent->Invalidate();
}

DEFINE_RESPONSE_TABLE1(TBTBView, TWindow)
  EV_WM_MOVE,
  EV_WM_SIZE,
END_RESPONSE_TABLE;

/* classe janela de visualizacao do Buffer de Reordenacao
*/
TROBView::TROBView(TWindow* parent, TCpu* cpuptr)
  : TWindow(parent),
	 fontStyle("Courier New", 14, 8)
{
  Attr.Style = W_STYLE | WS_HSCROLL | WS_VSCROLL;
  Attr.X = Parent->Attr.W * 5 / 6;
  Attr.Y = Parent->Attr.H / 2;
  Attr.W = Parent->Attr.W / 6;
  Attr.H = Parent->Attr.H / 4 - 27;

  CpuPtr = cpuptr;

  Scroller = new TScroller(this, 0, 0, 0, 0);

  SetCaption("Reorder Buffer");
}

void
TROBView::SetupWindow()
{
  TWindow::SetupWindow();
  TClientDC dc(*this);
  dc.SelectObject(fontStyle);
  fontSize = dc.GetTextExtent("M", 1);
  dc.RestoreFont();

  Scroller->SetUnits(fontSize.cx, fontSize.cy);
  Scroller->SetRange(80, CpuPtr->ROB.GetNumEntries());
}

void
TROBView::Paint(TDC& dc, BOOL /* erase */, TRect& /* rect */)
{
  TData* p;
  int ypos = 0;

  dc.SelectObject(fontStyle);
  for(int i = 0; i < CpuPtr->ROB.GetNumEntries(); i++)
  {
	 if( i < CpuPtr->ROB.GetNumItens() )
	 {
		p = CpuPtr->ROB.GetItemNum(i);
		p->GetInstStr(ibuf);
		if( p->IsReady() )
		  sprintf(sbuf, "R %d. %s", i, ibuf);
		else
		  sprintf(sbuf, "  %d. %s", i, ibuf);
	 }
	 else
	 {
		sprintf(sbuf, "  %d. * * * EMPTY * * *", i);
	 }
	 dc.TextOut(0, ypos, sbuf);
	 ypos += fontSize.cy;
  }
  dc.RestoreFont();
}

void
TROBView::EvMove(TPoint& /* clientOrigin */)
{
  Parent->Invalidate();
}

void
TROBView::EvSize(uint /* sizeType */, TSize& /* size */)
{
  Parent->Invalidate();
}

DEFINE_RESPONSE_TABLE1(TROBView, TWindow)
  EV_WM_MOVE,
  EV_WM_SIZE,
END_RESPONSE_TABLE;

/* classe janela de visualizacao da fila de instrucoes
*/
TDisqView::TDisqView(TWindow* parent, TCpu* cpuptr)
  : TWindow(parent),
	 fontStyle("Courier New", 14, 8)
{
  Attr.Style = W_STYLE | WS_HSCROLL | WS_VSCROLL;
  Attr.X = Parent->Attr.W * 4 / 6;
  Attr.Y = Parent->Attr.H / 2;
  Attr.W = Parent->Attr.W / 6;
  Attr.H = Parent->Attr.H / 4 - 27;

  CpuPtr = cpuptr;

  Scroller = new TScroller(this, 0, 0, 0, 0);

  SetCaption("Dispatch Queue");
}

void
TDisqView::SetupWindow()
{
  TWindow::SetupWindow();
  TClientDC dc(*this);
  dc.SelectObject(fontStyle);
  fontSize = dc.GetTextExtent("M", 1);
  dc.RestoreFont();

  Scroller->SetUnits(fontSize.cx, fontSize.cy);
  Scroller->SetRange(80, CpuPtr->Disq.GetNumEntries());
}

void
TDisqView::Paint(TDC& dc, BOOL /* erase */, TRect& /* rect */)
{
  TData* p;
  int xpos, ypos = 0;

  dc.SelectObject(fontStyle);
  for(int i = 0; i < CpuPtr->Disq.GetNumEntries(); i++)
  {
	 sprintf(sbuf, "%d.", i);
	 dc.TextOut(0, ypos, sbuf);

	 xpos = 3 * fontSize.cx;
	 if( i < CpuPtr->Disq.GetNumItens() )
	 {
		p = CpuPtr->Disq.GetItemNum(i);
		p->GetInstStr(ibuf);
		sprintf(sbuf, "%08lX  %s", p->PC, ibuf);

		for(int j = 0; j < p->GetBranchLevel(); j++)
		{
		  dc.TextOut(xpos, ypos, " >");
		  xpos += fontSize.cx * 2;
		}
		xpos += fontSize.cx;
	 }
	 else
		sprintf(sbuf, " * * * EMPTY * * *", i);

	 dc.TextOut(xpos, ypos, sbuf);
	 ypos += fontSize.cy;
  }
  dc.RestoreFont();
}

void
TDisqView::EvMove(TPoint& /* clientOrigin */)
{
  Parent->Invalidate();
}

void
TDisqView::EvSize(uint /* sizeType */, TSize& /* size */)
{
  Parent->Invalidate();
}

DEFINE_RESPONSE_TABLE1(TDisqView, TWindow)
  EV_WM_MOVE,
  EV_WM_SIZE,
END_RESPONSE_TABLE;

/* classe janela de visualizacao da fila de instrucoes
*/
TIQView::TIQView(TWindow* parent, TCpu* cpuptr)
  : TWindow(parent),
	 fontStyle("Courier New", 14, 8)
{
  Attr.Style = W_STYLE | WS_HSCROLL | WS_VSCROLL;
  Attr.X = Parent->Attr.W / 2;
  Attr.Y = Parent->Attr.H / 2;
  Attr.W = Parent->Attr.W / 6;
  Attr.H = Parent->Attr.H / 4 - 27;

  CpuPtr = cpuptr;

  Scroller = new TScroller(this, 0, 0, 0, 0);

  SetCaption("Instruction Queue");
}

void
TIQView::SetupWindow()
{
  TWindow::SetupWindow();
  TClientDC dc(*this);
  dc.SelectObject(fontStyle);
  fontSize = dc.GetTextExtent("M", 1);
  dc.RestoreFont();

  Scroller->SetUnits(fontSize.cx, fontSize.cy);
  Scroller->SetRange(80, CpuPtr->IQ.GetNumEntries());
}

void
TIQView::Paint(TDC& dc, BOOL /* erase */, TRect& /* rect */)
{
  TData* p;
  int ypos = 0;

  dc.SelectObject(fontStyle);
  for(int i = 0; i < CpuPtr->IQ.GetNumEntries(); i++)
  {
	 if( i < CpuPtr->IQ.GetNumItens() )
	 {
		p = CpuPtr->IQ.GetItem(i);
		p->GetInstStr(ibuf);
		sprintf(sbuf, "%d. %08lX  %s", i, p->PC, ibuf);
	 }
	 else
	 {
		sprintf(sbuf, "%d. * * * EMPTY * * *", i);
	 }
	 dc.TextOut(0, ypos, sbuf);
	 ypos += fontSize.cy;
  }
  dc.RestoreFont();
}

void
TIQView::EvMove(TPoint& /* clientOrigin */)
{
  Parent->Invalidate();
}

void
TIQView::EvSize(uint /* sizeType */, TSize& /* size */)
{
  Parent->Invalidate();
}

DEFINE_RESPONSE_TABLE1(TIQView, TWindow)
  EV_WM_MOVE,
  EV_WM_SIZE,
END_RESPONSE_TABLE;

/* classe janela de visualizacao dos registradores de controle
*/
TRegsView::TRegsView(TWindow* parent, TCpu* cpuptr)
  : TWindow(parent),
	 fontStyle("Courier New", 14, 8)
{
  Attr.Style = W_STYLE | WS_HSCROLL | WS_VSCROLL;
  Attr.X = parent->Attr.W / 2;
  Attr.W = Parent->Attr.W / 4;
  Attr.H = Parent->Attr.H / 4;

  CpuPtr = cpuptr;

  Scroller = new TScroller(this, 0, 0, 0, 0);

  SetCaption("Regs");
}

void
TRegsView::SetupWindow()
{
  TWindow::SetupWindow();
  TClientDC dc(*this);
  dc.SelectObject(fontStyle);
  fontSize = dc.GetTextExtent("M", 1);
  dc.RestoreFont();

  Scroller->SetUnits(fontSize.cx, fontSize.cy);
  Scroller->SetRange(80, 6);
}

void
TRegsView::Paint(TDC& dc, BOOL /* erase */, TRect& /* rect */)
{
  int i, ypos = 0;

  dc.SelectObject(fontStyle);

  sprintf(sbuf, "PC      = %08lX", CpuPtr->PC);
  dc.TextOut(0, ypos, sbuf);
  ypos += fontSize.cy;

  sprintf(sbuf, "IR      = %08lX", CpuPtr->IR);
  dc.TextOut(0, ypos, sbuf);
  ypos += fontSize.cy;

  if( CpuPtr->FP.IsBusy() )
	 sprintf(sbuf, "FP      = %08lX (%08lX) #%d", CpuPtr->FP.R.x.W, CpuPtr->FP.R1.x.W, CpuPtr->FP.GetIdentifier());
  else
	 sprintf(sbuf, "FP      = %08lX (%08lX)    ", CpuPtr->FP.R.x.W, CpuPtr->FP.R1.x.W);
  dc.TextOut(0, ypos, sbuf);
  ypos += fontSize.cy;

  if( CpuPtr->IAR.IsBusy() )
	 sprintf(sbuf, "IAR     = %08lX (%08lX) #%d", CpuPtr->IAR.R.x.W, CpuPtr->IAR.R1.x.W, CpuPtr->IAR.GetIdentifier());
  else
	 sprintf(sbuf, "IAR     = %08lX (%08lX)    ", CpuPtr->IAR.R.x.W, CpuPtr->IAR.R1.x.W);
  dc.TextOut(0, ypos, sbuf);
  ypos += fontSize.cy;

  sprintf(sbuf, "Cicle   = %ld              ", CpuPtr->Cicle);
  dc.TextOut(0, ypos, sbuf);
  ypos += fontSize.cy;

  if(CpuPtr->Tempo_paralelo > 0)
	 sprintf(sbuf, "SPEEDUP = %lf              ", CpuPtr->Tempo_seq / CpuPtr->Tempo_paralelo);
  else
	 sprintf(sbuf, "SPEEDUP = 0                ");
  dc.TextOut(0, ypos, sbuf);
  ypos += 2*fontSize.cy;

  for(i = 0; i < NUM_UNIT + 1; i++)
  {
	 sprintf(sbuf, " => Ocupacao de %d unidades = %ld", i, CpuPtr->cont[i]);
	 dc.TextOut(0, ypos, sbuf);
	 ypos += fontSize.cy;
  }

  dc.RestoreFont();
}

void
TRegsView::EvMove(TPoint& /* clientOrigin */)
{
  Parent->Invalidate();
}

void
TRegsView::EvSize(uint /* sizeType */, TSize& /* size */)
{
  Parent->Invalidate();
}

DEFINE_RESPONSE_TABLE1(TRegsView, TWindow)
  EV_WM_MOVE,
  EV_WM_SIZE,
END_RESPONSE_TABLE;

/* classe janela de visualizacao dos registradores GPR
*/
TGprView::TGprView(TWindow* parent, TCpu* cpuptr)
  : TWindow(parent),
	 fontStyle("Courier New", 14, 8)
{
  Attr.Style = W_STYLE | WS_HSCROLL | WS_VSCROLL;
  Attr.X = parent->Attr.W * 3 / 4;
  Attr.W = Parent->Attr.W / 4;
  Attr.H = Parent->Attr.H / 4;

  CpuPtr = cpuptr;

  Scroller = new TScroller(this, 0, 0, 0, 0);

  SetCaption("GPR");
}

void
TGprView::SetupWindow()
{
  TWindow::SetupWindow();
  TClientDC dc(*this);
  dc.SelectObject(fontStyle);
  fontSize = dc.GetTextExtent("M", 1);
  dc.RestoreFont();

  Scroller->SetUnits(fontSize.cx, fontSize.cy);
  Scroller->SetRange(80, 32);
}

void
TGprView::Paint(TDC& dc, BOOL /* erase */, TRect& /* rect */)
{
  TRegs* r;
  int ypos = 0;

  dc.SelectObject(fontStyle);
  for(int i = 0; i < 32; i++)
  {
	 r = CpuPtr->R.GetRegister(i);
	 if( r->IsBusy() )
		sprintf(sbuf, "R[%02d] = %08lX (%08lX) #%d", i, r->R.x.W, r->R1.x.W, r->GetIdentifier());
	 else
		sprintf(sbuf, "R[%02d] = %08lX (%08lX)    ", i, r->R.x.W, r->R1.x.W);
	 dc.TextOut(0, ypos, sbuf);
	 ypos += fontSize.cy;
  }
  dc.RestoreFont();
}

void
TGprView::EvMove(TPoint& /* clientOrigin */)
{
  Parent->Invalidate();
}

void
TGprView::EvSize(uint /* sizeType */, TSize& /* size */)
{
  Parent->Invalidate();
}

DEFINE_RESPONSE_TABLE1(TGprView, TWindow)
  EV_WM_MOVE,
  EV_WM_SIZE,
END_RESPONSE_TABLE;

/* classe janela de visualizacao dos registradores FPR
*/
TFprView::TFprView(TWindow* parent, TCpu* cpuptr)
  : TWindow(parent),
	 fontStyle("Courier New", 14, 8)
{
  Attr.Style = W_STYLE | WS_HSCROLL | WS_VSCROLL;
  Attr.X = parent->Attr.W / 2;
  Attr.Y = parent->Attr.H / 4;
  Attr.W = Parent->Attr.W / 2;
  Attr.H = Parent->Attr.H / 4;

  CpuPtr = cpuptr;

  Scroller = new TScroller(this, 0, 0, 0, 0);

  SetCaption("FPR");
}

void
TFprView::SetupWindow()
{
  TWindow::SetupWindow();
  TClientDC dc(*this);
  dc.SelectObject(fontStyle);
  fontSize = dc.GetTextExtent("M", 1);
  dc.RestoreFont();

  Scroller->SetUnits(fontSize.cx, fontSize.cy);
  Scroller->SetRange(80, 32);
}

void
TFprView::Paint(TDC& dc, BOOL /* erase */, TRect& /* rect */)
{
  TRegs* f;
  int ypos = 0;

  dc.SelectObject(fontStyle);
  for(int i = 0; i < 32; i++)
  {
	 f = CpuPtr->F.GetRegister(i);
	 if( f->IsBusy() )
		sprintf(sbuf, "F[%02d] = %8.6lf (%8.6lf)  |  %8.6le (%8.6le) #%d",
		  i, f->R.x.F, f->R1.x.F, f->R.x.D, f->R1.x.D, f->GetIdentifier());
	 else
		sprintf(sbuf, "F[%02d] = %8.6lf (%8.6lf)  |  %8.6le (%8.6le)    ",
		  i, f->R.x.F, f->R1.x.F, f->R.x.D, f->R1.x.D);
	 dc.TextOut(0, ypos, sbuf);
	 ypos += fontSize.cy;
  }
  dc.RestoreFont();
}

void
TFprView::EvMove(TPoint& /* clientOrigin */)
{
  Parent->Invalidate();
}

void
TFprView::EvSize(uint /* sizeType */, TSize& /* size */)
{
  Parent->Invalidate();
}

DEFINE_RESPONSE_TABLE1(TFprView, TWindow)
  EV_WM_MOVE,
  EV_WM_SIZE,
END_RESPONSE_TABLE;

/* classe janela de visualizacao da memoria
*/
TMemView::TMemView(TWindow* parent, TMem* memptr)
  : TWindow(parent),
	 fontStyle("Courier New", 14, 8)
{
  Attr.Style = W_STYLE | WS_HSCROLL | WS_VSCROLL;
  Attr.Y = parent->Attr.H / 2;
  Attr.W = Parent->Attr.W / 2;
  Attr.H = Parent->Attr.H / 2 - 54;

  MemPtr = memptr;

  Scroller = new TScroller(this, 0, 0, 0, 0);
  Scroller->TrackMode = 0;

  SetCaption("Memory");
}

void
TMemView::SetupWindow()
{
  TWindow::SetupWindow();
  TClientDC dc(*this);
  dc.SelectObject(fontStyle);
  fontSize = dc.GetTextExtent("M", 1);
  dc.RestoreFont();

  Scroller->SetUnits(fontSize.cx, fontSize.cy);
  Scroller->SetRange(80, MemPtr->GetMemSz() / 16);
}

void
TMemView::Paint(TDC& dc, BOOL /* erase */, TRect& rect)
{
  WORD_T addr;
  UBYTE_T dat;

  uint ypos = 0;

  uint fstRow, lstRow;

  fstRow = rect.top / fontSize.cy;
  lstRow = rect.bottom / fontSize.cy + 1;

  dc.SelectObject(fontStyle);
  for(uint i = fstRow; i < lstRow; i++)
  {
	 if((addr = i * 16) >= MemPtr->GetMemSz()) break;

	 sprintf(sbuf, "%08lX: ", addr);
	 for(uint j = 0; j < 4; j++)
	 {
		for(uint k = 0; k < 4; k++)
		{
		  MemPtr->RD(addr+k, &dat, sizeof(BYTE_T));
		  sprintf(ibuf, "%02hX ", dat);
		  strcat(sbuf, ibuf);
		}
		sprintf(ibuf, "  ", dat);
		strcat(sbuf, ibuf);
		addr += 4;
	 }

	 ypos = i * fontSize.cy;
	 dc.TextOut(0, ypos, sbuf);
  }

  dc.RestoreFont();
}

void
TMemView::EvMove(TPoint& /* clientOrigin */)
{
  Parent->Invalidate();
}

void
TMemView::EvSize(uint /* sizeType */, TSize& /* size */)
{
  Parent->Invalidate();
}

DEFINE_RESPONSE_TABLE1(TMemView, TWindow)
  EV_WM_MOVE,
  EV_WM_SIZE,
END_RESPONSE_TABLE;

/* classe janela de visualizacao do programa
*/
TProgView::TProgView(TWindow* parent, TMem* memptr)
  : TWindow(parent),
	 fontStyle("Courier New", 14, 8)
{
  Attr.Style = W_STYLE | WS_HSCROLL | WS_VSCROLL;
  Attr.W = Parent->Attr.W / 2;
  Attr.H = Parent->Attr.H / 2;

  MemPtr = memptr;

  Scroller = new TScroller(this, 0, 0, 0, 0);
  Scroller->TrackMode = 0;

  SetCaption("Program");
}

void
TProgView::SetupWindow()
{
  TWindow::SetupWindow();
  TClientDC dc(*this);
  dc.SelectObject(fontStyle);
  fontSize = dc.GetTextExtent("M", 1);
  dc.RestoreFont();

  currAddr = 0;

  Scroller->SetUnits(fontSize.cx, fontSize.cy);
  Scroller->SetRange(80, MemPtr->GetMemSz() / 4);
}

void
TProgView::Paint(TDC& dc, BOOL /* erase */, TRect& rect)
{
  TColor textColor, bkColor;

  WORD_T addr;
  uint ypos;

  uint fstRow, lstRow;

  fstRow = rect.top / fontSize.cy;
  lstRow = rect.bottom / fontSize.cy + 1;

  dc.SelectObject(fontStyle);
  for(uint i = fstRow; i < lstRow; i++)
  {
	 if((addr = i * 4) >= MemPtr->GetMemSz()) break;

	 MemPtr->GetInstr(addr, ibuf);
	 ypos = i * fontSize.cy;

	 sprintf(sbuf, "%08lX: %s", addr, ibuf);
	 dc.TextOut(0, ypos, sbuf);
  }

  MemPtr->GetInstr(currAddr, ibuf);
  sprintf(sbuf, "%08lX: %s", currAddr, ibuf);
  memset(& sbuf[strlen(sbuf)], ' ', 80 - strlen(sbuf));
  sbuf[80] = '\0';
  textColor = dc.GetTextColor();
  bkColor = dc.GetBkColor();
  dc.SetTextColor(TColor::White);
  dc.SetBkColor(TColor::LtBlue);
  dc.TextOut(0, (uint) (currAddr / 4) * fontSize.cy, sbuf);
  dc.SetTextColor(textColor);
  dc.SetBkColor(bkColor);
  dc.RestoreFont();
}

void
TProgView::EvMove(TPoint& /* clientOrigin */)
{
  Parent->Invalidate();
}

void
TProgView::EvSize(uint /* sizeType */, TSize& /* size */)
{
  Parent->Invalidate();
}

DEFINE_RESPONSE_TABLE1(TProgView, TWindow)
  EV_WM_MOVE,
  EV_WM_SIZE,
END_RESPONSE_TABLE;

/* classe janela de execucao das instrucoes
*/
TExecWindow::TExecWindow(TWindow* parent, TCpu* cpuptr)
  : TWindow(parent),
	 fontStyle("Courier New", 14, 8)
{
  Attr.Style = W_STYLE | WS_HSCROLL | WS_VSCROLL;
  Attr.Y = Parent->Attr.H * 3 / 4 - 27;
  Attr.W = Parent->Attr.W / 2;
  Attr.H = Parent->Attr.H / 4 - 27;

  CpuPtr = cpuptr;

  Scroller = new TScroller(this, 0, 0, 0, 0);
  Scroller->TrackMode = 0;

  SetCaption("Execution Stream");
}

void
TExecWindow::SetupWindow()
{
  TWindow::SetupWindow();
  TClientDC dc(*this);
  dc.SelectObject(fontStyle);
  fontSize = dc.GetTextExtent("M", 1);
  dc.RestoreFont();

  Scroller->SetUnits(fontSize.cx, fontSize.cy);
}

void
TExecWindow::Paint(TDC& dc, BOOL /* erase */, TRect& /* rect */)
{
  int dy;
  dc.SelectObject(fontStyle);
  for(int i = 0; i < CpuPtr->ExecBuff.GetNumItens(); i++) {
	 dy = 1.10 * i * fontSize.cy;
	 dc.TextOut(0, dy, CpuPtr->ExecBuff.GetBuffItem(i));
  }
  Scroller->SetRange(80, CpuPtr->ExecBuff.GetNumItens());
  dc.RestoreFont();
}

void
TExecWindow::EvMove(TPoint& /* clientOrigin */)
{
  Parent->Invalidate();
}

void
TExecWindow::EvSize(uint /* sizeType */, TSize& /* size */)
{
  Parent->Invalidate();
}

DEFINE_RESPONSE_TABLE1(TExecWindow, TWindow)
  EV_WM_MOVE,
  EV_WM_SIZE,
END_RESPONSE_TABLE;

/* classe janela de despacho das instrucoes
*/
TDispatchWindow::TDispatchWindow(TWindow* parent, TCpu* cpuptr)
  : TWindow(parent),
	 fontStyle("Courier New", 14, 8)
{
  Attr.Style = W_STYLE | WS_HSCROLL | WS_VSCROLL;
  Attr.Y = Parent->Attr.H / 2;
  Attr.W = Parent->Attr.W / 2;
  Attr.H = Parent->Attr.H / 4 - 27;

  CpuPtr = cpuptr;

  Scroller = new TScroller(this, 0, 0, 0, 0);
  Scroller->TrackMode = 0;

  SetCaption("Dispatch Stream");
}

void
TDispatchWindow::SetupWindow()
{
  TWindow::SetupWindow();
  TClientDC dc(*this);
  dc.SelectObject(fontStyle);
  fontSize = dc.GetTextExtent("M", 1);
  dc.RestoreFont();

  Scroller->SetUnits(fontSize.cx, fontSize.cy);
}

void
TDispatchWindow::Paint(TDC& dc, BOOL /* erase */, TRect& /* rect */)
{
  int dy;
  dc.SelectObject(fontStyle);
  for(int i = 0; i < CpuPtr->DispBuff.GetNumItens(); i++) {
	 dy = 1.10 * i * fontSize.cy;
	 dc.TextOut(0, dy, CpuPtr->DispBuff.GetBuffItem(i));
  }
  Scroller->SetRange(80, CpuPtr->DispBuff.GetNumItens());
  dc.RestoreFont();
}

void
TDispatchWindow::EvMove(TPoint& /* clientOrigin */)
{
  Parent->Invalidate();
}

void
TDispatchWindow::EvSize(uint /* sizeType */, TSize& /* size */)
{
  Parent->Invalidate();
}

DEFINE_RESPONSE_TABLE1(TDispatchWindow, TWindow)
  EV_WM_MOVE,
  EV_WM_SIZE,
END_RESPONSE_TABLE;

/* classe janela principal do aplicativo windows
*/
TDlxFrameWindow::TDlxFrameWindow(TWindow* parent, const char* title)
  : TFrameWindow(parent, title),
	 TWindow(parent, title),
	 fileNameData(OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		"Binary files (*.bin)|*.bin|All files (*.*)|*.*|",
		0, "", "*")
{
  AssignMenu(IDMENU);
  Attr.H = GetSystemMetrics(SM_CYSCREEN);
  Attr.W = GetSystemMetrics(SM_CXSCREEN);

  ExecViewWindow = new TExecView(this, &Cpu);
  VUViewWindow = new TVUView(this, &Cpu);
  BTBViewWindow = new TBTBView(this, &Cpu);
  ROBViewWindow = new TROBView(this, &Cpu);
  DisqViewWindow = new TDisqView(this, &Cpu);
  IQViewWindow = new TIQView(this, &Cpu);

  DispatchWindow = new TDispatchWindow(this, &Cpu);
  ExecWindow = new TExecWindow(this, &Cpu);

  ProgViewWindow = new TProgView(this, &Cpu.Mem);
  MemViewWindow = new TMemView(this, &Cpu.Mem);
  RegsViewWindow = new TRegsView(this, &Cpu);
  GprViewWindow = new TGprView(this, &Cpu);
  FprViewWindow = new TFprView(this, &Cpu);

  WinTitle = new string(title);
  NumTicks = new string("2000");
  fileName = 0;
}

TDlxFrameWindow::~TDlxFrameWindow()
{
  delete WinTitle;
  delete NumTicks;
  delete fileName;
}

void
TDlxFrameWindow::SetupWindow()
{
  TFrameWindow::SetupWindow();

  SetMenuItem(CM_VIEWEXEC_UNITS);
  ExecViewWindow->Show(SW_SHOW);

  SetMenuItem(CM_VIEWVIRTUAL_UNITS);
  VUViewWindow->Show(SW_SHOW);

  ResetMenuItem(CM_VIEWBRANCH_TARGET_BUFFER);
  BTBViewWindow->Show(SW_HIDE);

  SetMenuItem(CM_VIEWREORDER_BUFFER);
  ROBViewWindow->Show(SW_SHOW);

  SetMenuItem(CM_VIEWDISPATCH_QUEUE);
  DisqViewWindow->Show(SW_SHOW);

  SetMenuItem(CM_VIEWINSTRUCTION_QUEUE);
  IQViewWindow->Show(SW_SHOW);

  Cpu.DisableExecStream();
  ResetMenuItem(CM_VIEWEXEC_STREAM);
  ExecWindow->Show(SW_HIDE);

  Cpu.DisableDispatchStream();
  ResetMenuItem(CM_VIEWDISPATCH_STREAM);
  DispatchWindow->Show(SW_HIDE);

  SetMenuItem(CM_VIEWPROGRAM);
  ProgViewWindow->Show(SW_SHOW);

  SetMenuItem(CM_VIEWMEMORY);
  MemViewWindow->Show(SW_SHOW);

  SetMenuItem(CM_VIEWREGS);
  RegsViewWindow->Show(SW_SHOW);

  SetMenuItem(CM_VIEWGPR);
  GprViewWindow->Show(SW_SHOW);

  SetMenuItem(CM_VIEWFPR);
  FprViewWindow->Show(SW_SHOW);

  ResetAllCpuMenuItem();
  SetMenuItem(CM_CPUESCALAR);
  Cpu.SetCpuType(ESCALAR);
}

void
TDlxFrameWindow::SetMenuItem(uint mnuItem)
{
  ::CheckMenuItem(GetMenu(), mnuItem, MF_BYCOMMAND | MF_CHECKED);
}

void
TDlxFrameWindow::ResetMenuItem(uint mnuItem)
{
  ::CheckMenuItem(GetMenu(), mnuItem, MF_BYCOMMAND | MF_UNCHECKED);
}

int
TDlxFrameWindow::IsMenuItemChecked(uint mnuItem)
{
  return (::GetMenuState(GetMenu(), mnuItem, MF_BYCOMMAND) & MF_CHECKED);
}

void
TDlxFrameWindow::ResetAllCpuMenuItem()
{
  ResetMenuItem(CM_CPUESCALAR);
  ResetMenuItem(CM_CPUPENTIUM);
  ResetMenuItem(CM_CPUPOWERPC);
  ResetMenuItem(CM_CPUALPHA);
}

void
TDlxFrameWindow::CmFileOpen()
{
  string s(WinTitle->c_str());
  if((new TFileOpenDialog(this, fileNameData))->Execute() == IDOK)
	 if(fileNameData.Error == 0) {
		delete fileName;
		fileName = new string(fileNameData.FileName);
		s.append(" - ");
		s.append(fileName->c_str());
		SetCaption(s.c_str());
		Cpu.OpenFile(fileName->c_str());
		ProgViewWindow->SetCurrentAddress(Cpu.GetCurrentAddress());
		Invalidate();
	 }
}

void
TDlxFrameWindow::CmReset()
{
  Cpu.Reset();
  ProgViewWindow->SetCurrentAddress(Cpu.GetCurrentAddress());
  Invalidate();
  MessageBox("Program Reseted.", "Program...", MB_OK);
}

void
TDlxFrameWindow::CmRun()
{
  Cpu.Run();
  Invalidate();
  MessageBox("Execution Terminated.", "Program...", MB_OK);
}

void
TDlxFrameWindow::CmRunn()
{
  TRunNDlg::TDataBuff buff;
  strcpy(buff.szNumTicks, NumTicks->c_str());
  if((new TRunNDlg(this, & buff))->Execute() == IDOK) {
	 delete NumTicks;
	 NumTicks = new string(buff.szNumTicks);
	 Cpu.Runn(atol(NumTicks->c_str()));
    Invalidate();
	 MessageBox("Execution Terminated.", "Program...", MB_OK);
  }
}

void
TDlxFrameWindow::CmStep()
{
  Cpu.Step();
  ProgViewWindow->SetCurrentAddress(Cpu.GetCurrentAddress());
  Invalidate();
}

void
TDlxFrameWindow::CmExecStream()
{
  if(Cpu.IsExecStreamEnable()) {
	 ResetMenuItem(CM_VIEWEXEC_STREAM);
	 Cpu.DisableExecStream();
	 ExecWindow->Show(SW_HIDE);
	 Invalidate();
  }
  else {
	 SetMenuItem(CM_VIEWEXEC_STREAM);
	 Cpu.EnableExecStream();
	 ExecWindow->Show(SW_SHOW);
  }
}

void
TDlxFrameWindow::CmDispatchStream()
{
  if(Cpu.IsDispatchStreamEnable()) {
	 ResetMenuItem(CM_VIEWDISPATCH_STREAM);
	 Cpu.DisableDispatchStream();
	 DispatchWindow->Show(SW_HIDE);
	 Invalidate();
  }
  else {
	 SetMenuItem(CM_VIEWDISPATCH_STREAM);
	 Cpu.EnableDispatchStream();
	 DispatchWindow->Show(SW_SHOW);
  }
}

void
TDlxFrameWindow::CmProgView()
{
  if( IsMenuItemChecked(CM_VIEWPROGRAM) ) {
	 ResetMenuItem(CM_VIEWPROGRAM);
	 ProgViewWindow->Show(SW_HIDE);
	 Invalidate();
  }
  else {
	 SetMenuItem(CM_VIEWPROGRAM);
	 ProgViewWindow->Show(SW_SHOW);
  }
}

void
TDlxFrameWindow::CmMemoryView()
{
  if( IsMenuItemChecked(CM_VIEWMEMORY) ) {
	 ResetMenuItem(CM_VIEWMEMORY);
	 MemViewWindow->Show(SW_HIDE);
	 Invalidate();
  }
  else {
	 SetMenuItem(CM_VIEWMEMORY);
	 MemViewWindow->Show(SW_SHOW);
  }
}

void
TDlxFrameWindow::CmRegsView()
{
  if( IsMenuItemChecked(CM_VIEWGPR) ) {
	 ResetMenuItem(CM_VIEWREGS);
	 RegsViewWindow->Show(SW_HIDE);
	 Invalidate();
  }
  else {
	 SetMenuItem(CM_VIEWREGS);
	 RegsViewWindow->Show(SW_SHOW);
  }
}

void
TDlxFrameWindow::CmGprView()
{
  if( IsMenuItemChecked(CM_VIEWGPR) ) {
	 ResetMenuItem(CM_VIEWGPR);
	 GprViewWindow->Show(SW_HIDE);
	 Invalidate();
  }
  else {
	 SetMenuItem(CM_VIEWGPR);
	 GprViewWindow->Show(SW_SHOW);
  }
}

void
TDlxFrameWindow::CmFprView()
{
  if( IsMenuItemChecked(CM_VIEWFPR) ) {
	 ResetMenuItem(CM_VIEWFPR);
	 FprViewWindow->Show(SW_HIDE);
	 Invalidate();
  }
  else {
	 SetMenuItem(CM_VIEWFPR);
	 FprViewWindow->Show(SW_SHOW);
  }
}

void
TDlxFrameWindow::CmIQView()
{
  if( IsMenuItemChecked(CM_VIEWINSTRUCTION_QUEUE) ) {
	 ResetMenuItem(CM_VIEWINSTRUCTION_QUEUE);
	 IQViewWindow->Show(SW_HIDE);
	 Invalidate();
  }
  else {
	 SetMenuItem(CM_VIEWINSTRUCTION_QUEUE);
	 IQViewWindow->Show(SW_SHOW);
  }
}

void
TDlxFrameWindow::CmDisqView()
{
  if( IsMenuItemChecked(CM_VIEWDISPATCH_QUEUE) ) {
	 ResetMenuItem(CM_VIEWDISPATCH_QUEUE);
	 DisqViewWindow->Show(SW_HIDE);
	 Invalidate();
  }
  else {
	 SetMenuItem(CM_VIEWDISPATCH_QUEUE);
	 DisqViewWindow->Show(SW_SHOW);
  }
}

void
TDlxFrameWindow::CmROBView()
{
  if( IsMenuItemChecked(CM_VIEWREORDER_BUFFER) ) {
	 ResetMenuItem(CM_VIEWREORDER_BUFFER);
	 ROBViewWindow->Show(SW_HIDE);
	 Invalidate();
  }
  else {
	 SetMenuItem(CM_VIEWREORDER_BUFFER);
	 ROBViewWindow->Show(SW_SHOW);
  }
}

void
TDlxFrameWindow::CmBTBView()
{
  if( IsMenuItemChecked(CM_VIEWBRANCH_TARGET_BUFFER) ) {
	 ResetMenuItem(CM_VIEWBRANCH_TARGET_BUFFER);
	 BTBViewWindow->Show(SW_HIDE);
	 Invalidate();
  }
  else {
	 SetMenuItem(CM_VIEWBRANCH_TARGET_BUFFER);
	 BTBViewWindow->Show(SW_SHOW);
  }
}

void
TDlxFrameWindow::CmVUView()
{
  if( IsMenuItemChecked(CM_VIEWVIRTUAL_UNITS) ) {
	 ResetMenuItem(CM_VIEWVIRTUAL_UNITS);
	 VUViewWindow->Show(SW_HIDE);
	 Invalidate();
  }
  else {
	 SetMenuItem(CM_VIEWVIRTUAL_UNITS);
	 VUViewWindow->Show(SW_SHOW);
  }
}

void
TDlxFrameWindow::CmExecView()
{
  if( IsMenuItemChecked(CM_VIEWEXEC_UNITS) ) {
	 ResetMenuItem(CM_VIEWEXEC_UNITS);
	 ExecViewWindow->Show(SW_HIDE);
	 Invalidate();
  }
  else {
	 SetMenuItem(CM_VIEWEXEC_UNITS);
	 ExecViewWindow->Show(SW_SHOW);
  }
}

void
TDlxFrameWindow::CmCpuEscalar()
{
  ResetAllCpuMenuItem();
  SetMenuItem(CM_CPUESCALAR);
  Cpu.SetCpuType(ESCALAR);
  MessageBox("Escalar Algorithm Selected.", "Cpu Processor...", MB_OK);
}

void
TDlxFrameWindow::CmCpuPentium()
{
  ResetAllCpuMenuItem();
  SetMenuItem(CM_CPUPENTIUM);
  Cpu.SetCpuType(PENTIUM);
  MessageBox("Intel Pentium Algorithm Selected.", "Cpu Processor...", MB_OK);
}

void
TDlxFrameWindow::CmCpuPowerPC()
{
  ResetAllCpuMenuItem();
  SetMenuItem(CM_CPUPOWERPC);
  Cpu.SetCpuType(POWERPC);
  MessageBox("PowerPC 603 Algorithm Selected.", "Cpu Processor...", MB_OK);
}

void
TDlxFrameWindow::CmCpuAlpha()
{
  ResetAllCpuMenuItem();
  SetMenuItem(CM_CPUALPHA);
  Cpu.SetCpuType(ALPHA);
  MessageBox("Alpha AXP 21064 Algorithm Selected.", "Cpu Processor...", MB_OK);
}

void
TDlxFrameWindow::CmAbout()
{
  MessageBox("DLX Simulator\nby Luiz Marcio F A Viana\n12/7/96",
	 "About DLX...", MB_OK);
}

DEFINE_RESPONSE_TABLE1(TDlxFrameWindow, TFrameWindow)
  EV_COMMAND(CM_FILEOPEN, CmFileOpen),
  EV_COMMAND(CM_FILEEXIT, CmExit),
  EV_COMMAND(CM_VIEWEXEC_STREAM, CmExecStream),
  EV_COMMAND(CM_VIEWDISPATCH_STREAM, CmDispatchStream),
  EV_COMMAND(CM_VIEWPROGRAM, CmProgView),
  EV_COMMAND(CM_VIEWMEMORY, CmMemoryView),
  EV_COMMAND(CM_VIEWREGS, CmRegsView),
  EV_COMMAND(CM_VIEWGPR, CmGprView),
  EV_COMMAND(CM_VIEWFPR, CmFprView),
  EV_COMMAND(CM_VIEWINSTRUCTION_QUEUE, CmIQView),
  EV_COMMAND(CM_VIEWDISPATCH_QUEUE, CmDisqView),
  EV_COMMAND(CM_VIEWREORDER_BUFFER, CmROBView),
  EV_COMMAND(CM_VIEWBRANCH_TARGET_BUFFER, CmBTBView),
  EV_COMMAND(CM_VIEWVIRTUAL_UNITS, CmVUView),
  EV_COMMAND(CM_VIEWEXEC_UNITS, CmExecView),
  EV_COMMAND(CM_DEBUGRESET, CmReset),
  EV_COMMAND(CM_DEBUGRUN, CmRun),
  EV_COMMAND(CM_DEBUGRUNN, CmRunn),
  EV_COMMAND(CM_DEBUGSTEP, CmStep),
  EV_COMMAND(CM_CPUESCALAR, CmCpuEscalar),
  EV_COMMAND(CM_CPUPENTIUM, CmCpuPentium),
  EV_COMMAND(CM_CPUPOWERPC, CmCpuPowerPC),
  EV_COMMAND(CM_CPUALPHA, CmCpuAlpha),
  EV_COMMAND(CM_HELPABOUT, CmAbout),
END_RESPONSE_TABLE;

/* classe aplicativo windows
*/
void
TDlxAppl::InitMainWindow()
{
  MainWindow = new TDlxFrameWindow(0, "DLX Simulator");
  MainWindow->Attr.AccelTable = IDKEYB;
  MainWindow->SetIcon(this, IDICON);
}

/* implementacao da funcao OwlMain (principal)
*/

#pragma argsused

int
OwlMain(int argc, char* argv[])
{
  TDlxAppl app("DlxWinApp");
  return app.Run();
}

