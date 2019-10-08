//
// Created by liuyizhou on 2019/7/18.
//
#pragma once
#include "Animatable.h"

class Node;
class Scene;
class Component :public Animatable
{
    ENGINE_OBJECT(Component,Animatable);
public:
    Component(Context* context);

    ~Component();

    void SetEnabled(bool enable);

    /// 从场景中移除，如果没有其他指针引用，立即执行
    void Remove();

    /// Return scene node.
    Node* GetNode() const { return node_; }

    /// Return the scene the node belongs to.
    Scene* GetScene() const;

    /// Return whether is enabled.
    bool IsEnabled() const { return enabled_; }

    /// Return ID.
    unsigned GetID() const { return id_; }

    /// Return whether the component is replicated or local to a scene.
    bool IsReplicated() const;

    /// Set ID. Called by Scene.
    void SetID(unsigned id);

    /// Handle scene being assigned. This may happen several times during the component's lifetime. Scene-wide subsystems and events are subscribed to here.
    virtual void OnSceneSet(Scene* scene);

    /// Handle scene node being assigned at creation.
    virtual void OnNodeSet(Node* node);

    /// Set scene node. Called by Node when creating the component.
    void SetNode(Node* node);
protected:

    /// Scene node.
    Node* node_;

    /// Enabled flag.
    bool enabled_;

    unsigned id_;

};
