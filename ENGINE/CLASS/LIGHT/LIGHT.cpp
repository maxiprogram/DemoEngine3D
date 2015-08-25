#include "LIGHT.h"

LIGHT::LIGHT()
{
ZeroMemory(&light,sizeof(D3DLIGHT9));
light.Type=D3DLIGHT_DIRECTIONAL;
light.Ambient=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
light.Diffuse=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
light.Specular=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
light.Range=100.0f;
light.Direction=D3DXVECTOR3(0.0f,0.0f,1.0f);
D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction,(D3DXVECTOR3*)&light.Direction);
}

LIGHT::~LIGHT(){}

void LIGHT::SetType(D3DLIGHTTYPE type)
{
light.Type=type;
}

void LIGHT::SetPosition(float x,float y,float z)
{
light.Position.x=x;
light.Position.y=y;
light.Position.z=z;
}

void LIGHT::Move(float x,float y,float z)
{
light.Position.x+=x;
light.Position.y+=y;
light.Position.z+=z;
}

void LIGHT::SetPoint(float x,float y,float z)
{
light.Direction.x=x;
light.Direction.y=y;
light.Direction.z=z;
D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction,(D3DXVECTOR3*)&light.Direction);
}

void LIGHT::MovePoint(float x,float y,float z)
{
light.Direction.x+=x;
light.Direction.y+=y;
light.Direction.z+=z;
D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction,(D3DXVECTOR3*)&light.Direction);
}

void LIGHT::GetPosition(D3DXVECTOR3* position)
{
*position=light.Position;
}

void LIGHT::GetPoint(D3DXVECTOR3* point)
{
*point=light.Direction;
}

void LIGHT::SetAmbientColor(D3DXCOLOR color)
{
light.Ambient=color;
}

void LIGHT::SetDiffuseColor(D3DXCOLOR color)
{
light.Diffuse=color;
}

void LIGHT::SetSpecularColor(D3DXCOLOR color)
{
light.Specular=color;
}

void LIGHT::GetAmbientColor(D3DXCOLOR* color)
{
*color=light.Ambient;
}

void LIGHT::GetDiffuseColor(D3DXCOLOR* color)
{
*color=light.Diffuse;
}

void LIGHT::GetSpecularColor(D3DXCOLOR* color)
{
*color=light.Specular;
}

void LIGHT::SetRange(float range)
{
light.Range=range;
}

void LIGHT::GetRange(float* range)
{
*range=light.Range;
}

D3DLIGHT9* LIGHT::GetLight()
{
return &light;
}