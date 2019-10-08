//
// Created by liuyizhou on 2019/7/18.
//
#pragma once

#include "Serializable.h"

class Animatable:public Serializable
{
    ENGINE_OBJECT(Animatable,Serializable);
public:
    Animatable(Context* context);

    virtual ~Animatable();
};