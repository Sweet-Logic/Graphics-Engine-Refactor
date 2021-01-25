#ifndef _TGA_READER_H_
#define _TGA_READER_H_
#include "../FileReader.h"
#include <dxgiformat.h>

//Not a perfect tga reader as it only supports colour mapped images at 32 bits.
struct TGA_HEADDER
{
    unsigned char data1[12];
    unsigned short width;
    unsigned short height;
    unsigned char bpp;
    unsigned char data2;
};

struct TGA_Info : FileInfo
{
    unsigned int width = UINT_MAX;
    unsigned int height = UINT_MAX;
    unsigned int bpp = UINT_MAX; //bits per pixel
    DXGI_FORMAT format;
};

class TGA_READER : public FileReader<TGA_READER>
{
};

bool FileReader<TGA_READER>::CheckExtention(char* extention)
{
    return StrUtils::Compare(extention, ".tga") || StrUtils::Compare(extention, ".icb") ||StrUtils::Compare(extention, ".vda") ||StrUtils::Compare(extention, ".vst");
}

FileInfo* FileReader<TGA_READER>::ReadFile(char* filePath)
{
    TGA_Info* fileInfo = new TGA_Info();
    int error, imageSize;
	FILE* input;
	unsigned int count;
	TGA_HEADDER headder;
	unsigned char* targaImage;

	error = fopen_s(&input, filePath, "rb");
	if (error)
	{
		//File did not open
		return fileInfo;
	}

	count = (unsigned int)fread(&headder, sizeof(TGA_HEADDER), 1, input);
	if (count != 1)
	{
		return fileInfo;
	}

	fileInfo->height = (int)headder.height;
	fileInfo->width = (int)headder.width;
	fileInfo->bpp = (int)headder.bpp;

	if (fileInfo->bpp != 32)
	{
		return fileInfo;
	}
    fileInfo->type = TGA_32;
    fileInfo->format = DXGI_FORMAT_R8G8B8A8_UNORM;
	imageSize = fileInfo->width * fileInfo->height * (fileInfo->bpp/8);

	targaImage = new unsigned char[imageSize];
	if (!targaImage)
	{
		return fileInfo;
	}


	count = (unsigned int)fread(targaImage, 1, imageSize, input);
	if (count != imageSize)
	{
		return fileInfo;
	}
	//delete [] targetData;
	fileInfo->data = new unsigned char[imageSize];
	if (!fileInfo->data)
	{
		return fileInfo;
	}

	int index = 0;

	int k = (fileInfo->width * fileInfo->height * 4) - (fileInfo->width * 4);

	for (int j = 0; j < fileInfo->height; j++)
	{
		for (int i = 0; i < fileInfo->width; i++)
		{
			fileInfo->data[index + 0] = targaImage[k + 2];
			fileInfo->data[index + 1] = targaImage[k + 1];
			fileInfo->data[index + 2] = targaImage[k + 0];
			fileInfo->data[index + 3] = targaImage[k + 3];

			k += 4;
			index += 4;

		}
		k -= (fileInfo->width * 8);
	}
	delete[] targaImage;
	targaImage = nullptr;
    fileInfo->success = true;
    return fileInfo;
}

#endif //!_TGA_READER_H_