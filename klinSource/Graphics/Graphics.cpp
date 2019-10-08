//
// Created by liuyizhou on 2019/7/18.
//

#include "Graphics.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "GraphicsImpl.h"
#include "ShaderProgram.h"
#include <string>
#include "Texture.h"
#include "Texture2D.h"
#include "RenderSurface.h"

//glElementTypes类型的字节数
static const unsigned glElementComponents[] =
        {
                1,
                1,
                2,
                3,
                4,
                4,
                4
        };
//当前element的数据类型
static const unsigned glElementTypes[] =
        {
                GL_INT,
                GL_FLOAT,
                GL_FLOAT,
                GL_FLOAT,
                GL_FLOAT,
                GL_UNSIGNED_BYTE,
                GL_UNSIGNED_BYTE
        };

Graphics::Graphics(Context *context) :
        Object(context),
        impl_(new GraphicsImpl()),
        defaultTextureAnisotropy_(4),
        defaultTextureFilterMode_(FILTER_TRILINEAR),
        indexBuffer_(NULL),
        pixelShader_(NULL),
        vertexShader_(NULL) {

}

Graphics::~Graphics() {

}

void Graphics::SetIndexBuffer(IndexBuffer *buffer) {
    if (indexBuffer_ == buffer)
        return;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer ? buffer->getGPUObjectName() : 0);
    indexBuffer_ = buffer;
}

void Graphics::SetVertexBuffer(VertexBuffer *vertexBuffer) {
    std::vector<VertexBuffer *> vertexBuffers;
    vertexBuffers.push_back(vertexBuffer);
    SetVertexBuffers(vertexBuffers);
}

bool
Graphics::SetVertexBuffers(const std::vector<VertexBuffer *> buffers, unsigned int instanceOffset) {
    if (buffers.size() > MAX_VERTEX_STREAMS) {
        LOGE("Too many vertex buffers.");
        return false;
    }
    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; i++) {
        VertexBuffer *buffer = NULL;
        if (i < buffers.size())
            buffer = buffers[i];
        if (buffer != vertexBuffers_[i]) {
            vertexBuffers_[i] = buffer;
            impl_->vertexBuffersDirty_ = true;
        }
    }
    return true;
}

void Graphics::SetShaders(ShaderVariation *vs, ShaderVariation *ps) {
    if (vs == vertexShader_ && ps == pixelShader_)
        return;
    if (vs && !vs->getGPUObjectName()) {
        bool success = vs->Create();
        if (success) {
            LOGI("Compiled vertex shader:%d", vs->getGPUObjectName());
        } else {
            LOGE("Failed to compile vertex shader:%s", vs->GetName().c_str());
            vs = nullptr;
        }
    }

    if (ps && !ps->getGPUObjectName()) {
        bool success = ps->Create();
        if (success) {
            LOGI("Compiled pixel shader:%d", ps->getGPUObjectName());
        } else {
            LOGE("Failed to compile pixel shader:%s", ps->GetName().c_str());
        }
    }

    if (!vs || !ps) {
        glUseProgram(0);
        vertexShader_ = nullptr;
        pixelShader_ = nullptr;
        impl_->shaderProgram_ = nullptr;
    } else {
        vertexShader_ = vs;
        pixelShader_ = ps;
        pair<ShaderVariation *, ShaderVariation *> combinantion(vs, ps);
        KL_Map<pair<ShaderVariation *, ShaderVariation *>, ShaderProgram *>::iterator i = impl_->shaderPrograms_.find(
                combinantion);
        if (i != impl_->shaderPrograms_.end()) {
            if (i->second->getGPUObjectName()) {
                glUseProgram(i->second->getGPUObjectName());
                unsigned a = i->second->getGPUObjectName();
                impl_->shaderProgram_ = i->second;
            } else {
                glUseProgram(0);
                impl_->shaderProgram_ = nullptr;
            }
        } else {
            ShaderProgram *newProgram = new ShaderProgram(this, vs, ps);
            if (newProgram->Link()) {
                LOGI("Linked vertex shader:%s,and pixel shader:%s", vs->GetName().c_str(),
                     ps->GetName().c_str());
                impl_->shaderProgram_ = newProgram;
            } else {
                LOGE("Failed to link vertex shader:%s, and pixel shader:%s", vs->GetName().c_str(),
                     ps->GetName().c_str());
                glUseProgram(0);
                impl_->shaderProgram_ = nullptr;
            }
            impl_->shaderPrograms_[combinantion] = newProgram;
        }
    }

    if (impl_->shaderProgram_) {
        impl_->vertexAttributes_ = impl_->shaderProgram_->GetVertexAttributes();
    } else {
        impl_->vertexAttributes_.clear();
    }
    impl_->vertexBuffersDirty_ = true;
}

