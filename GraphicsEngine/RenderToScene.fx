//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 TexCoords : TEXCOORD0;
};

Texture2D gScene : register(t0);
SamplerState Sample1;

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
	return gScene.Sample(Sample1, input.TexCoords);
}
