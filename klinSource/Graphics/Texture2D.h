//
// Created by liuyizhou on 2019/7/18.
//
#pragma once
#include "Texture.h"
#include "RenderSurface.h"
class Image;
class Texture2D:public Texture
{
    ENGINE_OBJECT(Texture2D,Texture);
public:
    Texture2D(Context* context);

    virtual ~Texture2D();

    void release();

    bool setSize(int width,int height, unsigned format,TextureUsage usage = TEXTURE_RENDERTARGET,int multiSample = 1,bool autoResolve = true);

    bool setData(unsigned level, int x, int y, int width, int height, const void* data);
    bool setData(Image* image,bool useAlpha = false);
    /// Return render surface.
//    RenderSurface* getRenderSurface() const { return renderSurface_.get(); }

protected:
    virtual bool create() override;

private:
    /// Render surface.
//    shared_ptr<RenderSurface> renderSurface_;
};
