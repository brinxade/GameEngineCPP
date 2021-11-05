#pragma once
#include<string>
#include<shader/Shader.h>
#include<ui/Font.h>
#include<ui/FontLibrary.h>

class AssetsManager
{
public:
	static void init();
	static Shader* getShader(std::string);
	static Font* getFont(std::string);
};