//
// Created by B612 on 2019/9/18.
//

#pragma once

#include "Application.h"
#include "View.h"
#include "Batch.h"
#include "Camera.h"
#include "Texture2D.h"
#include "Node.h"
#include "shader_m.h"
#include "Image.h"
class FboNode  {

public:
    FboNode(Context *context, View *view, Camera *camera,string imagePath);

    ~FboNode();

    void useFBO(unsigned  framebuffer_ID);

    unsigned  createFBO(int width, int height);
    void renderTo(Texture2D * T, unsigned  framebuffer_ID);
private:
    Context* Context_;
    View *view_;
    Batch batch_;
    Image* image_;
    string imagePath_;
    Camera *camera_;
    Texture2D *texture2D_;
    void  *quadVertices_;
    unsigned  quadVAO_;
    unsigned  quadVBO_;
    unsigned  framebuffer_;
    unsigned  textureColorbuffer_;
    unsigned  lutTexture_;
    ShaderTest* screenShader_;

};



