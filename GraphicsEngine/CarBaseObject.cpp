#include "CarBaseObject.h"
#include "ObjLoader.h"
#include "CameraObject.h"


#include <iostream>
#include <sstream>
#include <Windows.h>

CarBaseObject::CarBaseObject(std::string objectName) : SceneObject(objectName), IDrawable(false)
{
	
}


CarBaseObject::~CarBaseObject()
{
}

void CarBaseObject::Initialize(ID3D11Device* _pd3dDevice)
{
	//RotateObject(XMVectorSet(0.0f, XM_PI / 2, 0.0f, 0.0f));
	StaticMeshComponent = ObjLoader::GetInstance()->LoadMeshFromFile("car.obj");
	StaticMeshComponent->load();
	StaticMeshComponent->SetTexture(Map::rDiffuse, new Texture2D("CarTextureMap.tga"));


	FrontCamera = new CameraObject("FPS Camera", LOOKTO);
	FollowCamera = new CameraObject("Follow Camera", LOOKAT);

	FrontCamera->Initialize(_pd3dDevice);
	//FrontCamera->RotateObject(XMVectorSet(0.0f, XM_PI / 2, 0.0f, 0.0f));

	FrontCamera->TranslateObject(GetWorldPosition() + GetForwardVector()*2.0f + XMVectorSet(0.0f, 2.0f, 0.0f, 1.0f));
	FrontCamera->RotateObject(XMVectorSet(GetRotation().x + (XM_PI / 18.0f), GetRotation().y, GetRotation().z, 0.0f));
	FrontCamera->SetLookAt(GetForwardVector());
	//FrontCamera->Update(0.0f);
	FollowCamera->Initialize(_pd3dDevice);
	FollowCamera->RotateObject(XMVectorSet(0.0f, XM_PI / 2, 0.0f, 0.0f));
	FollowCamera->TranslateObject(GetWorldPosition() + (GetForwardVector()*4.0f) + XMVectorSet(0.0f, 3.0f, 0.0f, 1.0f));
	FollowCamera->SetLookAt(GetWorldPosition() + GetForwardVector() *5.0f);
	FollowCamera->Update(0.0f);

}

void CarBaseObject::Update(float deltaTime)
{
	Accelerating = false;



	if (GetAsyncKeyState('W'))
	{
		if (CurrentSpeed < 0)
		{
			CurrentSpeed += breakSpeed * deltaTime;
		}
		CurrentSpeed += Acceleration * deltaTime;
		if (std::abs(CurrentSpeed) > MaxSpeed) CurrentSpeed = MaxSpeed;
		Accelerating = true;
		speedDecrementFrom = CurrentSpeed;

	}
	if (GetAsyncKeyState('S'))
	{

		if (CurrentSpeed > 0)
		{
			CurrentSpeed -= breakSpeed * deltaTime;
		}
		CurrentSpeed -= Acceleration * deltaTime;
		if (std::abs(CurrentSpeed) > MaxSpeed) CurrentSpeed = -MaxSpeed;
		Accelerating = true;
		speedDecrementFrom = CurrentSpeed;

	}

	if (!Accelerating)
	{
		if (std::abs(CurrentSpeed) > 0.1f)
		{
			CurrentSpeed -= (speedDecrementFrom * deltaTime)/timeToStop;
		}
		else
		{
			CurrentSpeed = 0.0f;
		}
	}
	
	TranslateObject(GetWorldPosition() + (GetForwardVector() * ((CurrentSpeed)*deltaTime)));
	


	if (CurrentSpeed != 0.0f)
	{
		if (GetAsyncKeyState('A'))
		{
			RotateObject(XMVectorSet(0.0f, -(XM_PI / 1.3f)*deltaTime, 0.0f, 1.0f) * CurrentSpeed / MaxSpeed);
			FrontCamera->RotateObject(XMVectorSet(0.0f, -(XM_PI / 1.3f)*deltaTime, 0.0f, 1.0f) * CurrentSpeed / MaxSpeed);

		}
		if (GetAsyncKeyState('D'))
		{
			RotateObject(XMVectorSet(0.0f, (XM_PI / 1.3f)*deltaTime, 0.0f, 1.0f) * CurrentSpeed / MaxSpeed);
			FrontCamera->RotateObject(XMVectorSet(0.0f, (XM_PI/1.3f)*deltaTime, 0.0f, 1.0f)* CurrentSpeed / MaxSpeed);
		}
	}


	FrontCamera->TranslateObject(GetWorldPosition() + (GetForwardVector()*60.0f) + XMVectorSet(0.0f, 60.0f, 0.0f, 1.0f));
	FrontCamera->SetLookAt(GetForwardVector());

	FollowCamera->TranslateObject(GetWorldPosition() + (GetForwardVector()*-200.0f) + XMVectorSet(0.0f, 90.0f, 0.0f, 1.0f));
	FollowCamera->SetLookAt(GetWorldPosition() + (GetForwardVector() * 10.0f));

	ScaleObject(XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	//TranslateObject(XMVectorSet(1.0f, 4.0f, 1.0f, 1.0f));

	SceneObject::Update(deltaTime);

}

void CarBaseObject::Draw(ID3D11DeviceContext*& Context, UINT * stride, UINT * offset, ID3D11Buffer *Buffer)
{
//	StaticMeshComponent->Draw(Context, stride, offset, Buffer, ObjectConstantBuffer);


}