void Graphics::setShaderParameter(std::string param, const float *data, unsigned count) {
    if (impl_->shaderProgram_) {
        const ShaderParameter *info = impl_->shaderProgram_->GetParameter(param);
        if (info) {
            switch (info->glType_) {
                case GL_FLOAT:
                    glUniform1fv(info->location_, count, data);
                    break;
                case GL_FLOAT_VEC2:
                    glUniform2fv(info->location_, count / 2, data);
                    break;
                case GL_FLOAT_VEC3:
                    glUniform3fv(info->location_, count / 3, data);
                    break;
                case GL_FLOAT_VEC4:
                    glUniform4fv(info->location_, count / 4, data);
                    break;
                case GL_FLOAT_MAT3:
                    glUniformMatrix3fv(info->location_, count / 9, GL_FALSE, data);
                    break;
                case GL_FLOAT_MAT4:
                    glUniformMatrix4fv(info->location_, count / 16, GL_FALSE, data);
                    break;
                default:
                    break;
            }
        }
    }
}

void Graphics::setShaderParameter(std::string param, const glm::mat4 matrix) {
    if (impl_->shaderProgram_) {
        const ShaderParameter *info = impl_->shaderProgram_->GetParameter(param);
        if (info) {
            //设置矩阵统一变量
            glUniformMatrix4fv(info->location_, 1, GL_FALSE, (GLfloat *) &matrix);
        }
    }
}

void Graphics::setShaderParameter(std::string param, const glm::vec4 vectorData) {
    if (impl_->shaderProgram_) {
        const ShaderParameter *info = impl_->shaderProgram_->GetParameter(param);
        if (info) {
            switch (info->glType_) {
                case GL_FLOAT:
                    glUniform1fv(info->location_, 1, (GLfloat *) &vectorData);
                    break;
                case GL_FLOAT_VEC2:
                    glUniform2fv(info->location_, 1, (GLfloat *) &vectorData);
                    break;
                case GL_FLOAT_VEC3:
                    glUniform3fv(info->location_, 1, (GLfloat *) &vectorData);
                    break;
                case GL_FLOAT_VEC4:
                    glUniform4fv(info->location_, 1, (GLfloat *) &vectorData);
                    break;
                default:
                    break;
            }
        }
    }
}

void Graphics::setShaderParameter(std::string param, float value) {
    if (impl_->shaderProgram_) {
        const ShaderParameter *info = impl_->shaderProgram_->GetParameter(param);
        if (info) {
            glUniform1fv(info->location_, 1, &value);
        }
    }
}

void Graphics::setShaderParameter(std::string param, int value) {
    if (impl_->shaderProgram_) {
        const ShaderParameter *info = impl_->shaderProgram_->GetParameter(param);
        if (info) {
            glUniform1i(info->location_, value);
        }
    }
}

void Graphics::setShaderParameter(std::string param, bool value) {
    if (impl_->shaderProgram_) {
        const ShaderParameter *info = impl_->shaderProgram_->GetParameter(param);
        if (info) {
            glUniform1i(info->location_, (int) value);
        }
    }
}

