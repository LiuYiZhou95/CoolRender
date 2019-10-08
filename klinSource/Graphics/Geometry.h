//
// Created by liuyizhou on 2019/7/18.
//

#pragma once

#include "Object.h"
#include "DataStruct.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Graphics.h"
class IndexBuffer;
class Graphics;
class VertexBuffer;
class Geometry :Object{

    ENGINE_OBJECT(Geometry,Object);
public:
    /// Construct with one empty vertex buffer.
    explicit Geometry(Context* context);
    /// Destruct.
    ~Geometry();

    /// Set a vertex buffer by index.
    bool SetVertexBuffer(unsigned index, VertexBuffer* buffer);
    /// Set the index buffer.
    void SetIndexBuffer(IndexBuffer* buffer);
    void Draw(Graphics* graphics);
    /// Set the draw range.
    bool SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, bool getUsedVertexRange = true);
    /// Set the draw range.
    bool SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned vertexStart, unsigned vertexCount,
                      bool checkIllegal = true);
    bool IsEmpty() const { return indexCount_ == 0 && vertexCount_ == 0; }

private:
    IndexBuffer* indexBuffer_;
    std::vector<VertexBuffer*> vertexBuffers_;
    PrimitiveType primitiveType_;
    unsigned indexStart_;
    unsigned indexCount_;
    unsigned vertexStart_;
    unsigned vertexCount_;
};




