//
// Created by liuyizhou on 2019/9/11.
//
#pragma once
#ifndef KLIN_TESTSAMPLE1_H
#define KLIN_TESTSAMPLE1_H

#include "Application.h"
#include "View.h"
#include "Batch.h"
#include "Camera.h"
#include "Texture2D.h"
#include "BackGroundNode.h"
#include "Scene.h"
#include "FboNode.h"

class TestSample1 : public Application {

public:
    TestSample1();

    ~TestSample1();

    virtual void CreateScence(Context *context, int width, int height);

    virtual void RenderOneFrame(Context *context);

    virtual void Move(float tx, float ty, float tz);


    void createFBO(int width, int height);

    void RenderQuad();

private:
    Context *Context_;
    Scene *scene_;
    View *view_;
    Batch batch_;

    Camera *camera_;
    Texture2D *texture2D_;
    float i;

    unsigned quadVAO_=0;
    unsigned quadVBO_;
    unsigned depthMapFbo;
    unsigned depthMap = 0;
    unsigned lutMap = 0;
    ShaderTest *shaderTest;
    int width_;
    int height_;

};


#endif //KLIN_TESTSAMPLE1_H

