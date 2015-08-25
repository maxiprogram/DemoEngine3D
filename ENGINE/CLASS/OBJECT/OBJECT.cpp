#include "OBJECT.h"
#include "MESHSTAT.cpp"
#include "MESHANIM.cpp"

OBJECTSTAT::OBJECTSTAT()
{
	copy=false;
	mesh=NULL;
	pos.x=pos.y=pos.z=0;
	right.x=1;
	right.y=right.z=0;
	up.y=1;
	up.x=up.z=0;
	look.z=1;
	look.x=look.y=0;
}

OBJECTSTAT::OBJECTSTAT(LPDIRECT3DDEVICE9 device,char* filename)
{
	pos.x=pos.y=pos.z=0;
	right.x=1;
	right.y=right.z=0;
	up.y=1;
	up.x=up.z=0;
	look.z=1;
	look.x=look.y=0;
	copy=false;
	LoadStat(device,filename);
}

OBJECTSTAT::OBJECTSTAT(OBJECTSTAT* obj)
{
	CopyObject(obj);
}

OBJECTSTAT::~OBJECTSTAT()
{
	if (copy==false)
	{
		if (mesh!=NULL)
			delete mesh;
	}
}

float OBJECTSTAT::GetRadius()
{
	return mesh->GetRadius();
}

int OBJECTSTAT::LoadStat(LPDIRECT3DDEVICE9 device,char* filename)
{
	mesh=new MESHSTAT();
	mesh->SetDevice(device);
	return mesh->LoadStat(filename);
}

void OBJECTSTAT::Render(unsigned long subset)
{
	LPDIRECT3DDEVICE9 dev=mesh->GetDevice();
	D3DXMATRIX tmpmat;
	dev->GetTransform(D3DTS_WORLD,&tmpmat);
	UpdateMatrix();
	dev->SetTransform(D3DTS_WORLD,&matrix);
	mesh->Render(subset);
	dev->SetTransform(D3DTS_WORLD,&tmpmat);
}

char* OBJECTSTAT::GetName()
{
	return mesh->GetName();
}

MESHSTAT* OBJECTSTAT::GetMesh()
{
	return mesh;
}

void OBJECTSTAT::CopyObject(OBJECTSTAT* obj)
{
	mesh=obj->GetMesh();
	copy=true;
}

///////////////////////////////////////////////////////////////////////////////////////
OBJECTANIM::OBJECTANIM()
{
	meshanim=NULL;
	currentkey=0;
	play=true;
	replay=true;
	hthread=NULL;
}

OBJECTANIM::~OBJECTANIM()
{
	if (hthread!=NULL)
		CloseHandle(hthread);
	if (meshanim!=NULL)
		delete meshanim;
}

int OBJECTANIM::LoadAnim(LPDIRECT3DDEVICE9 device,char* filename)
{
	meshanim=new MESHANIM();
	meshanim->SetDevice(device);
	if (meshanim->LoadAnim(filename)==0)
		return 0;
	hthread=CreateThread(0,0,this->UpdateKey,this,0,0);
	if (hthread==NULL)
	{
		MessageBoxA(NULL,"Error Create Thread!","Error!",MB_OK);
		return 0;
	}

}

void OBJECTANIM::SetCurrentKey(unsigned long key)
{
	currentkey=key;
}

unsigned long OBJECTANIM::GetCurrentKey()
{
	return currentkey;
}

unsigned long OBJECTANIM::GetFps()
{
	return meshanim->GetFps();
}

unsigned long OBJECTANIM::GetKeyCount()
{
	return meshanim->GetKeyCount();
}

void OBJECTANIM::SetReplay(bool rep)
{
	replay=rep;
}
bool OBJECTANIM::GetReplay()
{
	return replay;
}

void OBJECTANIM::SetPlay(bool pl)
{
	play=pl;
}

bool OBJECTANIM::GetPlay()
{
	return play;
}

void OBJECTANIM::Render()
{
	LPDIRECT3DDEVICE9 dev=meshanim->GetDevice();
	D3DXMATRIX tmpmat;
	dev->GetTransform(D3DTS_WORLD,&tmpmat);
	UpdateMatrix();
	dev->SetTransform(D3DTS_WORLD,&matrix);
	meshanim->Render(currentkey);
	dev->SetTransform(D3DTS_WORLD,&tmpmat);
}

unsigned long __stdcall OBJECTANIM::UpdateKey(void* param)
{
	OBJECTANIM* pclass=(OBJECTANIM*)param;
	unsigned long fps=pclass->GetFps();
	fps=1000/fps;
	while (1)
	{
		if (pclass->GetPlay())
		{	
			Sleep(fps);
			if (pclass->GetCurrentKey()<pclass->GetKeyCount()-1)
				pclass->SetCurrentKey(pclass->GetCurrentKey()+1);
			else
				if (pclass->GetReplay())
					pclass->SetCurrentKey(0);
		}
	}
}