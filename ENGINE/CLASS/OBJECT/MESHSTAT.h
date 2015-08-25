#pragma once

struct vertex
{
float x,y,z;
float nx,ny,nz;
float tx,ty;
};

class MESHSTAT
{
private:
LPDIRECT3DDEVICE9 device;
unsigned long meshcount;
char name[255];
LPDIRECT3DVERTEXBUFFER9 buffer;
LPDIRECT3DINDEXBUFFER9 index;
unsigned long* attribute;
unsigned long countvertex;
unsigned long countface;
D3DMATERIAL9* masmaterial;
LPDIRECT3DTEXTURE9* mastexture;
float m_radius;
public:
MESHSTAT();
~MESHSTAT();
void SetDevice(LPDIRECT3DDEVICE9 dev);
int LoadStat(char* filename);
void Render(unsigned long isubset=0);
char* GetName();
LPDIRECT3DDEVICE9 GetDevice();
float GetRadius();
};