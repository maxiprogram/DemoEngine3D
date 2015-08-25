#pragma once

class FONT
{
LPD3DXFONT font;
LPDIRECT3DDEVICE9 device;
public:
FONT();
~FONT();
bool Create(LPDIRECT3DDEVICE9 device,int size=16,int bold=500,bool italic=false,LPCWSTR style=L"Times New Roman");
void PrintText(LPCSTR text,long px,long py,D3DCOLOR color=0xffffffff);
};
