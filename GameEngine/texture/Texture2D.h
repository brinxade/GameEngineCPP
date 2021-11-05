#pragma once
#include"Texture.h"

class Texture2D:public Texture
{
private:
	int updateTextureCount()
	{
		int textureCount = 0;
		for (int i = 0; i < 3; i++)
			if (!images[i].empty() && !(images[i].size()<=0))
				++textureCount;

		return textureCount;
	}	

	void load()
	{
		int width, height, channels;
		int format;

		for (int i = 0; i < textureCount; i++)
		{
			unsigned char* data = stbi_load(images[i].c_str(), &width, &height, &channels, 0);
			format = getFormat(channels);
			glBindTexture(type, ID[i]);

			glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			if (data)
			{
				glTexImage2D(type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(type);
			}
			else
			{
				std::cout << "Failed to load texture: " << images[i] << "\n";
			}

			stbi_image_free(data);
		}
	}

public:
	std::string images[3];
	const int MAX_TEXTURES = 3;

	Texture2D(std::string diffusedFile, std::string specularFile, std::string normalFile)
	{
		type = GL_TEXTURE_2D;
		images[0] = diffusedFile;
		images[1] = specularFile;
		images[2] = normalFile;
		textureCount = updateTextureCount();
		ID = new unsigned int[MAX_TEXTURES];
		glGenTextures(MAX_TEXTURES, ID);

		load();
	}

	~Texture2D()
	{
		delete[] ID;
	}

	void bind()
	{
		glActiveTexture(GL_TEXTURE0+TU_DIFFUSE);
		glBindTexture(type, ID[0]);

		glActiveTexture(GL_TEXTURE0+TU_SPECULAR);
		glBindTexture(type, ID[1]);

		glActiveTexture(GL_TEXTURE0+TU_NORMAL);
		glBindTexture(type, ID[2]);
	}

	unsigned int getDiffusedTU()
	{
		return TU_DIFFUSE;
	}

	unsigned int getSpecularTU()
	{
		return TU_SPECULAR;
	}

	unsigned int getNormalTU()
	{
		return TU_NORMAL;
	}

};