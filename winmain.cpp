#include "ENGINE/ENGINE.h"

FORM forma;
GRAPHIC graphic;
INPUTS keyboard;
CAMERA camera;
OBJECTSTAT objectstat;
OBJECTSTAT obj2;
OBJECTANIM anim;
LIGHT light;
FONT font;

void Render();
bool collise(D3DXVECTOR3);

int __stdcall WinMain(HINSTANCE h,HINSTANCE hi,LPSTR l,int cmd)
{
	forma.CreateForm(h);
	graphic.Init(forma.GetHwnd());
	int bl=MessageBoxA(forma.GetHwnd(),"На весь экран?","Выбор режима",MB_YESNO);
	if (bl==IDNO)
		graphic.SetMode(forma.GetHwnd(),true,graphic.GetWidth(),graphic.GetHeigth(),graphic.GetBit(),true);
	else
		graphic.SetMode(forma.GetHwnd(),false,graphic.GetWidth(),graphic.GetHeigth(),graphic.GetBit(),true);
	keyboard.Init(h,forma.GetHwnd());
	font.Create(graphic.GetDevice());
	camera.SetDevice(graphic.GetDevice());
	camera.SetPosition(0.0,5.0,0.0);
	objectstat.LoadStat(graphic.GetDevice(),"model\\demo.stat");
	objectstat.SetPosition(0.0,0.0,0.0);
	obj2.LoadStat(graphic.GetDevice(),"model\\let.stat");
	obj2.SetPosition(-30,0,0);
	obj2.Rotation(0,180,0);
	anim.LoadAnim(graphic.GetDevice(),"model\\flag.anim");
	anim.SetPosition(25,-1,0);
	anim.Rotation(0,90,0);
	light.SetType(D3DLIGHT_POINT);
	//light.SetAmbientColor(D3DXCOLOR(1,1,1,1)*0.3f);
	//light.SetSpecularColor(D3DXCOLOR(1.0,1.0,1.0,1.0)*0.99f);
	light.SetPosition(0.0,90.0,0.0);
	light.SetRange(100.0f);
	graphic.SetLight(0,&light);
	graphic.EnableLight(0,true);

	LPDIRECT3DDEVICE9 dev=graphic.GetDevice();
	dev->SetRenderState(D3DRS_LIGHTING,true);
	dev->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);
	//dev->SetRenderState(D3DRS_SPECULARENABLE,true);

	forma.Run(&Render);
	return 0;
}

void Render()
{
	graphic.Clear();

	if (keyboard.ReadKey(DIK_ESCAPE))
		PostQuitMessage(0);
	if (keyboard.ReadKey(DIK_W))
	{
		camera.Move(0.0,0.0,0.3);
		if (collise(camera.GetPosition()))
			camera.Move(0.0,0.0,-0.3);
	}
	if (keyboard.ReadKey(DIK_S))
	{
		camera.Move(0.0,0.0,-0.3);
		if (collise(camera.GetPosition()))
			camera.Move(0.0,0.0,0.3);
	}
	if (keyboard.ReadKey(DIK_A))
	{
		camera.Move(-0.3,0.0,0.0);
		if (collise(camera.GetPosition()))
			camera.Move(0.3,0.0,0.0);
	}
	if (keyboard.ReadKey(DIK_D))
	{
		camera.Move(0.3,0.0,0.0);
		if (collise(camera.GetPosition()))
			camera.Move(-0.3,0.0,0.0);
	}
	if (keyboard.ReadKey(DIK_LEFT))
		camera.Rotation(0.0,-1.0,0.0);
	if (keyboard.ReadKey(DIK_RIGHT))
		camera.Rotation(0.0,1.0,0.0);
	if (keyboard.ReadKey(DIK_UP))
		camera.Rotation(-1.0,0.0,0.0);
	if (keyboard.ReadKey(DIK_DOWN))
		camera.Rotation(1.0,0.0,0.0);
	if (keyboard.ReadKey(DIK_Z))
		anim.Rotation(0,1,0);
	if (keyboard.ReadKey(DIK_X))
		anim.Rotation(0,-1,0);
	if (keyboard.ReadKey(DIK_C))
		obj2.Rotation(0,1,0);
	if (keyboard.ReadKey(DIK_V))
		obj2.Rotation(0,-1,0);

	camera.Apply();
	graphic.Begin();
	objectstat.Render();
	obj2.Render();
	anim.Render();
	font.PrintText("ESC - Выход\nW/S - Вперёд/Назад\nA/D - Влево/Вправо\nLeft/Right - Вращение Влево/Вправо\nUp/Down - Вращение Вверх/Вниз\nZ/X - Вращение флага\nC/V - Вращение самолёта\n",0,0);
	graphic.End();
	graphic.Display();
}

bool collise(D3DXVECTOR3 pos)
{
	bool b=false;
	if (pos.x>45 || pos.x<-45)
		b=true;
	if (pos.y>50 || pos.y<-50)
		b=true;
	if (pos.z>28 || pos.z<-28)
		b=true;
	return b;
}