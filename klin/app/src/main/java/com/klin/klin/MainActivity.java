package com.klin.klin;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.klin.klin.GLBase.GLView;

public class MainActivity extends AppCompatActivity {

    private GLView mGLView;
    private String mAssetsPath = "SkySnowResources";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
//        mGLView = new GLView(this);
//        setContentView(mGLView);
        mGLView = (GLView) findViewById(R.id.gl_view);
//        setContentView(mGLView);
    }


    @Override
    protected void onPause() {
        super.onPause();
        mGLView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mGLView.onResume();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mGLView.release();
    }
}
