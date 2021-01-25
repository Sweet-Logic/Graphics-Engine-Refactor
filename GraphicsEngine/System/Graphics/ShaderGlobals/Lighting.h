#pragma once
#include <directxmath.h>
#include <windows.h>

#define NUM_LIGHTS 8

using namespace DirectX;

enum LIGHT_MASK
{
	E_POINT = 0x00000001,
	E_DIRECTIONAL = 0x00000002,
	E_SPOT = 0x00000004
};

struct Lighting // instead of having a seperate buffer for each light
{
	Lighting()
	{
		ZeroMemory(this, sizeof(Lighting));
	}

	XMFLOAT4 Ambient; 		// all
	XMFLOAT4 Diffuse; 		// all
	XMFLOAT4 Specular; 		// all 
	XMFLOAT3 Position; 		// point and spot
	float Intensity; 		// all
	XMFLOAT3 Direction; 	// directional and spot
	float Range; 			// point and spot
	XMFLOAT3 Attenuation; 	// point and spot
	float Spot; 			// spot
	int lightType; 			// bitmask of diffrent lights
};

struct MatrialForCB
{
	MatrialForCB() { ZeroMemory(this, sizeof(MatrialForCB)); }

	XMFLOAT4 Ambient;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Specular; // w = specpower;
	XMFLOAT4 Reflect;
};