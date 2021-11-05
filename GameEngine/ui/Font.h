#pragma once
#include<freetype/freetype.h>
#include<iostream>
#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>
#include<map>
#include<shader/Shader.h>
#include<macros.h>
#include<glm/gtc/matrix_transform.hpp>

struct Character
{
	unsigned int texture;
	glm::ivec2 size, bearing;
	int advance;
};

class Font
{
private:
	std::string fontPath;
	std::map<const char, Character> characters;
	FT_Library ft;

	void loadCharacters(int start, int end)
	{
		FT_Face face;

		if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
		{
			std::cout << "Failed to load font: " << fontPath << "\n";
			return;
		}

		FT_Set_Pixel_Sizes(face, 0, 24);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for (unsigned char c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}

			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};

			characters.insert(std::pair<char, Character>(c, character));
		}
		
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}

public:
	Font(std::string fontPath)
	{
		this->fontPath = fontPath;
		FT_Init_FreeType(&ft);
		loadCharacters(0, 128);
	}

	std::map<const char, Character> getCharacterMap()
	{
		return characters;
	}

	Character getCharacter(char character)
	{
		return characters[character];
	}
};