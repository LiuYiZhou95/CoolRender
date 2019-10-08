//
// Created by liuqian8 on 2019/5/29.
//
#include <glm/ext.hpp>
#include "EngineSample.h"
#include "Graphics.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "DataStruct.h"
#include "View.h"
#include "ShaderProgram.h"
#include "ShaderVariation.h"
#include "Shader.h"
#include "Geometry.h"
#include "Texture2D.h"
#include "Image.h"
EngineSample::EngineSample():
        view_(nullptr),
        camera_(nullptr),
        texture2D_(nullptr)
{

}

EngineSample::~EngineSample()
{
    if(view_)
    {
        delete view_;
        view_ = nullptr;
    }

    if(camera_)
    {
        delete camera_;
        camera_ = nullptr;
    }

    if(texture2D_)
    {
        delete texture2D_;
        texture2D_ = nullptr;
    }
}

void EngineSample::CreateScence(Context *context, int width, int height)
{
    Context_ = context;
    Shader* shader_ = new Shader(context);
    string vs="#version 300 es\n"
            "precision highp float;\n"
            "precision highp int;\n"
            "in vec4 iPos;\n"
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
            "    vTexCoord = iTexCoord;\n"
            "    vNormal = iNormal;\n"
            "}//";
    string fs="#version 300 es\n"
            "precision highp float;\n"
            "precision highp int;\n"
            "uniform sampler2D sDiffuseMap;\n"
            "uniform vec4 cColor;\n"
            "in vec3 vNormal;\n"
            "in vec2 vTexCoord;\n"
            "out vec4 fragColor;\n"
            "void main()\n"
            "{\n"
            "   vec2 nTexCoor = vec2(vNormal.y - vTexCoord.x,vNormal.y - vTexCoord.y);\n"
            "    vec4 color = texture(sDiffuseMap,nTexCoor);\n"
            "    fragColor = color;\n"
            "}//";

    shader_->SetShaderSourceCode(VS,vs);
    shader_->SetShaderSourceCode(PS,fs);
    
    ShaderVariation* vertexShader_ = new ShaderVariation(shader_,VS);
    ShaderVariation* fragmentShader_ = new ShaderVariation(shader_,PS);

    //组建顶点几何数据
    VertexBuffer* vertexBuffer_ = new VertexBuffer(context);
    IndexBuffer* indexBuffer_ = new IndexBuffer(context);
    int index[] =
    {
        0,1,2,
        0,2,3
    };

    indexBuffer_->SetSize(6,true);
    indexBuffer_->SetData(index);
    Geometry* geometry_ = new Geometry(context);
    Geometry* geometry_1 = new Geometry(context);

    float vertex[] =
    {
             1.0f,  1.0f,  0.0f,  1.0f,  1.0f,   0.0f, 1.0f, 0.0f,
            -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,   0.0f, 1.0f, 0.0f,
            -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,   0.0f, 1.0f, 0.0f,
             1.0f, -1.0f,  0.0f,  1.0f,  0.0f,   0.0f, 1.0f, 0.0f
    };
    std::vector<VertexElement> elements;

    elements.push_back(VertexElement(TYPE_VECTOR3,SEM_POSITION));
    elements.push_back(VertexElement(TYPE_VECTOR2,SEM_TEXCOORD));
    elements.push_back(VertexElement(TYPE_VECTOR3,SEM_NORMAL));

    vertexBuffer_->SetSize(4,elements);

    vertexBuffer_->setData(vertex);
    geometry_->SetIndexBuffer(indexBuffer_);
    geometry_->SetVertexBuffer(0,vertexBuffer_);

    geometry_1->SetIndexBuffer(indexBuffer_);
    geometry_1->SetVertexBuffer(0,vertexBuffer_);

    camera_ = new Camera(context);
    camera_->setAspectRadio((float)width/(float)height);

    view_ = new View(context);

    batch_.geometry_ = geometry_;
    batch_.vertexShader_ = vertexShader_;
    batch_.pixelShader_ = fragmentShader_;
    batch_.modelmatrix_ = glm::translate(glm::vec3(0,-0,1))*glm::rotate(0.0f,glm::vec3(0,1,0))*
            glm::rotate(0.0f,glm::vec3(1,0,0))*glm::scale(glm::vec3(1.0f,1.0f,1.0f));



    Image* image = new Image(context);
    image->loadImage("/sdcard/klin/1.jpg");
    texture2D_ = new Texture2D(context);
    bool flag = texture2D_->setData(image);
    if(flag)
        LOGE("创建纹理成功。");


    batch_2.geometry_ = geometry_1;
    batch_2.vertexShader_ = vertexShader_;
    batch_2.pixelShader_ = fragmentShader_;
    batch_2.modelmatrix_ = glm::translate(glm::vec3(0.1,0.3,1))*glm::rotate(0.0f,glm::vec3(0,1,0))*
                          glm::rotate(0.0f,glm::vec3(1,0,0))*glm::scale(glm::vec3(1.0f,1.0f,1.0f));
    Image* image1 = new Image(context);
    image1->loadImage("/sdcard/klin/test.png");
    texture2D_2 = new Texture2D(context);
    bool flag1 = texture2D_2->setData(image1);
    if(flag)
        LOGE("创建纹理成功。");

}

void EngineSample::RenderOneFrame(Context *context)
{
    view_->GetGraphics()->setTexture(0,texture2D_);

    batch_.Draw(view_,camera_);
    view_->GetGraphics()->setTexture(0,texture2D_2);

    batch_2.Draw(view_,camera_);

}

void EngineSample::Move()
{

}
