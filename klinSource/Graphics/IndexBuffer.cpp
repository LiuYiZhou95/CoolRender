//
// Created by liuyizhou on 2019/7/18.
//

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Context *context) :
    Object( context),
    GPUObject(getSubsystem<Graphics>()),
    indexCount_(0),
    indexSize_(0),
    dynamic_(false)
{
}
IndexBuffer::~IndexBuffer() {

}

bool IndexBuffer::SetData(const void *data) {
    if(!data)
    {
        LOGE("Null pointer for index buffer data.");
        return false;
    }
    if(!indexSize_)
    {
        LOGE("Index size not defined, can not set index buffer data");

        return false;
    }
    if(object_.name_)
    {
        graphics_->SetIndexBuffer(this);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount_ * indexSize_, data, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }
    dataLost_ = false;
    return true;
}

bool IndexBuffer::SetSize(unsigned indexCount, bool largeIndices, bool dynamic) {
    indexCount_ = indexCount;
    indexSize_ = (unsigned)(largeIndices ? sizeof(unsigned) : sizeof(unsigned short));
    dynamic_ = dynamic;

    return Create();
}

bool IndexBuffer::Create() {
    if(!indexCount_)
    {
        LOGE("index buffer indexCount is null.");
        return false;
    }

    if(graphics_)
    {
        if(!object_.name_)
            glGenBuffers(1,&object_.name_);
        if(!object_.name_)
        {
            LOGE("Failed to create index buffer");
            return false;
        }
        graphics_->SetIndexBuffer(this);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount_ * indexSize_, nullptr, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }
    return true;
}