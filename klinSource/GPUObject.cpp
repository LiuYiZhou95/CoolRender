//
// Created by liuyizhou on 2019/7/18.
//

#include "GPUObject.h"

GPUObject::GPUObject(Graphics *graphics):
        graphics_(graphics),
        dataLost_(false)
{
    object_.name_ = 0;
}

unsigned GPUObject::getGPUObjectName()
{
    return object_.name_;
}