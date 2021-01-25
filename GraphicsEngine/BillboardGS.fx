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

cbuffer cbObject  : register(b1)
{
	matrix World;
	Material gMaterial;

	float hasTextureMap;
	float hasNormalMap;
	float hasSpecular;
};

cbuffer cbPerFrame : register(b2)
{
	float4 camPos;
};


cbuffer cbPerScene : register(b3)
{
	float4 Position;
	float BillboardImageWidth;
	float BillboardImageHeight;
	float Pad1;
	float Pad2;
}

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
	float4 Pos : SV_POSITION;
	float4 WorldPos : POSITION;
	float4 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float2 TexCoords : TEXCOORD0;
	float4 ProjTex : TEXCOORD1;
	float3 Color : COLOR;
};

Texture2D ObjTexture : register(t1);
SamplerState ObjSamplerState;



[maxvertexcount(4)]
void GS_Billboard(point VS_OUTPUT input[1], inout TriangleStream<PS_OUTPUT> OutputStream)
{
	float halfWidth = BillboardImageWidth / 2.0f;

	float3 planeNormal = camPos - input[0].WorldPos.xyz;
	planeNormal.y = 0.0f;
	planeNormal = normalize(planeNormal);

	float3 upVector = float3(0.0f, 1.0f, 0.0f);

	float3 rightVector = normalize(cross(planeNormal, upVector));

	rightVector = rightVector * 75;


	upVector = float3(0, 150, 0);

	float3 vert[4];

	vert[0] = input[0].WorldPos.xyz + rightVector;
	vert[1] = input[0].WorldPos.xyz - rightVector;
	vert[2] = input[0].WorldPos.xyz + rightVector + upVector;
	vert[3] = input[0].WorldPos.xyz - rightVector + upVector;


	float2 texCoord[4];
	texCoord[0] = float2(1, 1);
	texCoord[1] = float2(0, 1);
	texCoord[2] = float2(1, 0);
	texCoord[3] = float2(0, 0);

	PS_OUTPUT outputVert;
	outputVert.Color = float3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 4; i++)
	{
		outputVert.Pos = mul(float4(vert[i], 1.0f), mul(View, Projection));
		outputVert.WorldPos = float4(vert[i], 0.0f);
		outputVert.TexCoords = texCoord[i];
		outputVert.ProjTex = input[0].ProjTex;

		outputVert.Normal = float4(planeNormal, 0);
		outputVert.Tangent = float3(0, 0, 0);

		OutputStream.Append(outputVert);
	}
}


