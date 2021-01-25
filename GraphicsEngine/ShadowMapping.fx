//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//#include "LightHelper.fx"

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


struct Material
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular; // w = specpower;
	float4 Reflect;
};


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
Texture2D gDiffuseMap : register(t1);

cbuffer cbObject  : register(b1)
{
	matrix World;
	Material gMaterial;
	float clipTexture;
	float hasTextureMap;
	float hasNormalMap;
	float hasSpecular;
};

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 WorldPos : POSITION;
	float4 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float2 TexCoords : TEXCOORD0;
	float4 ProjTex : TEXCOORD1;
};

struct PS_OUTPUT
{
	float4 color : SV_Target0;
	float4 HDRLight : SV_Target1;
};


SamplerState samLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};



//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(float4 Pos : POSITION, float2 TexCoords : TEXCOORD, float4 Normal : NORMAL, float3 Tangent : TANGENT)
{
	VS_OUTPUT output;

	output.WorldPos = mul(Pos, World);
	output.Pos = mul(output.WorldPos, View);
	output.Pos = mul(output.Pos, Projection);
	output.TexCoords = TexCoords;
	output.ProjTex = mul(output.WorldPos, gCameraView);
	output.ProjTex = mul(output.ProjTex, gCameraProj);
	float4 normal;
	normal.xyz = Normal.xyz;
	normal.w = 0.0f;

	output.Normal = normalize(mul(normal, World));
	output.Tangent = normalize(mul(Tangent, World));
	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
void PS(VS_OUTPUT input)
{
	float4 diffuse = gDiffuseMap.Sample(samLinear, input.TexCoords);

	if (clipTexture)
	{
		clip(diffuse.a - 0.25f);
	}

}

RasterizerState Depth
{
	DepthBias = 10000;
	DepthBiasClamp = 0.0f;
	SlopeScaledDepthBias = 1.0f;
};

technique11 BuildShadowMapTech
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(NULL);

		SetRasterizerState(Depth);
	}
}

technique11 BuildShadowMapAlphaClipTech
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS()));
	}
}