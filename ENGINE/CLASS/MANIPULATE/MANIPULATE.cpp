#include "MANIPULATE.h"

MANIPULATE::MANIPULATE()
{
	pos.x=0.0f;
	pos.y=0.0f;
	pos.z=0.0f;
	right.x=1.0f;
	right.y=0.0f;
	right.z=0.0f;
	look.x=0.0f;
	look.y=0.0f;
	look.z=1.0f;
	up.x=0.0f;
	up.y=1.0f;
	up.z=0.0f;
}

void MANIPULATE::SetPosition(float x,float y,float z)
{
	pos.x=x;
	pos.y=y;
	pos.z=z;
}

void MANIPULATE::SetRotation(float x,float y,float z)
{
	D3DXMATRIX matx,maty,matz,res;
	D3DXMatrixRotationX(&matx,x/180.0f*D3DX_PI);
	D3DXMatrixRotationY(&maty,y/180.0f*D3DX_PI);
	D3DXMatrixRotationZ(&matz,z/180.0f*D3DX_PI);
	D3DXMatrixIdentity(&res);
	res=matx*maty*matz;
	
	right.x=res._11;
	right.y=res._21;
	right.z=res._31;

	up.x=res._12;
	up.y=res._22;
	up.z=res._32;

	look.x=res._13;
	look.y=res._23;
	look.z=res._33;
}

void MANIPULATE::Scaling(float x,float y,float z)
{
	right.x*=x;
	up.y*=y;
	look.z*=z;
}

D3DXVECTOR3 MANIPULATE::GetPosition()
{
	return pos;
}

void MANIPULATEACTIVE::UpdateMatrix()
{
	D3DXVec3Normalize(&look,&look);
    D3DXVec3Cross(&up,&look,&right);
    D3DXVec3Normalize(&up,&up);
    D3DXVec3Cross(&right,&up,&look);
	D3DXVec3Normalize(&right,&right);

	matrix._11=right.x;
	matrix._12=up.x;
	matrix._13=look.x;
	matrix._14=0.0f;
	
	matrix._21=right.y;
	matrix._22=up.y;
	matrix._23=look.y;
	matrix._24=0.0f;
	
	matrix._31=right.z;
	matrix._32=up.z;
	matrix._33=look.z;
	matrix._34=0.0f;

	matrix._41=pos.x;
	matrix._42=pos.y;
	matrix._43=pos.z;
	matrix._44=1.0f;
}

void MANIPULATEACTIVE::Move(float x,float y,float z)
{
	pos.x+=x;
	pos.y+=y;
	pos.z+=z;
}

void MANIPULATEACTIVE::Rotation(float x,float y,float z)
{
	D3DXMATRIX tmp;
	D3DXMatrixRotationAxis(&tmp,&right,x/180.0f*D3DX_PI);
	D3DXVec3TransformCoord(&up,&up,&tmp);
	D3DXVec3TransformCoord(&look,&look,&tmp);

	D3DXMatrixRotationAxis(&tmp,&up,y/180.0f*D3DX_PI);
	D3DXVec3TransformCoord(&right,&right,&tmp);
	D3DXVec3TransformCoord(&look,&look,&tmp);

	D3DXMatrixRotationAxis(&tmp,&look,z/180.0f*D3DX_PI);
	D3DXVec3TransformCoord(&right,&right,&tmp);
	D3DXVec3TransformCoord(&up,&up,&tmp);
}

void MANIPULATEPASSIVE::UpdateMatrix()
{
	D3DXVec3Normalize(&look,&look);
    D3DXVec3Cross(&up,&look,&right);
    D3DXVec3Normalize(&up,&up);
    D3DXVec3Cross(&right,&up,&look);
	D3DXVec3Normalize(&right,&right);

	float x=-D3DXVec3Dot(&right,&pos);
	float y=-D3DXVec3Dot(&up,&pos);
	float z=-D3DXVec3Dot(&look,&pos);

	matrix._11=right.x;
	matrix._12=up.x;
	matrix._13=look.x;
	matrix._14=0.0f;
	
	matrix._21=right.y;
	matrix._22=up.y;
	matrix._23=look.y;
	matrix._24=0.0f;
	
	matrix._31=right.z;
	matrix._32=up.z;
	matrix._33=look.z;
	matrix._34=0.0f;

	matrix._41=x;
	matrix._42=y;
	matrix._43=z;
	matrix._44=1.0f;
}


void MANIPULATEPASSIVE::Move(float x,float y,float z)
{
	pos+=D3DXVECTOR3(look.x,0.0f,look.z)*z;
	pos+=D3DXVECTOR3(right.x,0.0f,right.z)*x;
	pos+=up*y;
}

void MANIPULATEPASSIVE::Rotation(float x,float y,float z)
{
	D3DXMATRIX tmp;
	D3DXMatrixRotationAxis(&tmp,&right,x/180.0f*D3DX_PI);
	D3DXVec3TransformCoord(&up,&up,&tmp);
	D3DXVec3TransformCoord(&look,&look,&tmp);

	D3DXMatrixRotationY(&tmp,y/180.0f*D3DX_PI);
	D3DXVec3TransformCoord(&right,&right,&tmp);
	D3DXVec3TransformCoord(&look,&look,&tmp);

	D3DXMatrixRotationAxis(&tmp,&look,z/180.0f*D3DX_PI);
	D3DXVec3TransformCoord(&right,&right,&tmp);
	D3DXVec3TransformCoord(&up,&up,&tmp);
}