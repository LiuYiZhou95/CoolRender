//
// Created by liuyizhou on 2019/7/18.
//

#pragma once

#include "Object.h"
#include "Context.h"
#include "DataStruct.h"
#include "Graphics.h"

class VertexBuffer: public Object,public GPUObject
{
ENGINE_OBJECT(VertexBuffer,Object);
public:
    VertexBuffer(Context* context);

    ~VertexBuffer();

    bool SetSize(unsigned vertexCount, const std::vector<VertexElement>& elements,bool dynamic = false);

    bool setData(const void* data);

    unsigned GetVertexCount() const {return vertexCount_;}

    unsigned GetVertexSize()const {return vertexSize_;}

    std::vector<VertexElement> GetElements() const {return elements_;}

protected:


private:
    void UpdateOffsets();

    bool Create();

    unsigned vertexCount_;

    unsigned vertexSize_;

    std::vector<VertexElement> elements_;

    bool dynamic_;
};

