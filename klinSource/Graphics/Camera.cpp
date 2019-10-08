//
// Created by liuyizhou on 2019/7/18.
//
#include "matrix_transform.hpp"
#include "Camera.h"


//右手矩阵
//cameraPos_:摄像机点
//cameraLookAt_：target点
//cameraUpvec_：摄像机头顶朝向
//fov：fov角度
//near:近平面
//far：远平面

Camera::Camera(Context *context):
    Component(context),
    cameraMat_(glm::mat4(1.0)),
    frustumMat_(glm::mat4(1.0)),
    cameraPos_(0.0f, 0.0f,  -4.5f),
    cameraLookAt_(0.0f, 0.0f, 5.0f),
    cameraUpvec_(0.0f, 1.0f,  0.0f),
    fov_(glm::radians(45.0f)),
    near_(0.1f),
    far_(100.0f),
    aspectRadio_(0.5625f),
    cameraDirty_(true),
    frustumDirty_(true)

{

}

Camera::~Camera()
{

}

void Camera::setCameraPosition(glm::vec3 cameraPos)
{
    cameraPos_ = cameraPos;
    cameraDirty_ = true;
}

void Camera::setCameraLookAt(glm::vec3 lookAt)
{
    cameraLookAt_ = lookAt;
    cameraDirty_ = true;
}

void Camera::setCameraUp(glm::vec3 upVec)
{
    cameraUpvec_ = upVec;
    cameraDirty_ = true;
}

glm::mat4 Camera::getCamera()
{
    if(cameraDirty_)
    {
        cameraMat_ = glm::lookAt(cameraPos_,cameraPos_+cameraLookAt_,cameraUpvec_);
        cameraDirty_ = false;
    }

    return cameraMat_;
}

void Camera::setFov(float fov)
{
    fov_ = fov;
    frustumDirty_ = true;
}

void Camera::setAspectRadio(float aspectRadio)
{
    aspectRadio_ = aspectRadio;
    frustumDirty_ = true;
}

void Camera::setNear(float near)
{
    near_ = near;
    frustumDirty_ = true;
}

void Camera::setFar(float far)
{
    far_ = far;
    frustumDirty_ = true;
}

glm::mat4 Camera::getFrustum()
{
    if(frustumDirty_)
    {
        frustumMat_ = glm::perspective(fov_, aspectRadio_, near_, far_);
        frustumDirty_ = false;
    }
    return frustumMat_;
}