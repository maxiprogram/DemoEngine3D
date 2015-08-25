#include "CAMERA.h"

CAMERA::CAMERA()
{
	device=NULL;
}

CAMERA::~CAMERA(){}

void CAMERA::SetDevice(LPDIRECT3DDEVICE9 dev)
{
	device=dev;
}

void CAMERA::Apply()
{
	UpdateMatrix();
	device->SetTransform(D3DTS_VIEW,&matrix);
}