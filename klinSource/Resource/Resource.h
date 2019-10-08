//
// Created by liuyizhou on 2019/7/18.
//
#pragma  once

#include "Object.h"


class Resource :public Object{
    ENGINE_OBJECT(Resource,Object)
public:
    Resource(Context* context);
    virtual ~Resource();
};



