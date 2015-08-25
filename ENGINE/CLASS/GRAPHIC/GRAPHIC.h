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
//������ �����������
GRAPHIC();
//����������� � ����������: hwnd - ���������� ����
GRAPHIC(HWND hwnd);
//����������
~GRAPHIC();
//���������� directx
LPDIRECT3D9 GetDirect();
//���������� device ����������
LPDIRECT3DDEVICE9 GetDevice();
//���������� �����: true - �������, false - �������������
bool GetWindowed();
//���������� ������ device
int GetWidth();
//���������� ������ device
int GetHeigth();
//���������� ������� device
D3DFORMAT GetBit();
//���������� �����: true - ������ zbuffer, false - �������� zbuffer
bool GetZbuffer();
//������������� directx: hwnd - ���������� ����
bool Init(HWND hwnd);
//��������� ������: hwnd - ���������� ����, windowed - ������� �����, width - ������ device, heigth - ������ device, bitformat - �������, zbuffer - z-������
bool SetMode(HWND hwnd,bool windowed,int width,int heigth,D3DFORMAT bitformat,bool zbuffer);
//������ ��������
void Begin();
//��������� ��������
void End();
//������� �����: color - ���� �������
void Clear(unsigned long color=0x00000000);
//����� �����
void Display();
//����� ��������: number - ����� ��������, texture - ����� �������� 
void SetTexture(unsigned char number,TEXTURE* texture);
//����� ��������: material - ����� ��������� 
void SetMaterial(MATERIAL* material);
//����� ����: number - ����� �����, light - ����� ����� 
void SetLight(unsigned char number,LIGHT* light);
//��������� �����: number - ����� �����, b - ��������
void EnableLight(unsigned char number,bool b);
//
void SetPerspective(float fov=D3DX_PI/4,float aspect=1.3333f,float near=1.0f,float far=10000.0f);
};
