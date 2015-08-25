#include "MATERIAL.h"

MATERIAL::MATERIAL()
{
	ZeroMemory(&material,sizeof(D3DMATERIAL9));
	material.Ambient=material.Diffuse=material.Specular=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
}

MATERIAL::~MATERIAL(){}

void MATERIAL::SetAmbientColor(D3DXCOLOR color)
{
	material.Ambient=color;
}

void MATERIAL::SetDiffuseColor(D3DXCOLOR color)
{
	material.Diffuse=color;
}

void MATERIAL::SetSpecularColor(D3DXCOLOR color)
{
	material.Specular=color;
}

void MATERIAL::SetEmissiveColor(D3DXCOLOR color)
{
	material.Emissive=color;
}

void MATERIAL::SetPower(float power)
{
	material.Power=power;
}

void MATERIAL::GetAmbientColor(D3DXCOLOR* color)
{
	memcpy(color,&material.Ambient,sizeof(D3DXCOLOR));
}

void MATERIAL::GetDiffuseColor(D3DXCOLOR* color)
{
	memcpy(color,&material.Diffuse,sizeof(D3DXCOLOR));
}

void MATERIAL::GetSpecularColor(D3DXCOLOR* color)
{
	memcpy(color,&material.Specular,sizeof(D3DXCOLOR));
}

void MATERIAL::GetEmissiveColor(D3DXCOLOR* color)
{
	memcpy(color,&material.Emissive,sizeof(D3DXCOLOR));
}

float MATERIAL::GetPower()
{
	return material.Power; 
}

D3DMATERIAL9* MATERIAL::GetMaterial()
{
	return &material;
}