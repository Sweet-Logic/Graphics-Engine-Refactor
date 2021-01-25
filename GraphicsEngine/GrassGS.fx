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

#define GRASS_COUNT 1000

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

cbuffer cbPerScene : register(b2)
{
	float4 GrassPosition;
	float4 GrassColor;
	float2 GrassSize;
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
	float3 Color : COLOR;
	float2 Size : SIZE;
	float Rotation : ROTATION;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float4 WorldPos : POSITION;
	float4 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float2 TexCoords : TEXCOORD0;
	float4 ProjTex : TEXCOORD1;
	float3 Color : COLOR;
};

VS_OUTPUT VS(float4 Pos : POSITION, float2 TexCoords : TEXCOORD, float4 Normal : NORMAL, float3 Tangent : TANGENT, float4 InstPos : INSTANCEPOS, float4 InstColor : INSTANCECOLOR, float2 InstSize: INSTANCESIZE, uint instanceID : SV_InstanceID)
{
	VS_OUTPUT output;

	output.WorldPos = mul(InstPos, World);
	output.ProjTex = mul(output.WorldPos, gCameraView);
	output.ProjTex = mul(output.ProjTex, gCameraProj);
	output.Size = InstSize;
	output.Pos = mul(output.WorldPos, View);
	output.Color = float4(0.3f, 1.0f,0.1f, 1.0f);
	output.Pos = mul(output.Pos, Projection);

	output.TexCoords = float2(TexCoords.x, TexCoords.y);



	float4 normal;
	normal.xyz = Normal.xyz;
	normal.w = 0.0f;

	output.Normal = normalize(mul(normal, World));
	output.Tangent = normalize(mul(Tangent, World));

	output.Rotation = (instanceID / 20) * (Pos.x + instanceID);

	return output;
}

void PS(VS_OUTPUT input)
{

}

[maxvertexcount(12)]
void GS_GrassLowQuality(point VS_OUTPUT input[1], inout TriangleStream<PS_INPUT> OutputStream)
{
	matrix<float, 4,4> Rotation = matrix(cos(input[0].Rotation), 0, sin(input[0].Rotation),0,
		0,1,0,0,
		-sin(input[0].Rotation), 0, cos(input[0].Rotation), 0,
		0,0,0,1
		);

	float halfWidth = input[0].Size.x / 2.0f;

	float3 triNormal = input[0].Normal;
	triNormal.y = 0.0f;

	//triNormal = mul(triNormal, Rotation);
	triNormal = normalize(triNormal);

	float3 upVector = float3(0.0f, 1.0f, 0.0f);

	float3 rightVector = normalize(cross(triNormal, upVector));

	rightVector = rightVector * halfWidth;


	upVector = float3(0, input[0].Size.y, 0);

	float3 vert[5];
	float offsetX = 0;
	float offsetZ = 0;
	float2 texCoord[5];
	texCoord[0] = float2(0, 0);
	texCoord[1] = float2(1, 0);
	texCoord[2] = float2(0.5, 1);
	texCoord[3] = float2(1, 0);
	texCoord[4] = float2(0.5, 1);


	//for (int i = 0; i < 3; i++)
	//{
		//offsetX = (i * input[0].Size.x) - (input[0].Size.x);

		/*for (int j = 0; j < 3; j++)
		{
			offsetZ = (j * input[0].Size.x) - (input[0].Size.x);*/


			vert[0] = input[0].WorldPos + upVector; // +float3(offsetX, 0, offsetZ);
			vert[1] = input[0].WorldPos + rightVector + (triNormal*halfWidth); // +float3(offsetX, 0, offsetZ);
			vert[2] = input[0].WorldPos - rightVector + (triNormal*halfWidth);  // +float3(offsetX, 0, offsetZ);
			vert[3] = input[0].WorldPos - rightVector - (triNormal*halfWidth); // +float3(offsetX, 0, offsetZ);
			vert[4] = input[0].WorldPos + rightVector - (triNormal*halfWidth); // +float3(offsetX, 0, offsetZ);



			PS_INPUT outputVert[5];
			for (int i = 0; i < 5; i++)
			{
				outputVert[i].Pos = mul(float4(vert[i], 1.0f), mul(View, Projection));
				outputVert[i].WorldPos = float4(vert[i], 0.0f);
				outputVert[i].ProjTex = input[0].ProjTex;
				outputVert[i].TexCoords = texCoord[i];
				outputVert[i].Color = input[0].Color;

				outputVert[i].Normal = float4(triNormal, 0);
				outputVert[i].Tangent = rightVector;
			}

			outputVert[0].Normal = float4(triNormal, 0);;
			outputVert[1].Normal = float4(triNormal, 0);;
			outputVert[2].Normal = float4(triNormal, 0);;

			

			OutputStream.Append(outputVert[0]);
			OutputStream.Append(outputVert[1]); // normal is forward
			OutputStream.Append(outputVert[2]);
			OutputStream.RestartStrip();

			outputVert[0].Normal = float4(-rightVector, 0);
			outputVert[2].Normal = float4(-rightVector, 0);
			outputVert[3].Normal = float4(-rightVector, 0);

			OutputStream.Append(outputVert[0]);
			OutputStream.Append(outputVert[2]); // normal is left
			OutputStream.Append(outputVert[3]);
			OutputStream.RestartStrip();

			outputVert[0].Normal = float4(-triNormal, 0);
			outputVert[3].Normal = float4(-triNormal, 0);
			outputVert[4].Normal = float4(-triNormal, 0);

			OutputStream.Append(outputVert[0]);
			OutputStream.Append(outputVert[3]); // normal is backward
			OutputStream.Append(outputVert[4]);
			OutputStream.RestartStrip();

			outputVert[0].Normal = float4(rightVector, 0);
			outputVert[4].Normal = float4(rightVector, 0);
			outputVert[1].Normal = float4(rightVector, 0);

			OutputStream.Append(outputVert[0]);
			OutputStream.Append(outputVert[4]); // normal is right
			OutputStream.Append(outputVert[1]);
			OutputStream.RestartStrip();


		//}
	//}

}