#include "FORM.h"

FORM::FORM(){}
FORM::~FORM(){};
FORM::FORM(HINSTANCE h)
{
	CreateForm(h);
}

LRESULT CALLBACK FORM::Func(HWND h,UINT msg,WPARAM wp,LPARAM lp)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(h,msg,wp,lp);
}

void FORM::CreateForm(HINSTANCE h,int width,int heigth)
{
	hinst=h;
	wnd.cbClsExtra=0;
	wnd.cbWndExtra=0;
	wnd.hbrBackground=(HBRUSH)GRAY_BRUSH;
	wnd.hCursor=LoadCursor(NULL,IDC_ARROW);
	wnd.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wnd.hInstance=hinst;
	wnd.lpfnWndProc=Func;
	wnd.lpszClassName="myclass";
	wnd.lpszMenuName=NULL;
	wnd.style=CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	if (!RegisterClass(&wnd))
		MessageBox(NULL,"Error RegisterClass!","Error!",MB_OK);

	hwnd=CreateWindow("myclass","CAPTION",WS_OVERLAPPEDWINDOW,300,200,width,heigth,NULL,NULL,hinst,NULL);
	if (!hwnd)
		MessageBox(NULL,"Error CreateWindow!","Error!",MB_OK);

	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
}

HWND FORM::GetHwnd()
{
	return hwnd;
}

HINSTANCE FORM::GetHinst()
{
	return hinst;
}

void FORM::Run(void (*render) (void))
{
	while (msg.message!=WM_QUIT)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)!=0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (render!=NULL)
				render();
		}
	}
}