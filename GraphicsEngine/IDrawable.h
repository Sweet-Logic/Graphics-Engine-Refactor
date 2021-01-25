#pragma once
#include <d3d11_1.h>
#include "VertexTypes.h"


class IDrawable
{
public:
	IDrawable(bool HasTransparancy) : _materialHasTransparancy(HasTransparancy)
	{
	};

	~IDrawable()
	{
	};
	bool GetHasTransparancy() const { return _materialHasTransparancy; }
	void SetHasTransparancy(bool newTransparancy) { _materialHasTransparancy = newTransparancy; }


	bool _materialHasTransparancy;
	virtual void Draw(ID3D11DeviceContext*& Context, UINT* stride, UINT* offset, ID3D11Buffer *Buffer) = 0;
};