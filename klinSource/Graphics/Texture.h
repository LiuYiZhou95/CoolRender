//
// Created by liuyizhou on 2019/7/18.
//
#pragma once

#include "Resource.h"
#include "GPUObject.h"
#include "DataStruct.h"

class Texture : public Resource, public GPUObject {
ENGINE_OBJECT(Texture, Resource);
public:
    Texture(Context *context);

    virtual ~Texture();

    void setNumLevels(unsigned levels);

    void setFilterMode(TextureFilterMode mode);

    void setAddressMode(TextureCoordinate coord, TextureAddressMode mode);

//    void regenerateLevels();

    void updateParameters();

    bool getParametersDirty() const;

    unsigned getTarget() const { return target_; }

    TextureUsage getUsage() const { return usage_; }

    unsigned getExternalFormat(unsigned format);

    unsigned getDataType(unsigned format);

    /// Return number of mip levels.
    unsigned GetLevels() const { return levels_; }

    /// Return width.
    int getWidth() const { return width_; }

    /// Return height.
    int getHeight() const { return height_; }

    /// Return depth.
    int getDepth() const { return depth_; }

    /// Return texture multisampling level (1 = no multisampling).
    int getMultiSample() const { return multiSample_; }

    /// Return texture multisampling autoresolve mode. When true, the texture is resolved before being sampled on SetTexture(). When false, the texture will not be resolved and must be read as individual samples in the shader.
    bool getAutoResolve() const { return autoResolve_; }

    /// Return backup texture.
    Texture *GetBackupTexture() const { return backupTexture_.get(); }

    /// Return whether multisampled texture needs resolve.
    bool isResolveDirty() const { return resolveDirty_; }

    /// Set backup texture to use when rendering to this texture.
    void setBackupTexture(Texture *texture);

    /// Set or clear the need resolve flag. Called internally by Graphics.
    void setResolveDirty(bool enable) { resolveDirty_ = enable; }

protected:
    virtual bool create() {
        return true;
    }

    //将纹理对象绑定到GL_TEXTURE_2D、GL_TEXTURE_3D、GL_TEXTURE_2D_ARRAY或者GL_TEXTURE_CUBE_MAP等
    unsigned target_;
    //输入的纹理数据格式。比如说：GL_RED等
    unsigned format_;
    //纹理的宽
    int width_;
    //纹理的高
    int height_;
    ///纹理的深度
    int depth_;
    /// 纹理使用的类型.
    TextureUsage usage_;

    unsigned levels_;

//    unsigned requestedLevels_;

    bool parametersDirty_;

    TextureFilterMode filterMode_;

    TextureAddressMode addressMode_[MAX_COORDS];

    //是否使用SRGB
    bool sRGB_;

    bool levelsDirty_;

    unsigned anisotropy_;

    bool shadowCompare_;

    /// Multisampling level.
    int multiSample_{1};

    /// Multisampling autoresolve flag.
    bool autoResolve_{};
/// Multisampling resolve needed -flag.
    bool resolveDirty_{};
    /// Backup texture.
    shared_ptr<Texture> backupTexture_;
};