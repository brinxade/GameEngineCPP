#pragma once
#include"Texture.h"

class TextureCubeMap:public Texture
{
private:
	const std::string filenames[6] = { "right","left","top","bottom","front","back" };
	std::string filePath, fileExt;

	void load()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, *ID);
		int width, height, channels;
		int format;
		std::string filepath = "";
		for (int i = 0; i < textureCount; i++)
		{
			filepath = filePath + "/" + filenames[i] + fileExt;
			unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
			format = getFormat(channels);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				std::cout << "Failed to load texture: " << filepath << "\n";
			}

			stbi_image_free(data);
		}
	}
public:
	TextureCubeMap(std::string filePath, std::string fileExt = ".jpg")
	{
		textureCount = 6;
		this->filePath = filePath;
		this->fileExt = fileExt;
		ID = new unsigned int[1];
		glGenTextures(1, ID);
		load();
	}

	void bind()
	{
		glActiveTexture(GL_TEXTURE0 + TU_DIFFUSE);
	}
};