#include <jni.h>
#include <string>
#include <iostream>
#include "Context.h"
#include "Application.h"
#include "TestSample1.h"
#include "EngineSample.h"
#include "ShadowMapingDepthSample.h"
#include "ApplicationSystem.h"
using namespace std;


#define JNI_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_com_klin_klin_JNIAPI_JNIAPI_##method_name
#ifdef __cplusplus
extern "C" {
#endif

//测试jni
JNI_METHOD(jstring,stringFromJNI)(JNIEnv *env,jobject jobject1)
{
    std::string hello = "Hello from KLIN";
    return env->NewStringUTF(hello.c_str());
}


JNI_METHOD(jlong,intEngine)(JNIEnv *env,jobject jobject1,jobject assetManager,jint width,jint height)
{
    LOGE("引擎启动");
    jobject assetManagerTemp_ = env->NewGlobalRef(assetManager);
    AAssetManager* mgr = AAssetManager_fromJava(env,assetManagerTemp_);
    Context* context_ = new (std::nothrow)Context();
    context_->setSetAssetManager(mgr);
    ApplicationSystem* applicationSystem_ = new (std::nothrow)ApplicationSystem();
    applicationSystem_->initialEngine(context_,width,height);

    return (uintptr_t)(applicationSystem_);

}
JNI_METHOD(void,createSample)(JNIEnv *env,jobject jobject1,jlong ApplicationSystemClassId,jint width,jint height)
{
    LOGE("创建demo");
    ApplicationSystem* applicationSystem_ = (ApplicationSystem*)(ApplicationSystemClassId);


//    ShadowMapingDepthSample* testSample = new ShadowMapingDepthSample();
//    EngineSample* testSample = new EngineSample();
    TestSample1* testSample = new TestSample1();

    applicationSystem_->RegisteredApplication(testSample);

    applicationSystem_->CreateScence(width,height);

}

JNI_METHOD(void,renderFrame)(JNIEnv *env,jobject jobject1,jlong ApplicationSystemClassId)
{
//    LOGE("渲染frame");
    ApplicationSystem* applicationSystem_ = (ApplicationSystem*)(ApplicationSystemClassId);
    applicationSystem_->RenderOneFrame();
}


JNI_METHOD(void,engineRelease)(JNIEnv *env,jobject jobject1,jlong ApplicationSystemClassId)
{
    ApplicationSystem* applicationSystem_ = (ApplicationSystem*)(ApplicationSystemClassId);
    if(applicationSystem_ != NULL)
    {
        delete applicationSystem_;
        applicationSystem_ = NULL;
    }
}
#ifdef __cplusplus
}
#endif
