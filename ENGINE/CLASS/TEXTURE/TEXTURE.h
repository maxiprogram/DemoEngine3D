#pragma once

class TEXTURE
{
private:
LPDIRECT3DDEVICE9 device;
LPDIRECT3DTEXTURE9 texture;
public:
//������ �����������
TEXTURE();
//����������� � �����������: device - ���������� ���������, filename - ���� � ��������
TEXTURE(LPDIRECT3DDEVICE9 device,char* filename);
//����������
~TEXTURE();
//���������� ��������
LPDIRECT3DTEXTURE9 GetTexture();
//�������� ��������: device - ���������� ���������, filename - ���� � ��������
void LoadTexture(LPDIRECT3DDEVICE9 device,char* filename);
};