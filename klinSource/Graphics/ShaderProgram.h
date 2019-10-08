//
// Created by liuyizhou on 2019/7/18.
//


#pragma once
#include "GPUObject.h"
#include "Graphics.h"

class ShaderProgram:public GPUObject
{
public:
    ShaderProgram(Graphics* graphics, ShaderVariation* vertexShader, ShaderVariation* pixelShader);

    virtual ~ShaderProgram();

    bool Link();

    ShaderVariation* GetVertexShader() const;

    ShaderVariation* GetPixelShader() const;

    const ShaderParameter* GetParameter(string param) const;

    const KL_Map<pair<char,string>, unsigned>& GetVertexAttributes() const { return vertexAttributes_; }
protected:
    ShaderVariation* vertexShader_;
    ShaderVariation* pixeShader_;
    KL_Map<string,ShaderParameter> shaderParameters_;
    KL_Map<pair<char,string>,unsigned> vertexAttributes_;
};
