#pragma once

class FORM
{
private:
HINSTANCE hinst;
HWND hwnd;
WNDCLASS wnd;
MSG msg;
static LRESULT CALLBACK Func(HWND h,UINT msg,WPARAM wp,LPARAM lp);
public:
//������ �����������
FORM();
//����������� � ����������: handle - ���������� ����������
FORM(HINSTANCE handle);
//����������
~FORM();
//���������� ���������� ����
HWND GetHwnd();
//���������� ���������� ����������
HINSTANCE GetHinst();
//������� ����: handle - ���������� ����������, width - ������ ����, heigth - ������ ����
void CreateForm(HINSTANCE handle,int width=800,int heigth=400);
//������ ����: render - ������� ����������
void Run(void (*render)(void)=NULL);
};
