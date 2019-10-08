//
// Created by liuyizhou on 2019/4/17.
//

#include "ApplicationSystem.h"
#include "../Graphics/Graphics.h"
//#include "File.h"

ApplicationSystem::ApplicationSystem():
        CurrApplication_(NULL),
        context_(NULL)
{

}

ApplicationSystem::~ApplicationSystem()
{
    if(CurrApplication_ != NULL)
    {
        delete CurrApplication_;
        CurrApplication_ = NULL;
    }
    if(context_ != NULL)
    {
        delete context_;
        context_ = NULL;
    }
}

void ApplicationSystem::initialEngine(Context* context,int width,int height)
{
    context_ = context;
    //引擎启动，我们注册相关的渲染core对象
    Graphics* graphics = new Graphics(context_);
    context_->registerSubsystem(graphics);

    height_ = height;
    width_ = width;
}

void ApplicationSystem::RegisteredApplication(Application *application)
{
    if(CurrApplication_ != NULL)
    {
        delete CurrApplication_;
        CurrApplication_ = NULL;
    }
    CurrApplication_ = application;
}

void ApplicationSystem::CreateScence(int width, int height)
{
    if(CurrApplication_ == NULL)
    {
        LOGE("ApplicationSystem.cpp Application is NULL pointer!");
        return ;
    }
    CurrApplication_->BaseCreateScence(context_,width,height);
}

Context* ApplicationSystem::getContext()
{
    return context_;
}



void ApplicationSystem::RenderOneFrame()
{
    if(!CurrApplication_->isInitial())
        CreateScence(width_,height_);
    if(CurrApplication_ == NULL)
    {
        LOGE("ApplicationSystem.cpp Application is NULL pointer!");
        return ;
    }
    CurrApplication_->RenderOneFrame(context_);
}