#include "CameraObject.h"
#include "BillboardObject.h"


CameraObject::CameraObject(std::string ObjectName, Type CameraType) : SceneObject(ObjectName), _viewMatrix(DirectX::XMMatrixIdentity()), _cameraType(CameraType), _lookAt(DirectX::XMVectorSet(1.0f,0.0f,0.0f,1.0f)), _up(DirectX::XMVectorSet(0.0f,1.0f,0.0f,1.0f))
{
	
}


CameraObject::~CameraObject()
{
}

void CameraObject::Initialize(ID3D11Device* _pd3dDevice)
{

	
}

void CameraObject::Update(float deltaTime)
{
	//TranslateObject(DirectX::XMVectorSet(10.0f, 10.0f, 0.0f, 1.0f));

	switch (_cameraType)
	{
	case LOOKAT:
		// XMMatrixLookAt uses the eye pos and target to calculate a direction and passes that through to XMLookTo so if Eye and target are the same assert is triggered
		if (DirectX::XMVector3Equal(GetWorldPosition(), _lookAt ))
		{
			_lookAt += DirectX::XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f); //Makes the camera look down if its looking at its own position
		}
		
		_viewMatrix = DirectX::XMMatrixLookAtLH(GetWorldPosition(), _lookAt, _up); 
		break;
	case LOOKTO:
		_viewMatrix = DirectX::XMMatrixLookToLH(GetWorldPosition(), GetForwardVector(), _up);
		break;
	}
	SceneObject::Update(deltaTime);

}
