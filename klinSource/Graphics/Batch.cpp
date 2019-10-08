//
// Created by liuyizhou on 2019/7/18.
//
#include "glm/ext.hpp"
#include "Batch.h"
#include "Geometry.h"
#include "Graphics.h"
#include "View.h"
#include "Camera.h"


void Batch::Prepare(View *view, Camera *camera, Texture *texture2d) {
    if (!vertexShader_ || !pixelShader_)
        return;

    Graphics *graphics = view->GetGraphics();
    graphics->setTexture(0, texture2d);
    //设置着色器
    graphics->SetShaders(vertexShader_, pixelShader_);
    //设置模型矩阵
    graphics->setShaderParameter(VSP_MODEL, modelmatrix_);
    //设置相机相关的参数
    view->setCameraShaderParameters(camera);
}

void Batch::setParam(View *view, Camera *camera, Texture *texture2d) {
    if (!geometry_->IsEmpty()) {
        Prepare(view, camera, texture2d);
    }
}

void Batch::Draw(View *view, Camera *camera, Texture *texture2d) {
    if (!geometry_->IsEmpty()) {
        Prepare(view, camera, texture2d);

        geometry_->Draw(view->GetGraphics());

    }
}


void Batch::Prepare(View *view, Camera *camera) {
    if (!vertexShader_ || !pixelShader_)
        return;
    Graphics *graphics = view->GetGraphics();
    //设置着色器
    graphics->SetShaders(vertexShader_, pixelShader_);
    //设置模型矩阵
    graphics->setShaderParameter(VSP_MODEL, modelmatrix_);
    //设置相机相关的参数
    view->setCameraShaderParameters(camera);
}

void Batch::Draw(View *view, Camera *camera) {
    if (!geometry_->IsEmpty()) {
        Prepare(view, camera);
        geometry_->Draw(view->GetGraphics());
    }
}

void BatchGroup::Draw(View *view, bool allowDepthWrite) const {

}
