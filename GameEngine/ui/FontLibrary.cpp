#include"FontLibrary.h"


std::string FontLibrary::fontsDirectory="res/fonts/";
Shader* FontLibrary::shader;
glm::mat4 FontLibrary::projection;
unsigned int FontLibrary::vao, FontLibrary::vbo;
std::map<std::string, Font*> FontLibrary::fonts;

void FontLibrary::init(Shader* shader)
{
	projection=glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT);
	FontLibrary::shader = shader;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	loadAllFonts();
}

void FontLibrary::cleanUp()
{
	for(auto & [key, value]: fonts) {
		delete value;
	}
}

void FontLibrary::loadAllFonts()
{
	std::string path, fontName, fontPath;
	for (const auto& dirEntry : std::filesystem::directory_iterator(fontsDirectory))
	{
		fontPath = dirEntry.path().u8string();
		fontName = Utility::StringFunctions::getFilenameFromPath(fontPath, true);
		
		std::cout << "Loading Font: " << fontPath << "\n";
		fonts[fontName] = new Font(fontPath);
	}
}

void FontLibrary::loadFont(std::string fontName, std::string fontPath)
{
	fonts[fontName] = new Font(fontPath);
}

void FontLibrary::renderText(std::string fontName, std::string text, glm::vec2 position, float scale = 1.0f, glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f))
{
	if (fonts.find(fontName) == fonts.end())
		return;

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader->setVec3("textColor", color);
	shader->setMat4("projection", projection);
	shader->setInt("character", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);
	std::map<const char, Character> characters=fonts[fontName]->getCharacterMap();

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters[*c];

		float xpos = position.x + ch.bearing.x * scale;
		float ypos = position.y - (ch.size.y - ch.bearing.y) * scale;

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
		position.x += (ch.advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_NONE);
	glEnable(GL_DEPTH_TEST);
}

Font* FontLibrary::getFont(std::string fontName)
{
	return fonts[fontName];
}
