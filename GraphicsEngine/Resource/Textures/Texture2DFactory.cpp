#include "Texture2DFactory.h"
#include "../../System/Graphics/Graphics.h"
#include "../../Utils/String/StringUtils.h"
#include "../../File_IO/FileReaders/Image/TgaReader.h"

Texture2D* TEXTURE_2D_FACTORY::Create(
    FLOAT width,
    FLOAT height,
    uint mipLevels,
    uint arraySize,
    DXGI_FORMAT format,
    DXGI_SAMPLE_DESC sampleDesc,
    D3D11_USAGE usage,
    uint bindFlags,
    uint CPUAccessFlags,
    uint miscFlags
    )
{
    D3D11_TEXTURE2D_DESC newTextureDesc;
 	newTextureDesc.Width =  width;
 	newTextureDesc.Height = height;
 	newTextureDesc.MipLevels = mipLevels;
 	newTextureDesc.ArraySize = arraySize;
 	newTextureDesc.Format = format;
 	newTextureDesc.SampleDesc = sampleDesc;
 	newTextureDesc.Usage = usage;
 	newTextureDesc.BindFlags = bindFlags;
 	newTextureDesc.CPUAccessFlags = CPUAccessFlags;
 	newTextureDesc.MiscFlags = miscFlags;
    ID3D11Texture2D* tex2D;
 	HRESULT success = Graphics::GetInstance().GetDevice()->CreateTexture2D(&newTextureDesc, nullptr, &tex2D);
    if(success)
    {
        tex2D->Release();
        return nullptr;
    }
    Texture2D* newTexture = new Texture2D(tex2D, newTextureDesc.Format);

    return newTexture;
}


Texture2D* TEXTURE_2D_FACTORY::Create(char* imageFilePath)
{
    D3D11_SUBRESOURCE_DATA subresourceData;
    D3D11_TEXTURE2D_DESC newTextureDesc;
    FileInfo* fileInfo;
    DXGI_SAMPLE_DESC sample;
	sample.Count = 1;
	sample.Quality = 0;
    //First validate the extention

    // Load the image
    unsigned int pathLength = StrUtils::GetLength(imageFilePath);
    int extStart = StrUtils::rFind(imageFilePath, '.');

    char* ext = StrUtils::copy(imageFilePath, extStart, pathLength - extStart);

    if(TGA_READER::CheckExtention(ext))
    {
        TGA_Info* returnedFile = static_cast<TGA_Info*>(TGA_READER::ReadFile(imageFilePath));
        fileInfo = returnedFile;
        subresourceData.pSysMem = (void*)returnedFile->data;
        subresourceData.SysMemPitch = returnedFile->width * returnedFile->bpp;
        subresourceData.SysMemSlicePitch = returnedFile->width * returnedFile->height * returnedFile->bpp;
 	    newTextureDesc.Width =  returnedFile->width;
 	    newTextureDesc.Height = returnedFile->height;
 	    newTextureDesc.Format = returnedFile->format;
    }

 	newTextureDesc.MipLevels = 1;
 	newTextureDesc.ArraySize = 1;
 	newTextureDesc.SampleDesc = sample;
 	newTextureDesc.Usage = D3D11_USAGE_DEFAULT;
 	newTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
 	newTextureDesc.CPUAccessFlags = 0;
 	newTextureDesc.MiscFlags = 0;

    //Create the texture
    ID3D11Texture2D* tex2D;
 	HRESULT success = Graphics::GetInstance().GetDevice()->CreateTexture2D(&newTextureDesc, &subresourceData, &tex2D);
	if (success)
	{
		if (fileInfo)
		{
			delete[] fileInfo->data;
			delete fileInfo;
		}
		if(tex2D)
			tex2D->Release();
        return nullptr;
    }

    //Create the texture 2D resource
    Texture2D* newTexture = new Texture2D(tex2D, newTextureDesc.Format);
    newTexture->SetFileInfo(fileInfo);
    return newTexture;
}

Texture2D* TEXTURE_2D_FACTORY::Create(Resource* resource)
{
    return nullptr;
}
