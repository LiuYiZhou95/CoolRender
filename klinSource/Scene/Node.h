//
// Created by liuyizhou on 2019/7/18.
//
#pragma once

#include "Animatable.h"
#include "vec3.hpp"
#include "vec2.hpp"
#include "quaternion.hpp"

/// Component and child node creation mode for networking.
enum CreateMode {
    REPLICATED = 0,
    LOCAL = 1
};

/// 为平移和旋转变换空间
enum TransformSpace {
    TS_LOCAL = 0,
    TS_PARENT,
    TS_WORLD
};

class Component;

class Scene;

class Node : public Animatable {
ENGINE_OBJECT(Node, Animatable);

public:
    Node(Context *context);

    ~Node();

    glm::mat4 getMat();

    //设置当前节点在父空间的坐标，如果当前节点是空间节点的叶子节点，则等同于设置在世界空间的坐标
    void SetPosition(const glm::vec3 &position);

    void SetPosition(float tx, float ty, float tz);

    // 在父空间中设置旋转。四元数方式
    void SetRotation(const glm::quat &rotation);

    void SetRotate(const glm::vec3 &rotate, const float rotateAngle);

    void SetRotate(float tx, float ty, float tz, float rotateAngle);


    // 父空间设置缩放
    void SetScale(float scale);

    void SetScale(float scaleX, float scaleY, float scaleZ);

    /// 父空间设置缩放
    void SetScale(const glm::vec3 &scale);

    /// 将父空间中的位置和旋转都设置为原子操作。这比单独设置位置和旋转要快。
    void SetTransform(const glm::vec3 &position, const glm::quat &rotation);

    /// Move the scene node in the chosen transform space.
    void Translate(const glm::vec3 &delta, TransformSpace space = TS_LOCAL);

    /// Rotate the scene node in the chosen transform space.
    void Rotate(const glm::quat &delta, TransformSpace space = TS_LOCAL);


    /// Set enabled/disabled state without recursion. Components in a disabled node become effectively disabled regardless of their own enable/disable state.
    void SetEnabled(bool enable);

    ///在特定索引处添加子场景节点。如果没有显式指定索引或索引大小大于当前子元素的大小，则在末尾追加新子元素。
    void AddChild(Scene *parent, Node *child);

    /// Return whether is a direct or indirect child of specified node.
    bool IsChildOf(Node *node) const;

    /// Remove a child scene node.

    void RemoveChild(Node *parent, Node *child);

    void RemoveChild(vector<shared_ptr<Node>>::iterator i);

    void SetScene(Scene *scene);

    Scene *GetScene() const { return scene_; }

    //获取children vector
    vector<shared_ptr<Node>>& GetAllChildren()  { return children_; }
    //根据下标获取childnode
    Node* GetChild(int i)  { return children_[i].get(); }

    /// 设置在世界空间的坐标
    void SetWorldPosition(const glm::vec3 &position);

    /// 设置在世界空间的缩放
    void SetWorldScale(const glm::vec3 &scale);

    void SetWorldScale(float scale);

    void SetWorldRotation(const glm::quat &rotation);

    /// 将世界空间中的位置和旋转都设置为原子操作
    void SetWorldTransform(const glm::vec3 &position, const glm::quat &rotation);


    /// Create a component to this node (with specified ID if provided).
    Component *CreateComponent(string type, CreateMode mode = REPLICATED, unsigned id = 0);


    /// Template version of creating a component.
    template<class T>
    T *CreateComponent(CreateMode mode = REPLICATED, unsigned id = 0);

    void RemoveComponent(Component *component);

    template<class T>
    void RemoveComponent();

    void RemoveComponent(vector<shared_ptr<Component> >::iterator i);

    void AddComponent(Component *component, unsigned id, CreateMode mode);


protected:
    //父节点
    Node *parent_;
    //场景(根节点)
    Scene *scene_;
    //场景中的唯一ID标识
    unsigned id_;
    /// Position.
    glm::vec3 position_;

    glm::vec3 rotate_;
    float rotateAngle_;

    /// Rotation.
    glm::quat rotation_;
    /// Scale.
    glm::vec3 scale_;


    /// 世界空间的旋转
    mutable glm::quat worldRotation_;
    /// Components.
    vector<shared_ptr<Component> > components_;
    /// Child scene nodes.
    vector<shared_ptr<Node> > children_;
    /// Node listeners.

    /// Enabled flag.
    bool enabled_;
};

template<class T>
T *Node::CreateComponent(CreateMode mode, unsigned id) {
    return static_cast<T *>(CreateComponent(T::GetTypeStatic(), mode, id));
}

template<class T>
void Node::RemoveComponent() { RemoveComponent(T::GetTypeStatic()); }
