#pragma once

class CAMERA:public MANIPULATEPASSIVE
{
private:
LPDIRECT3DDEVICE9 device;
public:
CAMERA();
~CAMERA();
void SetDevice(LPDIRECT3DDEVICE9 device);
void Apply();
};
