//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
	float2 ScreenSize;
	float gTime;
	float BlurStrength;
};

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 TexCoords : TEXCOORD0;
};

Texture2D gScene;
Texture2D gBrightnessMap;
SamplerState Sample1;


uniform float2 TexelSize;
//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(float4 Pos : POSITION, float2 TexCoords : TEXCOORD)
{
	VS_OUTPUT output;

	output.Pos = Pos;
	output.TexCoords = TexCoords;

	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 color;
	color = gScene.Sample(Sample1, input.TexCoords);
	color += gBrightnessMap.Sample(Sample1, input.TexCoords);
	
	color.a = 1.0f;

	return color;
}
