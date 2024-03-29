//
// Created by liuyizhou on 2019/7/18.
//

#pragma once

#include "vec2.hpp"
#include "type_mat.hpp"
#include "type_mat4x4.hpp"
#include "Component.h"
class Geometry;
//class Material;
class Camera;
struct FrameInfo
{
    unsigned frameNumber_;
    float timeStep_;
    glm::vec2 viewSize_;
    Camera* camera_;
};

struct SourceBatch
{
    SourceBatch();

    SourceBatch(const SourceBatch& batch);

    ~SourceBatch();

    SourceBatch& operator=(const SourceBatch& rhs);

    Geometry* geometry_;

    glm::mat4 wordTransform_;

    float distance_;

    void* instancingData_;

//    Material* material_;

    unsigned numWorldTransforms_;
};

class Drawable:public Component
{
    ENGINE_OBJECT(Drawable,Component);
public:
    Drawable(Context* context);

    virtual ~Drawable();

    virtual void Update(const FrameInfo& frame) { }

    virtual void updateBatches(const FrameInfo& frame);
};
