#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include<string>
#include<glad/glad.h>
#include "stb_image.h"

class Texture
{
protected:
	unsigned int *ID=nullptr;
	int textureCount = 0;
	unsigned int type;

	static const unsigned int TU_DIFFUSE = 0;
	static const unsigned int TU_SPECULAR = 1;
	static const unsigned int TU_NORMAL = 2;
	static const unsigned int TU_SHADOW_MAP = 5;

	int getFormat(int channels)
	{
		int format=0;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;

		return format;
	}

public:
	Texture()
	{

	}

	~Texture()
	{
		delete[] ID;
	}

	unsigned int* getID()
	{
		return ID;
	}

	virtual void bind()
	{
		
	}

	virtual void unbind()
	{

	}

	static unsigned int getDiffusedTU()
	{
		return TU_DIFFUSE;
	}

	static unsigned int getSpecularTU()
	{
		return TU_SPECULAR;
	}

	static unsigned int getNormalTU()
	{
		return TU_NORMAL;
	}

	static int getShadowMapTU()
	{
		return TU_SHADOW_MAP;
	}
};