#pragma once

#include <string>
#include <fstream>

#include <d3d11.h>

struct TargaHeader
{
	unsigned char data1[12];
	unsigned short width;
	unsigned short height;
	unsigned char bpp;
	unsigned char data2;
};

class Texture2D
{
public:
	Texture2D(std::string filepath);
	Texture2D(const Texture2D&);
	~Texture2D();

	bool Initialize();
	void CleanUp();

	ID3D11ShaderResourceView** GetTexture();

	static void SetReferances(ID3D11Device *&device, ID3D11DeviceContext *&deviceContext);

	int GetWidth();
	int GetHeight();


private:
	HRESULT LoadTarga32(std::string filepath, int &width, int &height, unsigned char *&targetData, ID3D11Texture2D** texture);

	unsigned char* _mapArray = nullptr;

	static ID3D11Device* _device;
	static ID3D11DeviceContext* _deviceContext;

	std::string _textureFilePath;
	ID3D11Texture2D* _texture;
	ID3D11ShaderResourceView* _textureView;
};

