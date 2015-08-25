#pragma once

class LIGHT
{
private:
D3DLIGHT9 light;
public:
LIGHT();
~LIGHT();
D3DLIGHT9* GetLight();
void SetType(D3DLIGHTTYPE type);
void SetPosition(float x,float y,float z);
void Move(float x,float y,float z);
void SetPoint(float x,float y,float z);
void MovePoint(float x,float y,float z);
void SetAmbientColor(D3DXCOLOR color);
void SetDiffuseColor(D3DXCOLOR color);
void SetSpecularColor(D3DXCOLOR color);
void SetRange(float range);
void GetPosition(D3DXVECTOR3* pos);
void GetPoint(D3DXVECTOR3* point);
void GetAmbientColor(D3DXCOLOR* color);
void GetDiffuseColor(D3DXCOLOR* color);
void GetSpecularColor(D3DXCOLOR* color);
void GetRange(float* range);
};
