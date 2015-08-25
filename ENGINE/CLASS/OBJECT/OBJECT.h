#pragma once

#include "MESHSTAT.h"
#include "MESHANIM.h"

class OBJECTSTAT:public MANIPULATEACTIVE
{
private:
MESHSTAT* mesh;
bool copy;
public:
OBJECTSTAT();
OBJECTSTAT(LPDIRECT3DDEVICE9 device,char* filename);
OBJECTSTAT(OBJECTSTAT* obj);
~OBJECTSTAT();
int LoadStat(LPDIRECT3DDEVICE9 device,char* filename);
void Render(unsigned long subset=0);
char* GetName();
MESHSTAT* GetMesh();
void CopyObject(OBJECTSTAT* obj);
float GetRadius();
};

///////////////////////////////////////////////////////////////////////////
class OBJECTANIM:public MANIPULATEACTIVE
{
private:
MESHANIM* meshanim;
unsigned long currentkey;
bool play;
bool replay;
HANDLE hthread;
static unsigned long __stdcall UpdateKey(void* param);
public:
OBJECTANIM();
~OBJECTANIM();
int LoadAnim(LPDIRECT3DDEVICE9 device,char* filename);
void Render();
void SetCurrentKey(unsigned long key);
unsigned long GetCurrentKey();
unsigned long GetFps();
unsigned long GetKeyCount();
void SetReplay(bool replay);
bool GetReplay();
void SetPlay(bool play);
bool GetPlay();
};