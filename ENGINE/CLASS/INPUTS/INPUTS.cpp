#include "INPUTS.h"

INPUTS::INPUTS()
{
input=NULL;
keyboard=NULL;
}

INPUTS::~INPUTS()
{
keyboard->Unacquire();
if (keyboard!=NULL)
keyboard->Release();
if (input!=NULL)
input->Release();
}

bool INPUTS::Init(HINSTANCE handle,HWND hwnd)
{
DirectInput8Create(handle,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&input,NULL);
if (input==NULL)
{
MessageBoxW(NULL,L"Error CreateInput!",L"Error!",MB_OK);
return 0;
}
input->CreateDevice(GUID_SysKeyboard,&keyboard,NULL);
if (keyboard==NULL)
{
MessageBoxW(NULL,L"Error CreateKeyboard!",L"Error!",MB_OK);
return 0;
}
keyboard->SetDataFormat(&c_dfDIKeyboard);
keyboard->SetCooperativeLevel(hwnd,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
keyboard->Acquire();
return 1;
}

bool INPUTS::ReadKey(unsigned char dik_key)
{
keyboard->Acquire();
ZeroMemory(&Keys,sizeof(Keys));
keyboard->GetDeviceState(sizeof(Keys),(void**)&Keys);

bool c=(1==1)?false:true;
bool b=(Keys[dik_key])?true:false;
return b;
}