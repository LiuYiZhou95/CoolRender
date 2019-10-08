//
// Created by B612 on 2019/9/18.
//

#include "FboNode.h"
#include "Shader.h"
#include "ShaderVariation.h"
#include "ShaderProgram.h"
#include "Graphics.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Geometry.h"
#include <glm/ext.hpp>
#include "Image.h"
#include "shader_m.h"
//
// node 继承
// Context_ 渲染上下文
// camera_ 摄像机
// view_ 当前视口
// imagePath_ 图片路径
// texture2D_ texture2D


FboNode::FboNode(Context *context, View *view, Camera *camera, string imagePath) :
        Context_(context),
        camera_(camera),
        view_(view),
        texture2D_(nullptr),
//        screenShader_(shaderTest),
        imagePath_(imagePath),
        quadVAO_(0),
        quadVBO_(0) {

    Image *image = new Image(Context_);
    image_ = image;
    lutTexture_ = image_->loadTexture("/sdcard/klin/window.png");


}

FboNode::~FboNode() {

}


unsigned  FboNode::createFBO(int width, int height) {
    // framebuffer configuration
    // -------------------------
    glGenFramebuffers(1, &framebuffer_);
    // create a color attachment texture
    glGenTextures(1, &textureColorbuffer_);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);

    glBindTexture(GL_TEXTURE_2D,textureColorbuffer_);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer_,
                           0);


    glBindTexture(GL_TEXTURE_2D,0);



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

    return framebuffer_;
};

void FboNode::useFBO(unsigned  framebuffer_ID) {


};

void FboNode::renderTo(Texture2D *texture2D, unsigned  frameTextrue) {

    float quadVertices_[] = {
            // positions   // texCoords
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f
    };
//    quadVertices_ = &a;

    glGenVertexArrays(1, &quadVAO_);
    glGenBuffers(1, &quadVBO_);
    glBindVertexArray(quadVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices_), &quadVertices_, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *) (3 * sizeof(float)));

    screenShader_ = new ShaderTest("/sdcard/klin/shader/a.vs", "/sdcard/klin/shader/a.fs");
    screenShader_->use();
    screenShader_->setInt("screenTexture", 0);
    screenShader_->setInt("lutTexture", 1);


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0,1080,1920);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    screenShader_->use();

    glActiveTexture(GL_TEXTURE0);

//    texture2D->getGPUObjectName()
    glBindTexture(GL_TEXTURE_2D,
                  textureColorbuffer_);    // use the color attachment texture as the texture of the quad plane
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,
                  lutTexture_);    // use the color attachment texture as the texture of the quad plane

    glBindVertexArray(quadVAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}


