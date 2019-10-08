//
// Created by liuyizhou on 2019/7/18.
//
#pragma once
#include "Common.h"
#include "Object.h"
#if PLATFORM == PLATFORM_ANDROID
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#endif

class Context
{
    friend class Object;
public:
    Context()
    {
    }
    ~Context();

    Object* CreateObject(string objectType);

    void registerSubsystem(Object* subsystem);

    Object* getSubsystem(string type) const;

    void removeSubsystem(string ObjectType);

    template <class T> T* getSubsystem() const;

#if PLATFORM == PLATFORM_ANDROID
    void setSetAssetManager(AAssetManager *mgr)
    {
        if(nullptr == mgr)
            LOGE("AAssetManager is null pointer. -----Context.cpp.");
        mgr_ = mgr;
    }

    AAssetManager* getAAssetManager()
    {
        if(nullptr == mgr_)
            LOGE("AAssetManager is null pointer. -----Context.cpp.");
        return mgr_;
    }
#endif
protected:
    KL_HashMap<string ,Object*> subsystem_;
#if PLATFORM == PLATFORM_ANDROID
    AAssetManager* mgr_;
#endif
};

template <class T> T* Context::getSubsystem() const
{
    return static_cast<T*> (getSubsystem(T::getTypeNameStatic()));
}
