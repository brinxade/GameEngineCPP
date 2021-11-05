#pragma once
#include<map>
#include<string>
#include<filesystem>
#include<glad/glad.h>
#include<utility/StringFunctions.h>
#include<shader/Shader.h>
#include"Font.h"

class FontLibrary
{
private:
	static std::string fontsDirectory;
	static Shader* shader;
	static glm::mat4 projection;
	static unsigned int vao, vbo;
	static std::map<std::string, Font*> fonts;

public:
	static void init(Shader* shader);
	static void cleanUp();
	static void loadFont(std::string fontName, std::string fontPath);
	static void loadAllFonts();
	static void renderText(std::string fontName, std::string text, glm::vec2 position, float scale, glm::vec3 color);
	static Font* getFont(std::string fontName);
};
