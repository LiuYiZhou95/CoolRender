//
// Created by liuyizhou on 2019/7/18.
//

#include "GraphicsImpl.h"

GraphicsImpl::GraphicsImpl():
        vertexBuffersDirty_(false),
        shaderProgram_(nullptr),
        activeTexture_(0)
{

}

GraphicsImpl::~GraphicsImpl()
{

}