//
// Created by liuyizhou on 2019/7/18.
//

#include "View.h"
#include "Graphics.h"
#include "Camera.h"

View::View(Context *context):
        Object(context),
        graphics_(getSubsystem<Graphics>())
{

}

View::~View()
{

}
Graphics* View::GetGraphics() const
{
    return graphics_;
}

void View::setCameraShaderParameters(Camera* camera)
{
    graphics_->setShaderParameter(VSP_VIEW,camera->getCamera());
    graphics_->setShaderParameter(VSP_VIEWPROJ,camera->getFrustum());
}

void View::Update()
{

}

void View::Render()
{

}



