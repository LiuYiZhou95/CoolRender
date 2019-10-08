//
// Created by liuyizhou on 2019/7/18.
//
#pragma once
#include "Context.h"
#include "Resource.h"
class Image:public Resource
{
    ENGINE_OBJECT(Image,Resource)
public:
    Image(Context* context);

    virtual ~Image();

    bool loadImage(const std::string& filePath,int req_com = 0);

    int getImageWidth();

    int getImageHeight();

    int getImageComponents();

    unsigned char* getData();

    int loadTexture(const std::string &filePath);

protected:
    int width_;
    int height_;
    int components_;
    unsigned char*  data_;
};
