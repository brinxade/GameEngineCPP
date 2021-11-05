#include<shader/Shader.h>

void Shader::load(std::string shaderFullPath)
{	
	std::string str_vs, str_fs;
	std::ifstream file_vs, file_fs;
	std::stringstream strstream_vs, strstream_fs;

	file_vs.open(shaderFullPath + "/vs.glsl");
	file_fs.open(shaderFullPath + "/fs.glsl");

	if (!file_vs.is_open() || !file_fs.is_open())
	{
		std::cout << "ERR::SHADERLOG::FILE_NOT_FOUND: " << shaderFullPath << std::endl;
		return;
	}

	strstream_vs << file_vs.rdbuf();
	strstream_fs << file_fs.rdbuf();
	file_vs.close();
	file_fs.close();

	str_vs=strstream_vs.str();
	str_fs=strstream_fs.str();

	const char* src_vs = str_vs.c_str();
	const char* src_fs = str_fs.c_str();

	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vs, 1, &src_vs, NULL);
	glShaderSource(fs, 1, &src_fs, NULL);
	glCompileShader(vs);
	glCompileShader(fs);

	ID = glCreateProgram();
	glAttachShader(ID, vs);
	glAttachShader(ID, fs);
	glLinkProgram(ID);

	int statusVs, statusFs;
	char infoLog[512];

	glGetShaderiv(vs, GL_COMPILE_STATUS, &statusVs);
	if (!statusVs)
	{
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		std::cout << "ERR::SHADERLOG::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glGetShaderiv(fs, GL_COMPILE_STATUS, &statusFs);
	if (!statusFs)
	{
		glGetShaderInfoLog(fs, 512, NULL, infoLog);
		std::cout << "ERR::SHADERLOG::FRAG::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}