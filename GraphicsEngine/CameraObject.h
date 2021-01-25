#pragma once
#include "SceneObject.h"

enum Type
{
	LOOKAT = 0,
	LOOKTO,
};
class CameraObject :
	public SceneObject
{
public:
	CameraObject(std::string ObjectName, Type CameraType = LOOKAT);
	~CameraObject();

	virtual void Initialize(ID3D11Device* _pd3dDevice) override;

	void Update(float deltaTime) override;

	XMVECTOR GetLookDirection() const {
		switch (_cameraType)
		{
		case LOOKTO:
			return GetForwardVector();
		case LOOKAT:
			return _lookAt - GetWorldPosition();
		}
	}

	XMVECTOR GetUpVector() const { return _up; }

	void SetLookAt(XMVECTOR newLook) { if (_cameraType == LOOKAT) { _lookAt = newLook; }}

	XMMATRIX GetViewMatrix() { return _viewMatrix; };

	XMMATRIX GetTransposedViewMatrix() { return XMMatrixTranspose(_viewMatrix); }


	XMVECTOR _lookAt;
	XMVECTOR _up;
	XMMATRIX _viewMatrix;
	Type _cameraType;


};

