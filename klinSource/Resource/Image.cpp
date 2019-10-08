//
// Created by liuyizhou on 2019/7/18.
//
#include "Image.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
Image::Image(Context *context):
    Resource(context),
    width_(0),
    height_(0),
    components_(0),
    data_(NULL)
{
}

Image::~Image()
{
    stbi_image_free(data_);
}

bool Image::loadImage(const std::string &filePath, int req_com)
{
    data_ = stbi_load(filePath.c_str(),&width_,&height_,&components_,req_com);

    if(req_com != 0 && components_ >req_com)
        components_ = req_com;
    if(nullptr == data_)
    {
        LOGE("Can't open the file.");
        return false;
    }else{
        LOGI("Load image success.");
        LOGI("image width:%d",width_);
        LOGI("image height:%d",height_);
        LOGI("image components:%d",components_);
        return true;
    }
}

int Image::getImageWidth()
{
    return width_;
}

int Image::getImageHeight()
{
    return height_;
}

int Image::getImageComponents()
{
    return components_;
}

unsigned char* Image::getData()
{
    return data_;
}

int Image::loadTexture(const std::string &filePath) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << filePath << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}