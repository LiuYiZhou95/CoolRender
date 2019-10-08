package com.klin.klin.GLBase;

import android.content.Context;
import android.opengl.GLES30;
import android.opengl.GLSurfaceView;
import android.util.DisplayMetrics;
import android.view.MotionEvent;
import android.view.WindowManager;

import com.klin.klin.JNIAPI.JNIAPI;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by liuyizhou on 2019/7/16.
 */

public class BaseRenderer implements GLSurfaceView.Renderer {

    private Context mContext;
    private JNIAPI mCoreObjectJNI;
    private long mApplicationSystemClassId;
    private Fps fps;

    public BaseRenderer(Context context) {
        mContext = context;
        mCoreObjectJNI = new JNIAPI();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        WindowManager wm = (WindowManager) (mContext.getSystemService(Context.WINDOW_SERVICE));
        DisplayMetrics dm = new DisplayMetrics();
        wm.getDefaultDisplay().getMetrics(dm);
        int mScreenWidth = dm.widthPixels;
        int mScreenHeight = dm.heightPixels;
        System.out.println("屏幕宽度"+mScreenWidth);
        System.out.println("屏幕高度"+mScreenHeight);
        //测试JNI连接
        //System.out.println(mCoreObjectJNI.stringFromJNI());

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        mApplicationSystemClassId = mCoreObjectJNI.InitialEngine(mContext.getAssets(), width, height);
        System.out.println("屏幕宽度onSurfaceChanged"+width);
        System.out.println("屏幕高度onSurfaceChanged"+height);

        mCoreObjectJNI.RendererCreate(mApplicationSystemClassId, width, height);
        fps = new Fps();
    }

    @Override
    public void onDrawFrame(GL10 gl) {
//        fps.makeFPS();
//        System.out.println(fps.getFPS() + " 当前FPS");
//        System.out.println("渲染循环");
        GLES30.glClearColor(0.1f, 0.1f, 0.2f, 1);
        GLES30.glClear(GLES30.GL_COLOR_BUFFER_BIT | GLES30.GL_DEPTH_BUFFER_BIT);
//        GLES30.glEnable(GLES30.GL_DEPTH_TEST);
        GLES30.glEnable(GLES30.GL_BLEND);
        GLES30.glBlendFunc(GLES30.GL_SRC_ALPHA, GLES30.GL_ONE_MINUS_SRC_ALPHA);
//        GLES30.glEnable(GLES30.GL_STENCIL_TEST);
//        GLES30.glEnable(GLES30.GL_SCISSOR_TEST);//启用剪裁测试
//        GLES30.glScissor(0,0,1000,2000);//设置区域（左下角坐标（0，0），宽度100，高度200）

        mCoreObjectJNI.RendererFrame(mApplicationSystemClassId);
//        GLES30.glDisable(GLES30.GL_SCISSOR_TEST);//禁用剪裁测试
//        GLES30.glDisable(GLES30.GL_STENCIL_TEST);
//        GLES30.glDisable(GLES30.GL_DEPTH_TEST);



    }

    public void release() {
        mCoreObjectJNI.releaseEngine(mApplicationSystemClassId);
    }

    //触控回调方法
//    public boolean onTouchEvent(MotionEvent e, JNIAPI.applicationType type)
//    {
//
//        switch (e.getAction())
//        {
//            case MotionEvent.ACTION_DOWN:
//
//                break;
//            case MotionEvent.ACTION_MOVE:
//                if(mCoreObjectJNI != null)
//                    mCoreObjectJNI.moveObj(mApplicationSystemClassId);
//                break;
//            case MotionEvent.ACTION_UP:
//                break;
//        }
//        return true;
//    }
}
