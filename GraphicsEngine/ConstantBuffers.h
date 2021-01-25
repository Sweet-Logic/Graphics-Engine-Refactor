#pragma once
#include <directxmath.h>

using namespace DirectX;



struct ConstantBufferBrightnessMapping
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
	float hasNormalMap;
};

struct ConstantBufferSFX
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
	XMFLOAT2 ScreenSize;
	float gTime;
	float padding;

};