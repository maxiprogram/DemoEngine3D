#include "VERTEXBUFFER.h"

VERTEXBUFFER::VERTEXBUFFER()
{
}

VERTEXBUFFER::~VERTEXBUFFER()
{
if (vertexbuffer!=NULL)
vertexbuffer->Release();
}

void VERTEXBUFFER::Create(GRAPHIC* g,unsigned long vcol,unsigned long size,unsigned long fv)
{
graphic=g;
fvf=fv;
vertexsize=size;
vertexcount=vcol;
LPDIRECT3DDEVICE9 device=graphic->GetDevice();
device->CreateVertexBuffer(vertexcount*vertexsize,0,fvf,D3DPOOL_DEFAULT,&vertexbuffer,NULL);
}

void VERTEXBUFFER::Set(void* data)
{
void *temp;
vertexbuffer->Lock(0,vertexcount*vertexsize,(void**)&temp,0);
memcpy(temp,data,vertexcount*vertexsize);
vertexbuffer->Unlock();
}

void VERTEXBUFFER::Render(D3DPRIMITIVETYPE type, unsigned long col)
{
LPDIRECT3DDEVICE9 device=graphic->GetDevice();
device->SetStreamSource(0,vertexbuffer,0,vertexsize);
device->SetFVF(fvf);
device->DrawPrimitive(type,0,col);
}