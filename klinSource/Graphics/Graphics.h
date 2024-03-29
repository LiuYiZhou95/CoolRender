//
// Created by liuyizhou on 2019/7/18.
//

#ifndef KLIN_GRAPHICS_H
#define KLIN_GRAPHICS_H



#include "Object.h"
#include "DataStruct.h"
#include "ShaderVariation.h"
#include <vector>
#include "type_mat4x4.hpp"
#include "type_mat.hpp"
class VertexBuffer;
class IndexBuffer;
class GPUObject;
class GraphicsImpl;
class Texture;
class Texture2D;

class Graphics : public Object{
    ENGINE_OBJECT(Graphics,Object);
public:
    Graphics(Context* context);

    ~Graphics();

    //设置VBo的id
    void SetVBO(unsigned object);

    void SetIndexBuffer(IndexBuffer* buffer);

    void SetVertexBuffer(VertexBuffer* vertexBuffer);

    bool SetVertexBuffers(const std::vector<VertexBuffer*> buffers, unsigned instanceOffset = 0);

    void SetShaders(ShaderVariation* vs, ShaderVariation* ps);
    //设置数组类型的统一变量进GPU中
    void setShaderParameter(std::string param,const float* data, unsigned count);
    //设置4*4矩阵
    void setShaderParameter(std::string param,const glm::mat4 matrix);
    //设置最大4最小为1的向量数据
    void setShaderParameter(std::string param,const glm::vec4 vectorData);
    //设置int类型
    void setShaderParameter(std::string param,int value);
    //设置float类型
    void setShaderParameter(std::string param,float value);
    //设置布尔类型
    void setShaderParameter(std::string param,bool value);
    //设置纹理
    void setTexture(unsigned index, Texture* texture);
    //绑定纹理并更新纹理。
    void setTextureForUpdate(Texture* texture);
    //三角形卷绕绘制
    void Draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount);
    //索引法绘制
    void Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount);

    Texture* getTexture(unsigned index)const;

    TextureFilterMode getDefaultTextureFilterMode(){return defaultTextureFilterMode_;}

    unsigned getDefaultTextureAnisotropy()const {return defaultTextureAnisotropy_;}


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


private:
    /// Process dirtied state before draw.
    void PrepareDraw();

    void GetGLPrimitiveType(unsigned elementCount, PrimitiveType type, unsigned& primitiveCount, GLenum& glPrimitiveType);
    IndexBuffer* indexBuffer_;
    VertexBuffer* vertexBuffers_[MAX_VERTEX_STREAMS];
    GraphicsImpl* impl_;
    /// Vertex shader in use.
    ShaderVariation* vertexShader_;
    /// Pixel shader in use.
    ShaderVariation* pixelShader_;
    TextureFilterMode defaultTextureFilterMode_;
    unsigned defaultTextureAnisotropy_;
    Texture* textures_[MAX_TEXTURE_UNITS];
    /// Rendertargets in use.
//    RenderSurface* renderTargets_[MAX_RENDERTARGETS]{};

protected:




};


#endif //KLIN_GRAPHICS_H
