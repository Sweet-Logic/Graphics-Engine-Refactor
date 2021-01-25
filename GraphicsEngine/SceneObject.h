#pragma once
#include <directxmath.h>
#include <string>
#include "LinkedList.h"
#include "Buffers.h"


template<typename T>
class List;

class CBObject;

using namespace DirectX;

class ID3D11Device;

class SceneObject
{
public:
	SceneObject(std::string ObjectName, bool AddToList = true);
	~SceneObject() { 
		RemoveItemFromList(ObjectList, this);
		ObjectCount--; 
	};

	XMMATRIX GetWorldMatrix() const { 
		return _scaleMatrix * _rotationMatrix*_translationMatrix; 
	}

	XMVECTOR GetWorldPosition() const { 
		return XMVector4Transform(XMVectorSet(0.0f,0.0f,0.0f,1.0f), GetWorldMatrix());
	}

	void TranslateObject(XMVECTOR Translation) { 
		_translationMatrix = XMMatrixIdentity() * XMMatrixTranslation(XMVectorGetX(Translation),  XMVectorGetY(Translation), XMVectorGetZ(Translation)); 
		_translation = XMFLOAT3(XMVectorGetX(Translation), XMVectorGetY(Translation), XMVectorGetZ(Translation));
		//ObjectConstantBuffer.mWorld = XMMatrixTranspose(GetWorldMatrix());
	}
	void RotateObject(XMVECTOR Rotation) {
		_rotationMatrix *= XMMatrixRotationX(XMVectorGetX(Rotation))*  XMMatrixRotationY(XMVectorGetY(Rotation))* XMMatrixRotationZ(XMVectorGetZ(Rotation));
		_forward = XMVector4Transform(_forward, XMMatrixRotationX(XMVectorGetX(Rotation))*  XMMatrixRotationY(XMVectorGetY(Rotation))* XMMatrixRotationZ(XMVectorGetZ(Rotation))); 
		_rotation = XMFLOAT3(XMVectorGetX(Rotation), XMVectorGetY(Rotation) ,XMVectorGetZ(Rotation));
		//ObjectConstantBuffer.mWorld = XMMatrixTranspose(GetWorldMatrix());
	}
	void ScaleObject(XMVECTOR Scale) { 
		_scaleMatrix = XMMatrixIdentity() * XMMatrixScaling(XMVectorGetX(Scale), XMVectorGetY(Scale), XMVectorGetZ(Scale)); 
		_scale = XMFLOAT3(XMVectorGetX(Scale), XMVectorGetY(Scale), XMVectorGetZ(Scale)); 
		//ObjectConstantBuffer.mWorld = XMMatrixTranspose(GetWorldMatrix());
	}

	void virtual Update(float deltaTime) {};

	XMVECTOR GetForwardVector() const { return _forward; }

	static List<SceneObject>* ObjectList;
	static int ObjectCount;

	CBObject GetObjectCB();
	void virtual Initialize(ID3D11Device* _pd3dDevice) = 0;
protected:
	void SetForwardVector(XMVECTOR newForward) { _forward = newForward; }

//	CBObject ObjectConstantBuffer;
	

	XMFLOAT3 GetTranslation() {
		return _rotation;
	}
	XMFLOAT3 GetRotation() {
		return _rotation;
	}
	XMFLOAT3 GetScale() {
		return _rotation;
	}
private:

	XMVECTOR _forward;
	//XMMATRIX _worldMatrix;

	XMFLOAT3 _translation = XMFLOAT3(0, 0, 0);
	XMFLOAT3 _rotation = XMFLOAT3(0,0,0);
	XMFLOAT3 _scale = XMFLOAT3(1, 1, 1);


	XMMATRIX _translationMatrix;
	XMMATRIX _rotationMatrix;
	XMMATRIX _scaleMatrix;


	std::string _objectName;

};

