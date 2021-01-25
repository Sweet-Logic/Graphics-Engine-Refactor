#include "Texture2D.h"
#include "DDSTextureLoader.h"



 ID3D11Device* Texture2D::_device = nullptr;
 ID3D11DeviceContext* Texture2D::_deviceContext = nullptr;

Texture2D::Texture2D(std::string filepath) : _textureFilePath(filepath)
{
	_mapArray = 0;
	_texture = 0;
	
	_textureView = 0;
}

Texture2D::Texture2D(const Texture2D &)
{
}

void Texture2D::SetReferances(ID3D11Device *&device, ID3D11DeviceContext *&deviceContext)
{
	_device = device;
	_deviceContext = deviceContext;
}

Texture2D::~Texture2D()
{
}

bool Texture2D::Initialize()
{
	HRESULT hResult;

	//Check FilePath Extention
	int extentionStart = _textureFilePath.find('.');

	if (extentionStart == -1)
	{
		//no extention found
		return false;
	}
	std::string newFilepath = _textureFilePath;
	if (_textureFilePath.substr(0, 4) != "maps")
	{
		newFilepath = "maps\\" + _textureFilePath;
	}
	std::string extention = _textureFilePath.substr(extentionStart + 1, _textureFilePath.length() - extentionStart + 1);
	if (extention == "tga")
	{
		bool result;
		int height, width;
		unsigned int rowPitch;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

		//Load tga
		hResult = LoadTarga32(newFilepath, width, height, _mapArray, &_texture);
		if (FAILED(hResult))
		{
			return false;
		}

		D3D11_TEXTURE2D_DESC textureDesc;

		textureDesc.Height = height;
		textureDesc.Width = width;
		textureDesc.MipLevels = 0;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

		hResult = _device->CreateTexture2D(&textureDesc, nullptr, &_texture);
		// Create the empty texture.
		if (FAILED(hResult))
		{
			return false;
		}

		rowPitch = (width * 4) * sizeof(unsigned char);

		// Copy the targa image data into the texture.
		_deviceContext->UpdateSubresource(_texture, 0, nullptr, _mapArray, rowPitch, 0);

		// Setup the shader resource view description.
		srvDesc.Format = textureDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;

		// Create the shader resource view for the texture.
		hResult = _device->CreateShaderResourceView(_texture, &srvDesc, &_textureView);
		if (FAILED(hResult))
		{
			return false;
		}
		delete[] _mapArray;
	}
	else if (extention == "dds")
	{
		//Load DDS
		std::wstring wTextureFile = std::wstring(newFilepath.begin(), newFilepath.end());
		hResult = DirectX::CreateDDSTextureFromFile(_device, wTextureFile.c_str(), (ID3D11Resource**)&_texture, &_textureView);
		if (FAILED(hResult))
		{
			return false;
		}
	}


	//// Setup the description of the texture.



	//// Set the row pitch of the targa image data.
	//rowPitch = (width * 4) * sizeof(unsigned char);
	return true;
}

void Texture2D::CleanUp()
{
	// Release the texture view resource.
	if (_textureView)
	{

		_textureView = 0;
	}

	// Release the texture.
	if (_texture)
	{
		_texture->Release();
		_texture = 0;
	}

	// Release the targa data.

	delete[] _mapArray;
	_textureView->Release();

	delete[] _mapArray;

	return;
}

ID3D11ShaderResourceView** Texture2D::GetTexture()
{
	return &_textureView;
}

HRESULT Texture2D::LoadTarga32(std::string filepath, int & width, int & height, unsigned char* &targetData, ID3D11Texture2D** texture)
{

	int error, bpp, imageSize;
	FILE* input;
	unsigned int count;
	TargaHeader headder;
	unsigned char* targaImage;

	error = fopen_s(&input, filepath.c_str(), "rb");
	if (error)
	{
		//File did not open
		return S_FALSE;
	}

	count = (unsigned int)fread(&headder, sizeof(TargaHeader), 1, input);
	if (count != 1)
	{
		return S_FALSE;
	}

	height = (int)headder.height;
	width = (int)headder.width;
	bpp = (int)headder.bpp;

	if (bpp != 32)
	{
		return S_FALSE;
	}

	imageSize = width * height * 4;

	targaImage = new unsigned char[imageSize];
	if (!targaImage)
	{
		return S_FALSE;
	}


	count = (unsigned int)fread(targaImage, 1, imageSize, input);
	if (count != imageSize)
	{
		return S_FALSE;
	}
	//delete [] targetData;
	targetData = new unsigned char[imageSize];
	if (!targetData)
	{
		return S_FALSE;
	}

	int index = 0;

	int k = (width * height * 4) - (width * 4);

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			targetData[index + 0] = targaImage[k + 2];
			targetData[index + 1] = targaImage[k + 1];
			targetData[index + 2] = targaImage[k + 0];
			targetData[index + 3] = targaImage[k + 3];

			k += 4;
			index += 4;

		}
		k -= (width * 8);
	}
	delete[] targaImage;
	targaImage = nullptr;

	return S_OK;
}

int Texture2D::GetWidth()
{
	D3D11_TEXTURE2D_DESC textureDesc;

	_texture->GetDesc(&textureDesc);
	return textureDesc.Width;
}

int Texture2D::GetHeight()
{
	D3D11_TEXTURE2D_DESC textureDesc;

	_texture->GetDesc(&textureDesc);
	return textureDesc.Height;
}