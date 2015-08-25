#pragma once
#include "../GRAPHIC/GRAPHIC.h"

class VERTEXBUFFER
{
private:
GRAPHIC* graphic;
LPDIRECT3DVERTEXBUFFER9 vertexbuffer;
unsigned long fvf;
unsigned long vertexsize;
unsigned long vertexcount;
public:
VERTEXBUFFER();
~VERTEXBUFFER();
void Create(GRAPHIC* graphic,unsigned long vertexcount,unsigned long vertexsize,unsigned long fvf);
void Set(void* vertexdata);
void Render(D3DPRIMITIVETYPE primitivetype,unsigned long primitivecount);
};
