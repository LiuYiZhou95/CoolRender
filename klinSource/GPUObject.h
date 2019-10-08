//
// Created by liuyizhou on 2019/7/18.
//


#pragma once

//GPUObjectHandle生成一个标识，用来表示gl命令生成的buffer texture等
//GPUObject
//CPU传入GPU数据的标识类
#include "Common.h"
using namespace std;
class Graphics;
union GPUObjectHandle
{
    unsigned name_;
};

class GPUObject
{
public:
    GPUObject(Graphics* graphics);
    unsigned getGPUObjectName();

protected:
    GPUObjectHandle object_;
    Graphics* graphics_;
    bool dataLost_;
};
