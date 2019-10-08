package com.klin.klin.JNIAPI;

import android.content.res.AssetManager;


public class JNIAPI
{
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("StudyCoreObjec");
    }

    public JNIAPI()
    {
    }

    public enum applicationType
    {
        ObjSample,
        DeferredRenderSample,
        ProductNormalMapSample,
        ParallaxMappingSample,
        GammaCorrectionSample,
        PBRLightTextureSample,
        NormalMapSample,
        HelloTriangleSample,
        MTTestSample,
        ShadowMapingDepthSample,
        FresnelReflectionSample
    }

    //=================

    public long InitialEngine(AssetManager ass, int width, int height)
    {
        return intEngine(ass,width,height);
    }

    public void RendererCreate(long ApplicationSystemClassId,int width,int height)
    {
        createSample(ApplicationSystemClassId,width,height);
    }

    public void RendererFrame(long ApplicationSystemClassId)
    {
        renderFrame(ApplicationSystemClassId);
    }
//
//    public void  moveObj(long ApplicationSystemClassId)
//    {
//        move(ApplicationSystemClassId);
//    }

    public void releaseEngine(long ApplicationSystemClassId)
    {
        engineRelease(ApplicationSystemClassId);
    }

    //=========================================================================================

    protected native long intEngine(AssetManager ass,int width,int height);

    protected native void createSample(long ApplicationSystemClassId,int width,int height);
    protected native void renderFrame(long ApplicationSystemClassId);


    protected native void engineRelease(long ApplicationSystemClassId);


    public native String stringFromJNI();
}