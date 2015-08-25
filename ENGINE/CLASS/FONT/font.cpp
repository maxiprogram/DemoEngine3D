#include "FONT.h"

FONT::FONT()
{
font=NULL;
}
FONT::~FONT()
{
if (font!=NULL)
font->Release();
}

bool FONT::Create(LPDIRECT3DDEVICE9 dev,int s,int b,bool it,LPCWSTR st)
{
device=dev;
D3DXCreateFontW(device,25,12,b,0,it,DEFAULT_CHARSET,0,0,DEFAULT_PITCH | FF_MODERN,st,&font);
if (font==NULL)
{
MessageBoxW(NULL,L"Error CreateFont!",L"Error!",MB_OK);
return 0;
}
return 1;
}

void FONT::PrintText(LPCSTR text,long px,long py,D3DCOLOR col)
{
RECT rect;
rect.left=px;
rect.top=py;
rect.right=0;
rect.bottom=0;
font->DrawTextA(NULL,text,-1,&rect,DT_NOCLIP,col);
}