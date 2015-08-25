#pragma once

class TEXTURE
{
private:
LPDIRECT3DDEVICE9 device;
LPDIRECT3DTEXTURE9 texture;
public:
//Пустой конструктор
TEXTURE();
//Конструктор с параметрами: device - устройство рисования, filename - путь к текстуре
TEXTURE(LPDIRECT3DDEVICE9 device,char* filename);
//Деструктор
~TEXTURE();
//Возвратить текстуру
LPDIRECT3DTEXTURE9 GetTexture();
//Загрузка текстуры: device - устройство рисования, filename - путь к текстуре
void LoadTexture(LPDIRECT3DDEVICE9 device,char* filename);
};