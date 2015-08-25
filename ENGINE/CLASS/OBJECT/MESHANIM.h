#pragma once

class MESHANIM
{
private:
LPDIRECT3DDEVICE9 device;
unsigned long meshcount;
unsigned long keycount;
unsigned long fps;
char name[255];
LPDIRECT3DVERTEXBUFFER9* masbuffer;
LPDIRECT3DINDEXBUFFER9 index;
unsigned long* attribute;
unsigned long countvertex;
unsigned long countface;
D3DMATERIAL9* masmaterial;
LPDIRECT3DTEXTURE9* mastexture;
public:
MESHANIM();
~MESHANIM();
void SetDevice(LPDIRECT3DDEVICE9 dev);
int LoadAnim(char* filename);
void Render(unsigned int key);
unsigned long GetFps();
unsigned long GetMeshCount();
unsigned long GetKeyCount();
char* GetName();
LPDIRECT3DDEVICE9 GetDevice();
};