void Graphics::setTexture(unsigned index, Texture *texture) {
    if (index >= MAX_TEXTURE_UNITS)
        return;


    // Check if texture is currently bound as a rendertarget. In that case, use its backup texture, or blank if not defined
//    if (texture)
//    {
//        if (renderTargets_[0] && renderTargets_[0]->GetParentTexture() == texture)
//            texture = texture->GetBackupTexture();
//        else
//        {
//            // Resolve multisampled texture now as necessary
//            if (texture->getMultiSample() > 1 && texture->getAutoResolve() && texture->isResolveDirty())
//            {
//                if (texture->getType() == Texture2D::getTypeStatic())
//                    ResolveToTexture(static_cast<Texture2D*>(texture));
//
//            }
//        }
//    }

    if (textures_[index] != texture) {
        if (impl_->activeTexture_ != index) {
            glActiveTexture(GL_TEXTURE0 + index);
            impl_->activeTexture_ = index;
        }
        if (texture) {
            unsigned glType = texture->getTarget();

            if (impl_->textureTypes_[index] && impl_->textureTypes_[index] != glType)
                glBindTexture(impl_->textureTypes_[index], 0);
            glBindTexture(glType, texture->getGPUObjectName());
            impl_->textureTypes_[index] = glType;

            if (texture->getParametersDirty())
                texture->updateParameters();
        } else if (impl_->textureTypes_[index]) {
            glBindTexture(impl_->textureTypes_[index], 0);
            impl_->textureTypes_[index] = 0;
        }
        textures_[index] = texture;
    } else {
        if (texture && texture->getParametersDirty()) {
            if (impl_->activeTexture_ != index) {
                glActiveTexture(GL_TEXTURE0 + index);
                impl_->activeTexture_ = index;
            }
            glBindTexture(texture->getTarget(), texture->getGPUObjectName());
            if (texture->getParametersDirty())
                texture->updateParameters();
        }
    }

}

Texture *Graphics::getTexture(unsigned index) const {
    return index < MAX_TEXTURE_UNITS ? textures_[index] : nullptr;
}

void Graphics::setTextureForUpdate(Texture *texture) {
    if (impl_->activeTexture_ != 0) {
        glActiveTexture(GL_TEXTURE0);
        impl_->activeTexture_ = 0;
    }
    unsigned glType = texture->getTarget();
    if (impl_->textureTypes_[0] && impl_->textureTypes_[0] != glType)
        glBindTexture(impl_->textureTypes_[0], 0);
    glBindTexture(glType, texture->getGPUObjectName());
    impl_->textureTypes_[0] = glType;
    textures_[0] = texture;
}

void Graphics::SetVBO(unsigned object) {
    if (object)
        glBindBuffer(GL_ARRAY_BUFFER, object);
}

//三角形卷绕绘制
void Graphics::Draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount) {
    if (!vertexCount)
        return;
    PrepareDraw();
    unsigned primitiveCount;
    GLenum glPrimitiveType;

    GetGLPrimitiveType(vertexCount, type, primitiveCount, glPrimitiveType);

    glDrawArrays(glPrimitiveType, vertexStart, vertexCount);


}

//索引法绘制
void
Graphics::Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex,
               unsigned vertexCount) {
    if (!indexCount || !indexBuffer_ || !indexBuffer_->getGPUObjectName())
        return;

    PrepareDraw();

    unsigned indexSize = indexBuffer_->GetIndexSize();
    unsigned primitiveCount;
    GLenum glPrimitiveType;

    GetGLPrimitiveType(indexCount, type, primitiveCount, glPrimitiveType);
    GLenum indexType = indexSize == sizeof(unsigned short) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
    glDrawElements(glPrimitiveType, indexCount, indexType,
                   reinterpret_cast<const GLvoid *>(indexStart * indexSize));//indexCount
}

