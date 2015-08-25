#include "TEXTURE.h"

TEXTURE::TEXTURE()
{
	texture=NULL;
	device=NULL;
}

TEXTURE::TEXTURE(LPDIRECT3DDEVICE9 dev,char* filename)
{
	LoadTexture(dev,filename);
}

TEXTURE::~TEXTURE()
{
	if (texture)
		texture->Release();
}

LPDIRECT3DTEXTURE9 TEXTURE::GetTexture()
{return texture;}

void TEXTURE::LoadTexture(LPDIRECT3DDEVICE9 dev,char* filename)
{
	device=dev;
	D3DXCreateTextureFromFile(device,filename,&texture);
	if (texture==NULL)
		MessageBox(NULL,"Error LoadTexture!","Error!",MB_OK);
}