#pragma once
#include "SceneObject.h"
#include "IDrawable.h"

class MeshComponent;
class CameraObject;

class CarBaseObject :
	public SceneObject,
	public IDrawable
{
public:
	CarBaseObject(std::string objectName);
	~CarBaseObject();
	virtual void Initialize(ID3D11Device* _pd3dDevice) override;


	void Update(float deltaTime) override;
	void Draw(ID3D11DeviceContext*& Context, UINT* stride, UINT* offset, ID3D11Buffer *Buffer);

	MeshComponent* StaticMeshComponent;

	float MaxSpeed = 750.0f;
	float MinSpeed = 0.0f;
	float Acceleration = 50.0f;
	float breakSpeed = 60.0f;
	float CurrentSpeed = 0.0f;
	float speedDecrement = 0.0f;
	float speedDecrementFrom = 0.0f;
	float deccelerationSpeed = 60.0f;
	float timeToStop = 2.0f;
	bool Accelerating = false;


	CameraObject* FollowCamera;
	CameraObject* FrontCamera;
};

