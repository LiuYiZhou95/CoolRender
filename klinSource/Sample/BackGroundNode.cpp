//
// Created by liuyizhou on 2019/9/11.
//

#include "BackGroundNode.h"
#include "Shader.h"
#include "ShaderVariation.h"
#include "ShaderProgram.h"
#include "Graphics.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Geometry.h"
#include <glm/ext.hpp>
#include "Image.h"

//
// node 继承
// Context_ 渲染上下文
// camera_ 摄像机
// view_ 当前视口
// imagePath_ 图片路径
// texture2D_ texture2D


BackGroundNode::BackGroundNode(Context *context, View *view, Camera *camera,string imagePath) :
        Node(context),
        Context_(context),
        camera_(camera),
        view_(view),
        texture2D_(nullptr),
        imagePath_(imagePath)
{

    this->setTexture(imagePath_);
    LOGE("创建纹理成功");

    Shader *shader_ = new Shader(Context_);
    string vs = "#version 300 es\n"
            "precision highp float;\n"
            "precision highp int;\n"
            "in vec3 iPos;\n"
            "in vec2 iTexCoord;\n"
            "in vec3 iNormal;\n"
            "uniform mat4 cMadel;\n"
            "uniform mat4 cView;\n"
            "uniform mat4 cViewProj;\n"
            "out vec2 vTexCoord;\n"
            "out vec3 vNormal;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = cViewProj * cView * cMadel * vec4(iPos.xyz,1.0);\n"
            "    //gl_Position = cView * cMadel * vec4(iPos.xyz,1.0);\n"
            "    vTexCoord = iTexCoord;\n"
            "    vNormal = iNormal;\n"
            "}//";
    string fs = "#version 300 es\n"
            "precision highp float;\n"
            "precision highp int;\n"
            "precision mediump sampler2D;\n"
            "uniform sampler2D sDiffuseMap;\n"
            "in vec3 vNormal;\n"
            "in vec2 vTexCoord;\n"
            "out vec4 fragColor;\n"
            "void main()\n"
            "{\n"
            "   vec2 nTexCoor = vec2(vNormal.y - vTexCoord.x,vNormal.y - vTexCoord.y);\n"
            "    vec4 color = texture(sDiffuseMap,nTexCoor);\n"
            "    fragColor = color;\n"
            "}//";
    shader_->SetShaderSourceCode(VS, vs);
    shader_->SetShaderSourceCode(PS, fs);

    ShaderVariation *vertexShader_ = new ShaderVariation(shader_, VS);
    ShaderVariation *pixelShader_ = new ShaderVariation(shader_, PS);

    //组建顶点几何数据
    VertexBuffer *vertexBuffer_ = new VertexBuffer(Context_);
    IndexBuffer *indexBuffer_ = new IndexBuffer(Context_);
    int index[] =
            {
                    0, 1, 2,
                    0, 2, 3
            };

    indexBuffer_->SetSize(6, true);
    indexBuffer_->SetData(index);
    Geometry *geometry_ = new Geometry(Context_);
    float vertex[] =
            {
                    1.0f, 1.7f, 0.0f, 1.f, 1.f, 0.0f, 1.0f, 0.0f,
                    -1.0f, 1.7f, 0.0f, 0.0f, 1.f, 0.0f, 1.0f, 0.0f,
                    -1.0f, -1.7f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                    1.0f, -1.7f, 0.0f, 1.f, 0.0f, 0.0f, 1.0f, 0.0f
            };

    std::vector<VertexElement> elements;

    elements.push_back(VertexElement(TYPE_VECTOR3, SEM_POSITION));
    elements.push_back(VertexElement(TYPE_VECTOR2, SEM_TEXCOORD));
    elements.push_back(VertexElement(TYPE_VECTOR3, SEM_NORMAL));

    vertexBuffer_->SetSize(4, elements);

    vertexBuffer_->setData(vertex);
    geometry_->SetIndexBuffer(indexBuffer_);
    geometry_->SetVertexBuffer(0, vertexBuffer_);

    batch_.geometry_ = geometry_;
    batch_.vertexShader_ = vertexShader_;
    batch_.pixelShader_ = pixelShader_;
    batch_.modelmatrix_ = this->getMat();

}

BackGroundNode::~BackGroundNode() {

}

Batch BackGroundNode::getBatch() {
//    batch_.isBatchDirty=true;
    batch_.modelmatrix_ = this->getMat();
    return batch_;
};


void BackGroundNode::setBatch() {

    batch_.texture2d_ =  new Texture2D(Context_);
    bool flag = batch_.texture2d_->setData(image_,true);
    batch_.texture2d_->setAddressMode(COORD_V, ADDRESS_BORDER);
    batch_.texture2d_->setAddressMode(COORD_U, ADDRESS_BORDER);

//    batch_.texture2d_ = texture2D_;
//    texture2D_->release();
//    batch_.setParam(view_,camera_,batch_.texture2d_);

}

void BackGroundNode::setTexture(std::string path) {
    Image *image = new Image(Context_);
    //测试机路径
    //    image->loadImage("/sdcard/SkySnowResources/CoreData/Textures/nobeauty.png");
    //自己手机路径
    image->loadImage(path);
    image_=image;

}
