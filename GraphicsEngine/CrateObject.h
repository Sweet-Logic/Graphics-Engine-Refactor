#pragma once
#include "CubeObject.h"
class CrateObject :
	public CubeObject
{
public:
	CrateObject(std::string _objectName);
	~CrateObject();

	virtual void Initialize(ID3D11Device* _pd3dDevice) override;


};

