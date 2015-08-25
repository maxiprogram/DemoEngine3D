#include "GRAPHIC.h"

GRAPHIC::GRAPHIC()
{
	direct=NULL;
	device=NULL;
	windowed=true;
}

GRAPHIC::GRAPHIC(HWND h)
{
	Init(h);
}

GRAPHIC::~GRAPHIC()
{
	if (device!=NULL)
		device->Release();
	if (direct!=NULL)
		direct->Release();
}

LPDIRECT3D9 GRAPHIC::GetDirect()
{return direct;}
LPDIRECT3DDEVICE9 GRAPHIC::GetDevice()
{return device;}
bool GRAPHIC::GetWindowed()
{return windowed;}
int GRAPHIC::GetWidth()
{return width;}
int GRAPHIC::GetHeigth()
{return heigth;}
D3DFORMAT GRAPHIC::GetBit()
{return pbit;}
bool GRAPHIC::GetZbuffer()
{return zbuffer;}


bool GRAPHIC::Init(HWND h)
{
	D3DDISPLAYMODE mode;
	hwnd=h;
	direct=Direct3DCreate9(D3D_SDK_VERSION);
	if (direct==NULL)
	{
		MessageBox(NULL,"Error DirectX!","Error!",MB_OK);
		return 0;
	}
	direct->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&mode);
	pbit=mode.Format;
	width=mode.Width;
	heigth=mode.Height;
	D3DPRESENT_PARAMETERS param;
	ZeroMemory(&param,sizeof(param));
	param.BackBufferWidth=width;
	param.BackBufferHeight=heigth;
	param.BackBufferFormat=pbit;
	param.SwapEffect=D3DSWAPEFFECT_DISCARD;
	param.Windowed=true;
	param.AutoDepthStencilFormat=D3DFMT_D16;
	param.EnableAutoDepthStencil=true;

	direct->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&param,&device);
	if (device==NULL)
	{
		MessageBox(NULL,"Error Device!","Error!",MB_OK);
		return 0;
	}
	device->SetRenderState(D3DRS_ZENABLE,true);
	device->SetRenderState(D3DRS_LIGHTING,false);
	SetPerspective();
	return 1;
}

bool GRAPHIC::SetMode(HWND h,bool win,int width,int heigth,D3DFORMAT b,bool zbuf)
{
	hwnd=h;
	windowed=win;
	pbit=b;
	zbuffer=zbuf;
	D3DPRESENT_PARAMETERS param;
	ZeroMemory(&param,sizeof(param));
	if (windowed)
	{
		param.BackBufferWidth=width;
		param.BackBufferHeight=heigth;
		param.BackBufferFormat=pbit;
		param.Windowed=windowed;
		param.SwapEffect=D3DSWAPEFFECT_DISCARD;
		param.AutoDepthStencilFormat=D3DFMT_D16;
		param.EnableAutoDepthStencil=zbuffer;
		device->SetRenderState(D3DRS_ZENABLE,zbuffer);
	}
	else
	{
		param.BackBufferWidth=width;
		param.BackBufferHeight=heigth;
		param.BackBufferFormat=pbit;
		param.Windowed=windowed;
		param.SwapEffect=D3DSWAPEFFECT_DISCARD;
		param.FullScreen_RefreshRateInHz=D3DPRESENT_RATE_DEFAULT;
		param.PresentationInterval=D3DPRESENT_INTERVAL_DEFAULT;
		param.AutoDepthStencilFormat=D3DFMT_D16;
		param.EnableAutoDepthStencil=zbuffer;
		device->SetRenderState(D3DRS_ZENABLE,zbuffer);
	}
	device->Reset(&param);
	device->SetRenderState(D3DRS_LIGHTING,false);
	SetPerspective();
	return 1;
}

void GRAPHIC::Begin()
{device->BeginScene();}

void GRAPHIC::End()
{device->EndScene();}

void GRAPHIC::Clear(unsigned long color)
{
	if (zbuffer)
		device->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,color,1.0f,NULL);
	else
		device->Clear(0,NULL,D3DCLEAR_TARGET,color,1.0f,NULL);
}

void GRAPHIC::Display()
{device->Present(NULL,NULL,NULL,NULL);}

void GRAPHIC::SetPerspective(float f,float a,float n,float fr)
{
	D3DXMATRIX mat;
	D3DXMatrixPerspectiveFovLH(&mat,f,a,n,fr);
	device->SetTransform(D3DTS_PROJECTION,&mat);
}

void GRAPHIC::SetTexture(unsigned char number,TEXTURE* texture)
{
	device->SetTexture(number,texture->GetTexture());
}

void GRAPHIC::SetMaterial(MATERIAL* material)
{
	device->SetMaterial(material->GetMaterial());
}

void GRAPHIC::SetLight(unsigned char number,LIGHT* light)
{
	device->SetLight(number,light->GetLight());
}

void GRAPHIC::EnableLight(unsigned char number,bool b)
{
	device->LightEnable(number,b);
}