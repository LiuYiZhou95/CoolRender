//
// Created by liuyizhou on 2019/9/11.
//


#include "TestSample1.h"
#include "Shader.h"
#include "ShaderVariation.h"
#include "ShaderProgram.h"
#include "Graphics.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "DataStruct.h"
#include "Geometry.h"
#include "View.h"
#include "Scene.h"
#include <glm/ext.hpp>
#include "Texture2D.h"
#include "Image.h"
#include "BackGroundNode.h"
#include "shader_m.h"
#include <chrono>
#include "FboNode.h"


using namespace std::chrono;

double fps() {
    static double fps = 0.0;
    static int frameCount = 0;
    static auto lastTime = system_clock::now();
    static auto curTime = system_clock::now();

    curTime = system_clock::now();

    auto duration = duration_cast<microseconds>(curTime - lastTime);
    double duration_s =
            double(duration.count()) * microseconds::period::num / microseconds::period::den;

    if (duration_s > 2)//2秒之后开始统计FPS
    {
        fps = frameCount / duration_s;
        frameCount = 0;
        lastTime = curTime;
    }

    ++frameCount;

    return fps;
}

using namespace std;

TestSample1::TestSample1() :
        view_(nullptr),
        camera_(nullptr),
        texture2D_(nullptr),
        i(0.0) {


}

TestSample1::~TestSample1() {
    if (view_) {
        delete view_;
        view_ = nullptr;
    }

    if (camera_) {
        delete camera_;
        camera_ = nullptr;
    }

    if (texture2D_) {
        delete texture2D_;
        texture2D_ = nullptr;
    }
}


void TestSample1::RenderOneFrame(Context *context) {
//    LOGE("当前FPS%d", (int) fps());
//  batch_.Draw(view_,camera_,batch_.texture2d_);

    i += 0.01f;
//  batch_1.Draw(view_,camera_,texture2D_1);
    float radius = 1.0f;
    float camX = sin(i) * radius;
    float camY = cos(i) * radius;


    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFbo);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    for (int i = scene_->GetAllChildren().size() - 1; i >= 0; --i) {
        Batch temp = ((BackGroundNode *) scene_->GetChild(i))->getBatch();
        //view_->GetGraphics()->setTexture(0,temp.texture2d_);
        temp.Draw(view_, camera_, temp.texture2d_);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glDisable(GL_DEPTH_TEST);

    glViewport(0, 0, width_, height_);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderTest->use();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, lutMap);//depthMap
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMap);//depthMap

    RenderQuad();

    glEnable(GL_DEPTH_TEST);


        Batch temp = ((BackGroundNode *) scene_->GetChild(2))->getBatch();
        //view_->GetGraphics()->setTexture(0,temp.texture2d_);
        temp.Draw(view_, camera_, temp.texture2d_);


}


void TestSample1::Move(float tx, float ty, float tz) {

//    batch_.modelmatrix_ = batch_.modelmatrix_ * glm::translate(glm::vec3(tx, ty, tz));
//    batch_bg.modelmatrix_=batch_bg.modelmatrix_*glm::translate(glm::vec3(tx,ty,tz));

}

void TestSample1::CreateScence(Context *context, int width, int height) {

    width_ = width;
    height_ = height;

    glViewport(0, 0, width, height);
    scene_ = new Scene(context);

    camera_ = new Camera(context);
    camera_->setAspectRadio((float) width / (float) height);

    view_ = new View(context);


    BackGroundNode *backGroundNode1 = new BackGroundNode(context, view_, camera_,
                                                         "/sdcard/klin/human/human2.png");

    backGroundNode1->SetPosition(0, 0.0, 0.0);
    backGroundNode1->setBatch();
    scene_->AddChild(scene_, backGroundNode1);


    BackGroundNode *face1 = new BackGroundNode(context, view_, camera_, "/sdcard/klin/face1.png");
    face1->SetScale(0.05, 0.05, 0.0);
    face1->SetPosition(-0.2, -0.1, 0.0);
    face1->setBatch();
    scene_->AddChild(scene_, face1);

    BackGroundNode *face2 = new BackGroundNode(context, view_, camera_, "/sdcard/klin/face2.png");
    face2->SetScale(0.1, 0.1, 0.0);
    face2->SetPosition(0.4, 0.3, 0.0);
    face2->setBatch();
    scene_->AddChild(scene_, face2);

    BackGroundNode *face3 = new BackGroundNode(context, view_, camera_, "/sdcard/klin/face3.png");
    face3->SetScale(0.1, 0.1, 0.0);
    face3->SetPosition(-0.4, 0.5, 0.0);
    face3->setBatch();
    scene_->AddChild(scene_, face3);

    BackGroundNode *border = new BackGroundNode(context, view_, camera_,
                                                "/sdcard/klin/border/border1.png");
    border->setBatch();
    scene_->AddChild(scene_, border);

    createFBO(width, height);

    shaderTest = new ShaderTest("/sdcard/klin/shader/a/a.vs", "/sdcard/klin/shader/a/a.fs");
    shaderTest->use();
    shaderTest->setInt("screenTexture", 0);
    shaderTest->setInt("lutTexture", 1);

    Image *image = new Image(context);
    lutMap = image->loadTexture("/sdcard/klin/window.png");



}


void TestSample1::createFBO(int width, int height) {
    // framebuffer configuration

    // -------------------------
    glGenFramebuffers(1, &depthMapFbo);
    // create a color attachment texture
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_CLAMP_TO_BORDER_EXT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_BORDER_EXT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFbo);

    glBindTexture(GL_TEXTURE_2D, depthMap);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, depthMap, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
//    unsigned int rbo;
//    glGenRenderbuffers(1, &rbo);
//    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width,
//                          height); // use a single renderbuffer object for both a depth AND stencil buffer.
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER,
//                              rbo); // now actually attach it
//    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

};

void TestSample1::RenderQuad() {
    if (quadVAO_ == 0) {
        float quadVertices[] = {
                // positions        // texture Coords
                -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO_);
        glGenBuffers(1, &quadVBO_);
        glBindVertexArray(quadVAO_);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                              (void *) (3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO_);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}