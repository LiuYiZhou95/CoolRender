//
// Created by liuyizhou on 2019/9/20.
//
#pragma once
#include "Object.h"
#include "Batch.h"
class Renderer:public Object
{
    ENGINE_OBJECT(Renderer,Object);
public:
    Renderer(Context* context);

    virtual ~Renderer();

    void updata(float timeStep);

    void render();

//    void setBatchShaders(Batch& batch);

    void setCullMode(CullMode mode,Camera* camera);
private:
    void initialize();

    void loadShaders();

    void releaseMaterialShaders();
};
