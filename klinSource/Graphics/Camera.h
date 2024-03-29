//
// Created by liuyizhou on 2019/7/18.
//
#pragma once

#include "vec3.hpp"
#include "type_mat4x4.hpp"
#include "type_mat.hpp"
#include "Component.h"

class Camera : public Component
{
    ENGINE_OBJECT(Camera,Component);
public:
    Camera(Context* context);

    virtual ~Camera();

    void setCameraPosition(glm::vec3 cameraPos);

    void setCameraLookAt(glm::vec3 lookAt);

    void setCameraUp(glm::vec3 upVec);

    glm::mat4 getCamera();

    void setFov(float fov);

    void setAspectRadio(float aspectRadio);

    void setNear(float near);

    void setFar(float far);

    glm::mat4 getFrustum();

protected:


private:

    bool cameraDirty_;
    glm::vec3 cameraPos_;
    glm::vec3 cameraUpvec_;
    glm::vec3 cameraLookAt_;
    glm::mat4 cameraMat_;

    bool frustumDirty_;
    float fov_;
    float aspectRadio_;
    float near_;
    float far_;
    glm::mat4 frustumMat_;
};
