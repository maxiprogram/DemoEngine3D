#pragma once

class MATERIAL
{
private:
D3DMATERIAL9 material;
public:
//Пустой конструктор
MATERIAL();
//Деструктор
~MATERIAL();
//Возвращает материал
D3DMATERIAL9* GetMaterial();
//Задаёт цвет ambient: color - цвет
void SetAmbientColor(D3DXCOLOR color);
//Задаёт цвет diffuse: color - цвет
void SetDiffuseColor(D3DXCOLOR color);
//Задаёт цвет specular: color - цвет
void SetSpecularColor(D3DXCOLOR color);
//Задаёт цвет emissive: color - цвет
void SetEmissiveColor(D3DXCOLOR color);
//Задаёт дальность emissive: power - дальность
void SetPower(float power);
//Возвращает цвет ambient: color - цвет
void GetAmbientColor(D3DXCOLOR* color);
//Возвращает цвет diffuse: color - цвет
void GetDiffuseColor(D3DXCOLOR* color);
//Возвращает цвет specular: color - цвет
void GetSpecularColor(D3DXCOLOR* color);
//Возвращает цвет emissive: color - цвет
void GetEmissiveColor(D3DXCOLOR* color);
//Возвращает дальность emissive
float GetPower();
};
