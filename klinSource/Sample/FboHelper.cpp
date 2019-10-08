//
// Created by B612 on 2019/9/26.
//

#include "FboHelper.h"



unsigned FboHelper::CreateFramebuffer() {
    unsigned newFbo = 0;

    glGenFramebuffers(1, &newFbo);
    return newFbo;
}

void FboHelper::DeleteFramebuffer(unsigned fbo) {

    glDeleteFramebuffers(1, &fbo);
}

void FboHelper::BindFramebuffer(unsigned fbo) {

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FboHelper::BindColorAttachment(unsigned index, unsigned target, unsigned object,
                                    bool isRenderBuffer) {
    if (!object)
        isRenderBuffer = false;


    {
        if (!isRenderBuffer)
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, target, object, 0);
        else
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_RENDERBUFFER,
                                      object);
    }
}

void FboHelper::BindDepthAttachment(unsigned object, bool isRenderBuffer) {
    if (!object)
        isRenderBuffer = false;


    {
        if (!isRenderBuffer)
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, object, 0);
        else
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, object);
    }
}

void FboHelper::BindStencilAttachment(unsigned object, bool isRenderBuffer) {
    if (!object)
        isRenderBuffer = false;

    {
        if (!isRenderBuffer)
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, object, 0);
        else
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER,
                                      object);
    }
}

bool FboHelper::CheckFramebuffer() {

    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}