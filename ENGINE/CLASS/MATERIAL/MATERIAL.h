#pragma once

class MATERIAL
{
private:
D3DMATERIAL9 material;
public:
//������ �����������
MATERIAL();
//����������
~MATERIAL();
//���������� ��������
D3DMATERIAL9* GetMaterial();
//����� ���� ambient: color - ����
void SetAmbientColor(D3DXCOLOR color);
//����� ���� diffuse: color - ����
void SetDiffuseColor(D3DXCOLOR color);
//����� ���� specular: color - ����
void SetSpecularColor(D3DXCOLOR color);
//����� ���� emissive: color - ����
void SetEmissiveColor(D3DXCOLOR color);
//����� ��������� emissive: power - ���������
void SetPower(float power);
//���������� ���� ambient: color - ����
void GetAmbientColor(D3DXCOLOR* color);
//���������� ���� diffuse: color - ����
void GetDiffuseColor(D3DXCOLOR* color);
//���������� ���� specular: color - ����
void GetSpecularColor(D3DXCOLOR* color);
//���������� ���� emissive: color - ����
void GetEmissiveColor(D3DXCOLOR* color);
//���������� ��������� emissive
float GetPower();
};
