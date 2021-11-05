#include"ShaderLibrary.h"

const std::string ShaderLibrary::shadersDirectory = "res/shaders/";
std::map<std::string, Shader*> ShaderLibrary::shaders;

void ShaderLibrary::init()
{
	std::string path, shaderName, shaderPath;
	for (const auto& dirEntry : std::filesystem::directory_iterator(shadersDirectory))
	{
		shaderPath = dirEntry.path().u8string();
		shaderName = Utility::StringFunctions::getFilenameFromPath(shaderPath);

		std::cout << "Loading Shader: " << shaderPath << "\n";
		shaders[shaderName] = new Shader(shaderPath);
	}
}

Shader* ShaderLibrary::getShader(std::string shaderName)
{
	return shaders[shaderName];
}

void ShaderLibrary::cleanUp()
{
	for (auto& [key, value] : shaders) {
		delete value;
	}
}