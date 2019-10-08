//
// Created by liuyizhou on 2019/7/18.
//

#pragma once

#include "ShaderProgram.h"

class GraphicsImpl {
    friend class Graphics;

public:
    GraphicsImpl();

    ~GraphicsImpl();

private:
    bool vertexBuffersDirty_;
    ShaderProgram *shaderProgram_;
    KL_Map<pair<ShaderVariation *, ShaderVariation *>, ShaderProgram *> shaderPrograms_;

    KL_Map<pair<char, string>, unsigned> vertexAttributes_;
    unsigned activeTexture_;
    unsigned textureTypes_[MAX_TEXTURE_UNITS];

    /// Read frame buffer for multisampled texture resolves.
    unsigned resolveSrcFBO_{};
    /// Write frame buffer for multisampled texture resolves.
    unsigned resolveDestFBO_{};
    /// Currently bound frame buffer object.
    unsigned boundFBO_{};

};