void Graphics::PrepareDraw() {
    if (impl_->vertexBuffersDirty_)//设置一个标识位，该操作只需要执行一次就可以了
    {
        unsigned assignedLocations = 0;
        for (unsigned i = MAX_VERTEX_STREAMS - 1; i < MAX_VERTEX_STREAMS; i--) {
            VertexBuffer *buffer = vertexBuffers_[i];
            if (!buffer || !buffer->getGPUObjectName())
                continue;
            const std::vector<VertexElement> elements = buffer->GetElements();
            for (int j = 0; j < elements.size(); j++) {
                VertexElement element = elements[j];
                KL_Map<pair<char, string>, unsigned>::const_iterator k =
                        impl_->vertexAttributes_.find(
                                make_pair((char) element.semantic_, element.index_));
                if (k != impl_->vertexAttributes_.end()) {
                    unsigned location = k->second;
                    //
                    glEnableVertexAttribArray(location);
                    // Enable/disable instancing divisor as necessary
                    unsigned dataStart = element.offset_;
                    SetVBO(buffer->getGPUObjectName());
                    //
                    glVertexAttribPointer(location, glElementComponents[element.type_],
                                          glElementTypes[element.type_],
                                          element.type_ == TYPE_UBYTE4_NORM ? GL_TRUE : GL_FALSE,
                                          (unsigned) buffer->GetVertexSize(),
                                          (const void *) (size_t) dataStart);
                }
            }
        }
        impl_->vertexBuffersDirty_ = false;
    }

}

void
Graphics::GetGLPrimitiveType(unsigned elementCount, PrimitiveType type, unsigned &primitiveCount,
                             GLenum &glPrimitiveType) {
    switch (type) {
        case TRIANGLE_LIST:
            primitiveCount = elementCount / 3;
            glPrimitiveType = GL_TRIANGLES;
            break;

        case LINE_LIST:
            primitiveCount = elementCount / 2;
            glPrimitiveType = GL_LINES;
            break;

        case POINT_LIST:
            primitiveCount = elementCount;
            glPrimitiveType = GL_POINTS;
            break;

        case TRIANGLE_STRIP:
            primitiveCount = elementCount - 2;
            glPrimitiveType = GL_TRIANGLE_STRIP;
            break;

        case LINE_STRIP:
            primitiveCount = elementCount - 1;
            glPrimitiveType = GL_LINE_STRIP;
            break;

        case TRIANGLE_FAN:
            primitiveCount = elementCount - 2;
            glPrimitiveType = GL_TRIANGLE_FAN;
            break;
    }

}

//------------------------------------------------------------
unsigned Graphics::CreateFramebuffer() {
    unsigned newFbo = 0;

    glGenFramebuffers(1, &newFbo);
    return newFbo;
}

void Graphics::DeleteFramebuffer(unsigned fbo) {

    glDeleteFramebuffers(1, &fbo);
}

void Graphics::BindFramebuffer(unsigned fbo) {

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Graphics::BindColorAttachment(unsigned index, unsigned target, unsigned object,
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

void Graphics::BindDepthAttachment(unsigned object, bool isRenderBuffer) {
    if (!object)
        isRenderBuffer = false;


    {
        if (!isRenderBuffer)
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, object, 0);
        else
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, object);
    }
}

void Graphics::BindStencilAttachment(unsigned object, bool isRenderBuffer) {
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

bool Graphics::CheckFramebuffer() {

    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

bool Graphics::ResolveToTexture(Texture2D *texture) {
//    if (!texture)
//        return false;
//    RenderSurface *surface = texture->getRenderSurface();
//    if (!surface || !surface->GetRenderBuffer())
//        return false;
//
//    URHO3D_PROFILE(ResolveToTexture);
//
//    texture->setResolveDirty(false);
//    surface->SetResolveDirty(false);
//
//    // Use separate FBOs for resolve to not disturb the currently set rendertarget(s)
//    if (!impl_->resolveSrcFBO_)
//        impl_->resolveSrcFBO_ = CreateFramebuffer();
//    if (!impl_->resolveDestFBO_)
//        impl_->resolveDestFBO_ = CreateFramebuffer();
//
//
//    glBindFramebuffer(GL_READ_FRAMEBUFFER, impl_->resolveSrcFBO_);
//    glFramebufferRenderbuffer(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER,
//                              surface->GetRenderBuffer());
//    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, impl_->resolveDestFBO_);
//    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
//                           texture->getGPUObjectName(), 0);
//    glBlitFramebuffer(0, 0, texture->getWidth(), texture->getHeight(), 0, 0, texture->getWidth(),
//                      texture->getHeight(),
//                      GL_COLOR_BUFFER_BIT, GL_NEAREST);
//    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
//    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
//
//
//    // Restore previously bound FBO
//    BindFramebuffer(impl_->boundFBO_);
    return true;

}





