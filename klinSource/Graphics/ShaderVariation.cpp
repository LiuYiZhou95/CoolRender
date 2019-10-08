//
// Created by liuyizhou on 2019/7/18.
//

#include "ShaderVariation.h"
#include "Shader.h"
#include "Graphics.h"

const char *ShaderVariation::elementSemanticNames[] =
        {
                "Pos",
                "Normal",
                "BinNormal",
                "Tangetnt",//TANGENT
                "TexCoord",//TEXCOORD
                "Color",//COLOR
                "BlendWeight",//BLENDWEIGHT
                "BlendIndices",//BLENDINDICES
                "ObjectIndex"//OBJECTINDEX
        };

ShaderVariation::ShaderVariation(Shader *shader, ShaderType type):
        GPUObject(shader->getSubsystem<Graphics>()),
        owner_(shader),
        type_(type)
{
}

ShaderVariation::~ShaderVariation() {

}


bool ShaderVariation::Create() {
    if (!owner_) {
        LOGE("Owner shader has expired");
        return false;
    }

    object_.name_ = glCreateShader(type_ == VS ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    if (!object_.name_) {
        LOGE("Could not create shader object");
        return false;
    }

    const std::string &originalShaderCode = owner_->GetSourceCode(type_);
    //shader代码转换成字符串
    const char *shaderCStr = originalShaderCode.c_str();
    //获取shader字串
    glShaderSource(object_.name_, 1, &shaderCStr, nullptr);
    //编译shader
    glCompileShader(object_.name_);

    int compiled, length;
    //检测编译状态
    glGetShaderiv(object_.name_, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        glGetShaderiv(object_.name_, GL_INFO_LOG_LENGTH, &length);
        char *buf = (char *) malloc(length);
        int outLength;
        glGetShaderInfoLog(object_.name_, length, &outLength, buf);
        LOGE("CreateShader Error:%s", buf);
        free(buf);
        glDeleteShader(object_.name_);
        object_.name_ = 0;
    } else {
        LOGI("CreateShader Successful。");
    }
    return object_.name_ != 0;
}


void ShaderVariation::SetName(const std::string &name) {
    name_ = name;
}

Shader *ShaderVariation::GetShader() const {
    return owner_;
}