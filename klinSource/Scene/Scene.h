//
// Created by liuyizhou on 2019/7/18.
//
#pragma once
#include "Node.h"

class Scene: public Node
{
    ENGINE_OBJECT(Scene,Node);
public:
    Scene(Context* context);

    ~Scene();

//    virtual bool load(std::string source, bool setInstanceDefault = false) override;

    /// Node added. Assign scene pointer and add to ID map.
    void NodeAdded(Node* node);
    /// Node removed. Remove from ID map.
    void NodeRemoved(Node* node);
    void ComponentRemoved(Component* component);
    /// Component added. Add to ID map.
    void ComponentAdded(Component* component);

private:
    float elapsedTime_;

    /// Local components by ID.
    KL_HashMap<unsigned, Component*> localComponents_;
};
