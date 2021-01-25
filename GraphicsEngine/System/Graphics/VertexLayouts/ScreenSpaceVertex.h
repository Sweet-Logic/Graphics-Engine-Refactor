#ifndef _SCREEN_SPACE_VERTEX_H_
#define _SCREEN_SPACE_VERTEX_H_

#include <directxmath.h>

namespace ScreenSpace
{
	struct ScreenVertex
	{
		XMFLOAT2 Pos;
		XMFLOAT2 TexCoords;
	};

	static D3D11_INPUT_ELEMENT_DESC vertexLayout[] =
	{
		{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	12,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "NORMAL",		0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	20,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "TANGENT",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	36,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	};
}

#endif //!_SCREEN_SPACE_VERTEX_H_