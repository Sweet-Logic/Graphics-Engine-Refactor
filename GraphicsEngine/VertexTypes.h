#pragma once
#include <directxmath.h>

using namespace DirectX;

struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 TexCoords;
	XMFLOAT4 Normal;
	XMFLOAT3 Tangent;
};

struct ScreenVertex
{
	XMFLOAT2 Pos;
	XMFLOAT2 TexCoords;
};
