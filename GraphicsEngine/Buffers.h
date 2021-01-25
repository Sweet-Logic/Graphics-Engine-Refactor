//#pragma once
//
//#include "Lighting.h"
//
//struct CBFrame
//{
//	Lighting gDirLight[NUM_LIGHTS];
//
//	XMFLOAT4 EyePosW;
//
//	XMMATRIX View;
//	XMMATRIX Projection;
//
//	XMMATRIX gCameraView;
//	XMMATRIX gCameraProj;
//
//	float gTime;
//	float DirLightCount;
//	float PointLightCount;
//	float SpotLightCount;
//};
//
//struct CBObject
//{
//	XMMATRIX mWorld;
//	MatrialForCB gMaterial;
//	float clipTexture;
//	float hasTextureMap;
//	float hasNormalMap;
//	float hasSpecular;
//};
//
//struct ConstantBufferSFX
//{
//	XMMATRIX mWorld;
//	XMMATRIX mView;
//	XMMATRIX mProjection;
//	XMFLOAT2 ScreenSize;
//	float gTime;
//	float padding;
//
//};
//
//
//struct ConstantBufferBrightnessMapping
//{
//	XMMATRIX mWorld;
//	XMMATRIX mView;
//	XMMATRIX mProjection;
//	float hasNormalMap;
//};
//
//struct CBBillboardFrame
//{
//	XMFLOAT4 CamPos;
//};
//
//struct CBPerBillboard
//{
//	XMFLOAT4 Position;
//	float BillboardImageWidth;
//	float BillboardImageHeight;
//	float pad1;
//	float pad2;
//};
//
//struct CBPerGrass
//{
//	XMFLOAT4 Position;
//	XMFLOAT4 GrassColor;
//	XMFLOAT2 GrassSize;
//	float Pad1;
//	float Pad2;
//};