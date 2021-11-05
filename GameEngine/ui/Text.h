#pragma once
#include<glm/gtc/matrix_transform.hpp>
#include"FontLibrary.h"
#include"Control.h"
#include<shader/Shader.h>

class Text
{
private:
	Controls::Control* parent;
	Shader* shader;
	Font* font;
	Character* charMap;

	std::string text, fontName;
	unsigned int width, height, vao, vbo;
	float x, y, scale;

	void calcSize()
	{
		int w = 0;
		int h = 0;

		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character character = font->getCharacter(*c);
			w+= character.advance >> 6;
			if (character.size.y > h)
				h=character.size.y;
		}

		width = w;
		height = h;
	}

public:

	Text(Controls::Control* parent, std::string text, std::string fontName = "arial")
	{
		this->parent = parent;
		this->shader = new Shader("res/shaders/text");
		this->fontName = fontName;
		this->font = FontLibrary::getFont(fontName);
		this->text = text;
		this->x = parent->getXOffset();
		this->y = parent->getYOffset();
		this->scale = 1;

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		calcSize();
	}

	~Text()
	{
		delete shader;
		delete charMap;
	}

	void setText(std::string text)
	{
		this->text = text;
		calcSize();
	}

	void render()
	{
		this->x = parent->getXOffset();
		this->y = parent->getYOffset();

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::vec3 color = glm::vec3(1, 1, 1);
		glm::mat4 projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT);
		shader->setVec3("textColor", color);
		shader->setMat4("projection", projection);
		shader->setInt("character", 0);

		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vao);

		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = font->getCharacter(*c);

			float xpos = x + ch.bearing.x * scale;
			float ypos = y - (ch.size.y - ch.bearing.y) * scale;

			float w = ch.size.x * scale;
			float h = ch.size.y * scale;

			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};

			glBindTexture(GL_TEXTURE_2D, ch.texture);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (float)(ch.advance >> 6) * scale;
		}

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_NONE);
		glEnable(GL_DEPTH_TEST);
	}

	unsigned int getWidth()
	{
		return width;
	}

	unsigned int getHeight()
	{
		return height;
	}
};

