#ifndef _CONSTANT_BUFFERS_H_
#define _CONSTANT_BUFFERS_H_

#include <directxmath.h>
#include "Lighting.h"

using namespace DirectX;

// Main shading
namespace MainConstants
{
	struct Globals
	{
		float gTime;
	};

	struct Frame
	{
		Lighting gLights[NUM_LIGHTS];

		XMFLOAT4 EyePosW;

		XMMATRIX View;
		XMMATRIX Projection;

		XMMATRIX gCameraView;
		XMMATRIX gCameraProj;

		float DirLightCount;
		float PointLightCount;
		float SpotLightCount;
	};

	struct Object
	{
		XMMATRIX mWorld;
		MatrialForCB gMaterial;
		int mResourcesInUse; //bit mask of the object resources used
	};
}

// Post Processing
namespace PostProcessing
{
	struct BrightnessMapping
	{
		XMMATRIX mWorld;
		XMMATRIX mView;
		XMMATRIX mProjection;
		float hasNormalMap;
	};

	struct ScreenFX
	{
		XMMATRIX mWorld;
		XMMATRIX mView;
		XMMATRIX mProjection;
		XMFLOAT2 ScreenSize;
		float gTime;
		float padding;

	};
}

// GeometryShader
namespace GS
{
	struct BillboardFrame
	{
		XMFLOAT4 CamPos;
	};

	struct BillboardInstance
	{
		XMFLOAT4 Position;
		float BillboardImageWidth;
		float BillboardImageHeight;
		float pad1;
		float pad2;
	};

	struct GrassInstance
	{
		XMFLOAT4 Position;
		XMFLOAT4 GrassColor;
		XMFLOAT2 GrassSize;
		float Pad1;
		float Pad2;
	};
}
#endif //!_CONSTANT_BUFFERS_H_