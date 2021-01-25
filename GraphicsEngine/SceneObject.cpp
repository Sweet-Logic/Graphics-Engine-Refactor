#include "SceneObject.h"

List<SceneObject>* SceneObject::ObjectList = nullptr;
int SceneObject::ObjectCount = 0;

SceneObject::SceneObject(std::string ObjectName, bool AddToList) :_objectName(ObjectName)
{
	if (AddToList)
	{

		ObjectList = AddNewListItem(ObjectList, this);
		ObjectCount++;
	}
//	ObjectConstantBuffer.mWorld = &_worldMatrix;
//	ObjectConstantBuffer.hasNormalMap = 0.0f;
	//ObjectConstantBuffer.hasSpecular = 0.0f;
	//ObjectConstantBuffer.hasTextureMap = 1.0f;
	//ObjectConstantBuffer.clipTexture = 0.0f;
	//ObjectConstantBuffer.gMaterial.Ambient = { 0.2f,0.2f,0.2f,1.0f };
	//ObjectConstantBuffer.gMaterial.Diffuse = { 0.7f,0.7f,0.7f,1.0f };
	//ObjectConstantBuffer.gMaterial.Specular = { 0.2f,0.2f,0.2f,16.0f };
	//ObjectConstantBuffer.gMaterial.Reflect = { 1.0f,1.0f,1.0f,1.0f };

	_forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f); 
	_translationMatrix = XMMatrixIdentity();
	_scaleMatrix = XMMatrixIdentity();
	_rotationMatrix = XMMatrixIdentity();
};

//CBObject SceneObject::GetObjectCB()
//{
//	return ObjectConstantBuffer;
//}