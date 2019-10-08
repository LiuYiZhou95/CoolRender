//
// Created by liuyizhou on 2019/7/18.
//
#pragma once

#include "Object.h"
#include "Context.h"
#include "DataStruct.h"

class Shader : public Object{
    ENGINE_OBJECT(Shader,Object);
public:
    Shader(Context* context);
    ~Shader();

    void SetShaderSourceCode(ShaderType type,std::string shaderCode);

    const string& GetSourceCode(ShaderType type) const { return type == VS ? vsSourceCode_ : psSourceCode_; }

private:
    std::string vsSourceCode_;
    std::string psSourceCode_;

};



