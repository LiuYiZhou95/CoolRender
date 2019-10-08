//
// Created by B612 on 2019/9/26.
//

#pragma once

#include "Application.h"
#include "View.h"
#include "Batch.h"
#include "Camera.h"
#include "Texture2D.h"
#include "Node.h"
#include "shader_m.h"
#include "Image.h"

class FboHelper {

public:
    FboHelper();
    ~FboHelper();
    unsigned CreateFramebuffer();
    /// Delete a framebuffer using either extension or core functionality. Used only on OpenGL.
    void DeleteFramebuffer(unsigned fbo);
    /// Bind a framebuffer using either extension or core functionality. Used only on OpenGL.
    void BindFramebuffer(unsigned fbo);
    /// Bind a framebuffer color attachment using either extension or core functionality. Used only on OpenGL.
    void BindColorAttachment(unsigned index, unsigned target, unsigned object, bool isRenderBuffer);
    /// Bind a framebuffer depth attachment using either extension or core functionality. Used only on OpenGL.
    void BindDepthAttachment(unsigned object, bool isRenderBuffer);
    /// Bind a framebuffer stencil attachment using either extension or core functionality. Used only on OpenGL.
    void BindStencilAttachment(unsigned object, bool isRenderBuffer);
    /// Check FBO completeness using either extension or core functionality. Used only on OpenGL.
    bool CheckFramebuffer();
    /// Resolve a multisampled texture on itself.
    bool ResolveToTexture(Texture2D* texture);
};



