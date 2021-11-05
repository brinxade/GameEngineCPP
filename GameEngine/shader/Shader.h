#pragma once
#include <string>
#include<fstream>
#include<sstream>
#include"glad/glad.h"
#include<iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

using namespace std;

class Shader
{

private:
	void load(string shaderFullPath);

public:
	unsigned int ID;

    Shader()
    {
        ID = 0;
    }

	Shader(string shaderPath)
	{
		load(shaderPath);

	}

    void use()
    {
        glUseProgram(ID);
    }

    void setBool(const std::string& name, bool value) const
    {   
        glUseProgram(ID);
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    
    void setInt(const std::string& name, int value) const
    {   
        glUseProgram(ID);
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string& name, float value)
    {
        glUseProgram(ID);
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setVec2(const std::string& name, const glm::vec2& value) const
    {   
        glUseProgram(ID);
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec2(const std::string& name, float x, float y) const
    {
        glUseProgram(ID);
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }

    void setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUseProgram(ID);
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string& name, float x, float y, float z) const
    {
        glUseProgram(ID);
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }

    void setVec4(const std::string& name, const glm::vec4& value) const
    {
        glUseProgram(ID);
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string& name, float x, float y, float z, float w)
    {
        glUseProgram(ID);
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }

    void setMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUseProgram(ID);
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUseProgram(ID);
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUseProgram(ID);
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

};

