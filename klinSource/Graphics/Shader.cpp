//
// Created by liuyizhou on 2019/7/18.
//

#include "Shader.h"
#include "ShaderVariation.h"
Shader::Shader(Context *context):
        Object(context)
{

}

Shader::~Shader()
{

}

void Shader::SetShaderSourceCode(ShaderType type, std::string shaderCode)
{
    if(type == VS)
        vsSourceCode_ = shaderCode;
    else
        psSourceCode_ = shaderCode;
}