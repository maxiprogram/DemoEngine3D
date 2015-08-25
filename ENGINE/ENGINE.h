#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include "CLASS\FORM\FORM.cpp"
#include "CLASS\INPUTS\INPUTS.cpp"
#include "CLASS\FONT\FONT.cpp"
#include "CLASS\TEXTURE\TEXTURE.cpp"
#include "CLASS\MATERIAL\MATERIAL.cpp"
#include "CLASS\LIGHT\LIGHT.cpp"
#include "CLASS\MANIPULATE\MANIPULATE.cpp"
#include "CLASS\OBJECT\OBJECT.cpp"
#include "CLASS\CAMERA\CAMERA.cpp"
#include "CLASS\GRAPHIC\GRAPHIC.cpp"