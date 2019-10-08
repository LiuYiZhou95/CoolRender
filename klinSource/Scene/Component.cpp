//
// Created by liuyizhou on 2019/7/18.
//
#include "Component.h"
#include "Scene.h"
Component::Component(Context *context):
    Animatable(context),
    node_(nullptr),
    enabled_(true)
{

}

Component::~Component()
{

}

void Component::Remove()
{
    if (node_)

        node_->RemoveComponent(this);
}

void Component::SetEnabled(bool enable)
{
    if (enable != enabled_)
    {
        enabled_ = enable;

    }
}

void Component::SetID(unsigned id)
{
    id_ = id;
}

void Component::OnSceneSet(Scene* scene)
{
}

void Component::OnNodeSet(Node* node)
{
}
void Component::SetNode(Node* node)
{
    node_ = node;
    OnNodeSet(node_);
}