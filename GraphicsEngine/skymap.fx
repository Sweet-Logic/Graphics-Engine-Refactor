//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

// #include "LightHelper.fx" //Need to look into Include handlers

#define NUM_LIGHTS 8

struct DirectionalLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float3 Direction;
	float Intensity;
};

struct PointLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float3 Position;
	float Range;
	float3 Att;
	float Intensity;
};

struct SpotLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float3 Position;
	float Range;
	float3 Direction;
	float Spot;
	float3 Att;
	float Intensity;
};

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------


cbuffer cbFrame : register(b0)
{
	DirectionalLight gDirLight[NUM_LIGHTS];
	PointLight gPointLight[NUM_LIGHTS];
	SpotLight gSpotLight[NUM_LIGHTS];
	float4 EyePosW;

	matrix View;
	matrix Projection;
	matrix gCameraView;
	matrix gCameraProj;
	float gTime;
	float DirLightCount;
	float PointLightCount;
	float SpotLightCount;
};

cbuffer cbObject
{
	matrix World;
	float hasTextureMap;
	float hasNormalMap;
	float hasSpecular;
	float isLitByWorld;
	float reflectiveness;
};

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float3 TexCoords : TEXCOORD0;
};

TextureCube gRenderView : register(t1);
SamplerState Sample1;

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(float4 Pos : POSITION, float2 TexCoords : TEXCOORD, float4 Normal : NORMAL, float3 Tangent : TANGENT)
{
	VS_OUTPUT output;
	Pos.w = 1.0f;
	output.Pos = mul(Pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection).xyww;

	output.TexCoords = Pos;

	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
	return gRenderView.Sample(Sample1, input.TexCoords);
}
