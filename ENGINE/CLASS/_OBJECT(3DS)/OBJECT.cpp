#include "OBJECT.h"

OBJECT::OBJECT()
{
mesh=NULL;
D3DXMatrixIdentity(&matrix);
D3DXMatrixIdentity(&rotate);
D3DXMatrixIdentity(&trans);
D3DXMatrixIdentity(&scale);
}

OBJECT::~OBJECT(void)
{
if (mesh!=NULL)
mesh->Release();
}

int OBJECT::Load(LPDIRECT3DDEVICE9 dev,char* filename)
{
device=dev;
struct _vertex 
{
float x,y,z;
float tv,tu;
};
_vertex* vertex;
unsigned short* index;

int i=0;
unsigned short count;
FILE* f=NULL;
fopen_s(&f,filename,"rb");
if (f==NULL)
{
MessageBox(NULL,L"Error Load!",L"Error!",MB_OK);
return 0;
}
fseek(f,0,SEEK_END);
long size=ftell(f);
fseek(f,0,SEEK_SET);
while (ftell(f)<size)
{
unsigned short chunk;
unsigned long chunk_length;
fread(&chunk,sizeof(chunk),1,f);
fread(&chunk_length,sizeof(chunk_length),1,f);
switch(chunk)
{
case 0x4d4d:
break;
case 0x3d3d:
break;

case 0x4000:
unsigned char buf;
do
{
fread(&buf,sizeof(buf),1,f);
name[i]=buf;
i++;
}while(buf!='\0' && i<20);
break;

case 0x4100:
break;

case 0x4110:
fread(&count,sizeof(count),1,f);
vertexcount=count;
vertex=new _vertex[vertexcount];
for (int i=0;i<vertexcount;i++)
{
fread(&vertex[i].x,sizeof(float),1,f);
fread(&vertex[i].z,sizeof(float),1,f);
fread(&vertex[i].y,sizeof(float),1,f);
}
break;

case 0x4120:
fread (&count,sizeof(count),1,f);
facecount=count;
index=new unsigned short[facecount*3];
for (int i=0;i<facecount*3;i+=3)
{
fread(&index[i],sizeof(unsigned short),1,f);
fread(&index[i+1],sizeof(unsigned short),1,f);
fread(&index[i+2],sizeof(unsigned short),1,f);
unsigned short flag;
fread(&flag,sizeof(unsigned short),1,f);
}
break;

case 0x4140:
fread (&count,sizeof(count),1,f);
for (int i=0;i<count;i++)
{
fread(&vertex[i].tv,sizeof(float),1,f);
fread(&vertex[i].tu,sizeof(float),1,f);
}
break;

default:
fseek(f,chunk_length-6,SEEK_CUR);
}//switch
}//while
fclose(f);

D3DXCreateMeshFVF(facecount,vertexcount,D3DXMESH_MANAGED,D3DFVF_XYZ | D3DFVF_TEX1,device,&mesh);
void* tmp;
mesh->LockVertexBuffer(0,(void**)&tmp);
memcpy(tmp,vertex,sizeof(_vertex)*vertexcount);
mesh->UnlockVertexBuffer();

void* ind;
mesh->LockIndexBuffer(0,(void**)&ind);
memcpy(ind,index,sizeof(unsigned short)*facecount*3);
mesh->UnlockIndexBuffer();
unsigned long* atr;
mesh->LockAttributeBuffer(0,&atr);
for (int i=0;i<facecount;i++)
atr[i]=0;
mesh->UnlockAttributeBuffer();

LPD3DXMESH tmpmesh;
mesh->CloneMeshFVF(D3DXMESH_MANAGED,mesh->GetFVF()|D3DFVF_NORMAL,device,&tmpmesh);
D3DXComputeNormals(tmpmesh,0);
mesh->Release();
mesh=tmpmesh;

delete [] vertex;
delete [] index;
return 1;
}

void OBJECT::Render()
{
device->SetTransform(D3DTS_WORLD,&matrix);
mesh->DrawSubset(0);
}

void OBJECT::SetPosition(float x,float y,float z)
{
D3DXMatrixTranslation(&trans,x,y,z);
matrix=rotate*trans;
}

void OBJECT::Move(float x,float y,float z)
{
D3DXMATRIX tmp;
D3DXMatrixTranslation(&tmp,x,y,z);
trans=trans*tmp;
matrix=rotate*trans;
}

void OBJECT::Rotate(float x,float y,float z)
{
D3DXMATRIX matx;
D3DXMATRIX maty;
D3DXMATRIX matz;
D3DXMatrixRotationX(&matx,x/180.0f*D3DX_PI);
D3DXMatrixRotationY(&maty,y/180.0f*D3DX_PI);
D3DXMatrixRotationZ(&matz,z/180.0f*D3DX_PI);
rotate=matx*maty*matz;
matrix=rotate*trans;
}


void OBJECT::Scale(float x,float y,float z)
{
D3DXMatrixScaling(&scale,x,y,z);
}

D3DXMATRIX OBJECT::GetMatrix()
{return matrix;}