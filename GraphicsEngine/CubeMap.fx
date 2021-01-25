//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 TexCoords : TEXCOORD0;
};

Texture2D gBaseMap;
Texture2D gMapToAdd;
SamplerState Sample;



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
	float4 color = float4(0,0,0,0);

	color = gBaseMap.Sample(Sample, input.TexCoords) + gMapToAdd.Sample(Sample, input.TexCoords);
	

	return color;
}
