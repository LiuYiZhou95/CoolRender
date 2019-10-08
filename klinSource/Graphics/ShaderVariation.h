//
// Created by liuyizhou on 2019/7/18.
//

#pragma once

#include "Shader.h"
#include "GPUObject.h"

class Shader;

//一个shader的参数
struct ShaderParameter {
    ShaderParameter() {}

    ShaderType type_;
    std::string name_;
    int location_;
    unsigned glType_;
};

//shader的属性，区别于shader.h
//该类主要是得到shader的string块，是ShaderVariation的一个属性
//而本类是一个shader的全部属性以及操作函数
//Vertex or pixel shader on the GPU.

class ShaderVariation : public  GPUObject {
public:
    ShaderVariation(Shader *shader, ShaderType type);

    ~ShaderVariation();

    void SetName(const std::string &name);

    bool Create();

    ShaderType GetShaderType() const { return type_; }

    const std::string &GetName() const { return name_; }

    Shader *GetShader() const;

    static const char *elementSemanticNames[];

private:
    ShaderType type_;
    std::string name_;
    Shader *owner_;

};


