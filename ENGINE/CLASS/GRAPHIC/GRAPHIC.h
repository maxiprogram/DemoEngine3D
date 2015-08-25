#pragma once

class GRAPHIC
{
private:
HWND hwnd;
LPDIRECT3D9 direct;
LPDIRECT3DDEVICE9 device;
int width;
int heigth;
D3DFORMAT pbit;
bool windowed;
bool zbuffer;
public:
//Пустой конструктор
GRAPHIC();
//Конструктор с параметром: hwnd - дескриптор окна
GRAPHIC(HWND hwnd);
//Деструктор
~GRAPHIC();
//Возвращает directx
LPDIRECT3D9 GetDirect();
//Возвращает device устройства
LPDIRECT3DDEVICE9 GetDevice();
//Возвращает режим: true - оконный, false - полноэкранный
bool GetWindowed();
//Возвращает ширину device
int GetWidth();
//Возвращает высоту device
int GetHeigth();
//Возвращает глубину device
D3DFORMAT GetBit();
//Возвращает режим: true - влючён zbuffer, false - выключен zbuffer
bool GetZbuffer();
//Инициализация directx: hwnd - дескриптор окна
bool Init(HWND hwnd);
//Установка режима: hwnd - дескриптор окна, windowed - оконный режим, width - ширина device, heigth - высота device, bitformat - глубина, zbuffer - z-буффер
bool SetMode(HWND hwnd,bool windowed,int width,int heigth,D3DFORMAT bitformat,bool zbuffer);
//Начать рисовать
void Begin();
//Закончить рисовать
void End();
//Очистка кадра: color - цвет очистки
void Clear(unsigned long color=0x00000000);
//Вывод кадра
void Display();
//Задаёт текстуру: number - номер текстуры, texture - класс текстуры 
void SetTexture(unsigned char number,TEXTURE* texture);
//Задаёт материал: material - класс материала 
void SetMaterial(MATERIAL* material);
//Задаёт свет: number - номер света, light - класс света 
void SetLight(unsigned char number,LIGHT* light);
//Включение света: number - номер света, b - включить
void EnableLight(unsigned char number,bool b);
//
void SetPerspective(float fov=D3DX_PI/4,float aspect=1.3333f,float near=1.0f,float far=10000.0f);
};
