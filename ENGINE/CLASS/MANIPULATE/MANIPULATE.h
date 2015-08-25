#pragma once

class MANIPULATE
{
protected:
D3DXVECTOR3 pos;
D3DXVECTOR3 right;
D3DXVECTOR3 up;
D3DXVECTOR3 look;
D3DXMATRIX matrix;
virtual void UpdateMatrix()=0;
public:
MANIPULATE();
void SetPosition(float x,float y,float z);
virtual void Move(float x,float y,float z)=0;
void SetRotation(float x,float y,float z);
virtual void Rotation(float x,float y,float z)=0;
void Scaling(float x,float y,float z);
D3DXVECTOR3 GetPosition();
};

class MANIPULATEACTIVE:public MANIPULATE
{
protected:
void UpdateMatrix();
public:
void Move(float x,float y,float z);
void Rotation(float x,float y,float z);
};

class MANIPULATEPASSIVE:public MANIPULATE
{
protected:
void UpdateMatrix();
public:
void Move(float x,float y,float z);
void Rotation(float x,float y,float z);
};