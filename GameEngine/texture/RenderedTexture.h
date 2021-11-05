#pragma once

#include<texture/Texture.h>
#include<macros.h>

class RenderedTexture : public Texture
{
protected:
    Shader* shader;
    unsigned int fbo;
    unsigned int width, height;

public:
    RenderedTexture(unsigned int width, unsigned int height, Shader* shader=nullptr)
    {
        ID = new unsigned int[1];
        this->shader = shader;
        this->width = width;
        this->height = height;
        glGenFramebuffers(1, &fbo);
        glGenTextures(1, ID);
    }

    ~RenderedTexture()
    {
        delete shader;
    }

    Shader* getShader()
    {
        return shader;
    }

    void getTexture()
    {

    }

    virtual void bindFBO()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    }

    virtual void unbindFBO()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
};