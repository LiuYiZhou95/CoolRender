//
// Created by liuyizhou on 2019/7/18.
//
#pragma once

#include "Object.h"
#include "GPUObject.h"
#include "Graphics.h"

class IndexBuffer : public Object,public GPUObject{
    ENGINE_OBJECT(IndexBuffer,Object)
public:
    IndexBuffer(Context* context);
    ~IndexBuffer();

    /// Set size and vertex elements and dynamic mode. Previous data will be lost.
    bool SetSize(unsigned indexCount, bool largeIndices, bool dynamic = false);
    /// Set all data in the buffer.
    bool SetData(const void* data);
    /// Return whether is dynamic.
    bool IsDynamic() const { return dynamic_; }

    /// Return number of indices.
    unsigned GetIndexCount() const { return indexCount_; }

    /// Return index size in bytes.
    unsigned GetIndexSize() const { return indexSize_; }
private:
    /// Create buffer.
    bool Create();
    /// Update the shadow data to the GPU buffer.
    bool UpdateToGPU();
    /// Number of indices.
    unsigned indexCount_;
    /// Index size.
    unsigned indexSize_;
    /// Dynamic flag.
    bool dynamic_;
};


