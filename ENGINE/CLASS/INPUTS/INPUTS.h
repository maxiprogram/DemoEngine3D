#pragma once

class INPUTS
{
private:
LPDIRECTINPUT8 input;
LPDIRECTINPUTDEVICE8 keyboard;
unsigned char Keys[256];
public:
INPUTS();
~INPUTS();
bool Init(HINSTANCE handle,HWND hwnd);
bool ReadKey(unsigned char dik_key);
};
