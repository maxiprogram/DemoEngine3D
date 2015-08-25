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
//Пустой конструктор
FORM();
//Конструктор с параметром: handle - дескриптор приложения
FORM(HINSTANCE handle);
//Деструктор
~FORM();
//Возвращает дескриптор окна
HWND GetHwnd();
//Возвращает дескриптор приложения
HINSTANCE GetHinst();
//Создает окно: handle - дескриптор приложения, width - ширина окна, heigth - высота окна
void CreateForm(HINSTANCE handle,int width=800,int heigth=400);
//Запуск окна: render - функция прорисовки
void Run(void (*render)(void)=NULL);
};
