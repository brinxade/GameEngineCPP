#pragma once
#include<map>
#include<string>
#include<filesystem>
#include<utility/StringFunctions.h>
#include"Shader.h"

class ShaderLibrary
{
private:
	const static std::string shadersDirectory;
	static std::map<std::string, Shader*> shaders;

public:
	static void init();
	static void cleanUp();
	static Shader* getShader(std::string shaderName);

};

