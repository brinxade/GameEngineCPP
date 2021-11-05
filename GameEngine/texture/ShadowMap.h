#pragma once
#include"RenderedTexture.h"

class ShadowMap:public RenderedTexture
{

public:
	ShadowMap():RenderedTexture(1024, 1024, new Shader("res/shaders/shadowMap"))
	{
        glBindTexture(GL_TEXTURE_2D, ID[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ID[0], 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

    void bind()
    {
        glActiveTexture(GL_TEXTURE0+TU_SHADOW_MAP);
        glBindTexture(GL_TEXTURE_2D, ID[0]);
    }

    void unbind()
    {

    }

    void bindFBO()
    {
        glViewport(0, 0, width, height);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void unbindFBO()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
};
