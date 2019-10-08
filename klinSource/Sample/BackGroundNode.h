//
// Created by liuyizhou on 2019/9/11.
//
#pragma once

#include "Application.h"
#include "View.h"
#include "Batch.h"
#include "Camera.h"
#include "Texture2D.h"
#include "Node.h"
class BackGroundNode : public Node {
    ENGINE_OBJECT(BackGroundNode, Node);

public:
    BackGroundNode(Context *context, View *view, Camera *camera,string imagePath);

    ~BackGroundNode();

    Batch getBatch();

    void setBatch();

    void setTexture(std::string path);
private:
    Context *Context_;
    View *view_;
    Batch batch_;
    Image* image_;
    string imagePath_;
    Camera *camera_;
    Texture2D *texture2D_;
};


