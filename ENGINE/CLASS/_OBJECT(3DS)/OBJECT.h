#pragma once

class OBJECT
{
private:
LPDIRECT3DDEVICE9 device;
char name[20];
LPD3DXMESH mesh;
unsigned short vertexcount;
unsigned short facecount;
D3DXMATRIX matrix;
D3DXMATRIX trans;
D3DXMATRIX rotate;
D3DXMATRIX scale;
public:
OBJECT();
~OBJECT();
void SetPosition(float x,float y,float z);
void Move(float x,float y,float z);
void Rotate(float x,float y,float z);
void Scale(float x,float y,float z);
int Load(LPDIRECT3DDEVICE9 device,char* filename);
void Render();
D3DXMATRIX GetMatrix();
};
