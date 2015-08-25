#include "MESHANIM.h"

MESHANIM::MESHANIM()
{
	device=NULL;
	masbuffer=NULL;
	index=NULL;
	attribute=NULL;
	masmaterial=NULL;
	mastexture=NULL;
}
MESHANIM::~MESHANIM()
{
	if (attribute!=NULL)
		delete[] attribute;
	if (index!=NULL)
		index->Release();
	if (masmaterial!=NULL)
		delete[] masmaterial;
	
	if (masbuffer!=NULL)
	{
		for (unsigned long i=0;i<meshcount;i++)
		{
			if (masbuffer[i]!=NULL)
				masbuffer[i]->Release();
		}
		delete[] masbuffer;
	}

	if (mastexture!=NULL)
	{
		for (unsigned long i=0;i<meshcount;i++)
		{
			if (mastexture[i]!=NULL)
				mastexture[i]->Release();
		}
	}
	
}

void MESHANIM::SetDevice(LPDIRECT3DDEVICE9 dev)
{
	device=dev;
}

LPDIRECT3DDEVICE9 MESHANIM::GetDevice()
{
	return device;
}

int MESHANIM::LoadAnim(char* filename)
{
	FILE* f=NULL;
	fopen_s(&f,filename,"rb");
	if (f==NULL)
	{
		MessageBoxW(NULL,L"Error Load!",L"Error!",MB_OK);
		return 0;
	}

	fread(&keycount,sizeof(unsigned long),1,f);
	fread(&fps,sizeof(unsigned long),1,f);
	fread(&meshcount,sizeof(unsigned long),1,f);
	int i=0;
	fread(&name[i],sizeof(char),1,f);
	while(name[i]!=0)
	{
		i++;
		fread(&name[i],sizeof(char),1,f);
	}

	masmaterial=new D3DMATERIAL9[meshcount];
	mastexture=new LPDIRECT3DTEXTURE9[meshcount];
	
	fread(&countface,sizeof(unsigned long),1,f);
	unsigned long* masindex=new unsigned long[countface*3];
	attribute=new unsigned long[countface*3];

	for (unsigned long i=0;i<countface*3;i++)
		fread(&masindex[i],sizeof(unsigned long),1,f);

	for (unsigned long i=0;i<countface*3;i++)
		fread(&attribute[i],sizeof(unsigned long),1,f);

	device->CreateIndexBuffer(countface*3*sizeof(unsigned long),0,D3DFMT_INDEX32,D3DPOOL_MANAGED,&index,0);
	void* tmp;
	index->Lock(0,countface*3*sizeof(unsigned long),(void**)&tmp,0);
	memcpy(tmp,masindex,countface*3*sizeof(unsigned long));
	index->Unlock();
	delete[] masindex;

	for (unsigned long imesh=0;imesh<meshcount;imesh++)
	{
		unsigned char bbuf;
		ZeroMemory(&masmaterial[imesh],sizeof(D3DMATERIAL9));
		fread(&bbuf,sizeof(unsigned char),1,f);
		masmaterial[imesh].Ambient.a=(float)bbuf/255.0f;
		fread(&bbuf,sizeof(unsigned char),1,f);
		masmaterial[imesh].Ambient.r=(float)bbuf/255.0f;
		fread(&bbuf,sizeof(unsigned char),1,f);
		masmaterial[imesh].Ambient.g=(float)bbuf/255.0f;
		fread(&bbuf,sizeof(unsigned char),1,f);
		masmaterial[imesh].Ambient.b=(float)bbuf/255.0f;

		fread(&bbuf,sizeof(unsigned char),1,f);
		masmaterial[imesh].Diffuse.a=(float)bbuf/255.0f;
		fread(&bbuf,sizeof(unsigned char),1,f);
		masmaterial[imesh].Diffuse.r=(float)bbuf/255.0f;
		fread(&bbuf,sizeof(unsigned char),1,f);
		masmaterial[imesh].Diffuse.g=(float)bbuf/255.0f;
		fread(&bbuf,sizeof(unsigned char),1,f);
		masmaterial[imesh].Diffuse.b=(float)bbuf/255.0f;

		fread(&bbuf,sizeof(unsigned char),1,f);
		masmaterial[imesh].Specular.a=(float)bbuf/255.0f;
		fread(&bbuf,sizeof(unsigned char),1,f);
		masmaterial[imesh].Specular.r=(float)bbuf/255.0f;
		fread(&bbuf,sizeof(unsigned char),1,f);
		masmaterial[imesh].Specular.g=(float)bbuf/255.0f;
		fread(&bbuf,sizeof(unsigned char),1,f);
		masmaterial[imesh].Specular.b=(float)bbuf/255.0f;

		char path[255];
		fread(&path[0],sizeof(unsigned char),1,f);
		if (path[0]!=0)
		{
			int j=0;
			while (path[j]!=0)
			{
				j++;
				fread(&path[j],sizeof(unsigned char),1,f);
			}
			char buf[1024]="textures\\";
			strcat_s(buf,1024,path);
			D3DXCreateTextureFromFileA(device,buf,&mastexture[imesh]);
		}else
			mastexture[imesh]=NULL;
	}

	masbuffer=new LPDIRECT3DVERTEXBUFFER9[keycount];
	fread(&countvertex,sizeof(unsigned long),1,f);
	vertex* masvertex=new vertex[countvertex];

	for (unsigned long ikey=0;ikey<keycount;ikey++)
	{
		device->CreateVertexBuffer(countvertex*sizeof(vertex),0,D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1,D3DPOOL_MANAGED,&masbuffer[ikey],0);
		for (unsigned long i=0;i<countvertex;i++)
		{
			fread(&masvertex[i].x,sizeof(float),1,f);
			fread(&masvertex[i].y,sizeof(float),1,f);
			fread(&masvertex[i].z,sizeof(float),1,f);
			fread(&masvertex[i].nx,sizeof(float),1,f);
			fread(&masvertex[i].ny,sizeof(float),1,f);
			fread(&masvertex[i].nz,sizeof(float),1,f);
			fread(&masvertex[i].tx,sizeof(float),1,f);
			fread(&masvertex[i].ty,sizeof(float),1,f);
		}
		void* tmp;
		masbuffer[ikey]->Lock(0,countvertex*sizeof(vertex),(void**)&tmp,0);
		memcpy(tmp,masvertex,countvertex*sizeof(vertex));
		masbuffer[ikey]->Unlock();
	}

	delete[] masvertex;

	fclose(f);
	return 1;
}

void MESHANIM::Render(unsigned int key)
{
	D3DMATERIAL9 tmpmat;
	LPDIRECT3DBASETEXTURE9 tmptex;
	device->GetMaterial(&tmpmat);
	device->GetTexture(0,&tmptex);

	device->SetStreamSource(0,masbuffer[key],0,sizeof(vertex));
	device->SetFVF(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1);
	device->SetIndices(index);

	unsigned long start=0;
	unsigned long colver=0;
	for (unsigned long subset=0;subset<meshcount;subset++)
	{
		for (unsigned long i=start;i<countface*3;i++)
		{
			if (attribute[i]!=subset)
			{
				break;
			}
			else
				colver++;
		}
		device->SetMaterial(&masmaterial[subset]);
		device->SetTexture(0,mastexture[subset]);
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,colver,start,colver/3);
		start+=colver;
		colver=0;
	}
	
	device->SetMaterial(&tmpmat);
	device->SetTexture(0,tmptex);
}

unsigned long MESHANIM::GetFps()
{
	return fps;
}
unsigned long MESHANIM::GetMeshCount()
{
	return meshcount;
}
unsigned long MESHANIM::GetKeyCount()
{
	return keycount;
}

char* MESHANIM::GetName()
{
	return name;
}