//
// Created by liuyizhou on 2019/7/18.
//

#include "Node.h"
#include "Scene.h"
#include "Context.h"
#include "Component.h"
#include <glm/ext.hpp>

Node::Node(Context *context) :
        Animatable(context),
        enabled_(true),
        parent_(nullptr),
        scene_(nullptr),
        position_(glm::vec3(0.0, 0.0, 0.0)),
        rotation_(glm::quat(1.0, 0.0, 0.0, 0.0)),
        rotate_(glm::vec3(0, 1, 0)),
        rotateAngle_(0),
        //1080->1.0
        scale_(glm::vec3(1.0, 1.0, 1.0)) {

}

Node::~Node() {


}

glm::mat4 Node::getMat() {
    return glm::translate(position_) * glm::rotate(glm::radians(rotateAngle_), rotate_) *
           glm::scale(scale_);
}

void Node::SetScene(Scene *scene) {
    scene_ = scene;
}

void Node::SetPosition(float tx, float ty, float tz) {
    SetPosition(glm::vec3(tx, ty, tz));

}

void Node::SetPosition(const glm::vec3 &position) {
    position_ = position;

}


void Node::SetRotation(const glm::quat &rotation) {
    rotation_ = rotation;

}

void Node::SetRotate(const glm::vec3 &rotate, const float rotateAngle) {
    rotate_ = rotate;
    rotateAngle_ = rotateAngle;
}

void Node::SetRotate(float tx, float ty, float tz, float rotateAngle) {
    SetRotate( glm::vec3 (tx,ty,tz), rotateAngle);
}

void Node::SetScale(float scaleX,float scaleY,float scaleZ) {
    SetScale(glm::vec3(scaleX, scaleY, scaleZ));
}

void Node::SetScale(float scale) {
    SetScale(glm::vec3(scale, scale, scale));
}

void Node::SetScale(const glm::vec3 &scale) {
    scale_ = scale;
    //避免精确的零标度，例如，避免瞬时编辑，因为这可能会导致在分解世界变换矩阵时除以零
    if (scale_.x == 0.0f)
        scale_.x = 0.0001f;
    if (scale_.y == 0.0f)
        scale_.y = 0.0001f;
    if (scale_.z == 0.0f)
        scale_.z = 0.0001f;

}

void Node::SetTransform(const glm::vec3 &position, const glm::quat &rotation) {
    position_ = position;
    rotation_ = rotation;

}

void Node::Translate(const glm::vec3 &delta, TransformSpace space) {

    // Note: local space translation disregards local scale for scale-independent movement speed
    position_ += rotation_ * delta;


}

void Node::Rotate(const glm::quat &delta, TransformSpace space) {

    rotation_ = (rotation_ * delta);
    //归一化
    rotation_ = rotation_ / sqrt(rotation_.x * rotation_.x + rotation_.y * rotation_.y +
                                 rotation_.z * rotation_.z);


}

void Node::SetEnabled(bool enable) {

    if (getType() == Scene::getTypeStatic()) {
        LOGE("Can not change enabled state of the Scene");
        return;
    }
    if (enable != enabled_)
        enabled_ = enable;

}

void Node::AddChild(Scene *parent, Node *child) {
    if (!child || child == this || child->GetScene() == this)
        return;
    child->SetScene(parent);

    vector<shared_ptr<Node>>::iterator theIterator = children_.begin();

    shared_ptr<Node> nodeShared(child);

    children_.insert(theIterator, nodeShared);
    if (scene_ && child->GetScene() != scene_)
        scene_->NodeAdded(child);

    child->parent_ = this;


    for (int i = 0; i < nodeShared->children_.size(); ++i) {
        nodeShared->children_[i].get()->SetScene(parent);
        AddChild(parent, nodeShared->children_[i].get());
    };
}

void Node::RemoveChild(Node *parent, Node *child) {
    if (!child || parent == child)
        return;

//    vector <shared_ptr<Node>>::iterator theIterator = find(children_.begin(),children_.end(),child);
//    theIterator=children_.erase(theIterator);
//    theIterator--;

    //迭代出当前指向child的node
    for (vector<shared_ptr<Node>>::iterator theIterator = children_.begin();
         theIterator != children_.end(); ++theIterator) {

        if (theIterator->get() == child) {
            RemoveChild(theIterator);
        }
    }
}

//通过迭代器下标remove Node
void Node::RemoveChild(vector<shared_ptr<Node>>::iterator i) {
    shared_ptr<Node> child(*i);

    child->parent_ = nullptr;
    //可以清空scene指向
    // child->scene_=nullptr;

    i = children_.erase(i);
    i--;
}

bool Node::IsChildOf(Node *node) const {
    Node *parent = parent_;
    while (parent) {
        if (parent == node)
            return true;
        parent = parent->parent_;
    }
    return false;
}

void Node::SetWorldPosition(const glm::vec3 &position) {
//    SetPosition((parent_ == scene_ || !parent_) ? position : parent_->GetWorldTransform().Inverse() * position);
}

void Node::SetWorldRotation(const glm::quat &rotation) {
//    SetRotation((parent_ == scene_ || !parent_) ? rotation : parent_->GetWorldRotation().Inverse() * rotation);
}

void Node::SetWorldScale(float scale) {
    SetWorldScale(glm::vec3(scale, scale, scale));
}

void Node::SetWorldScale(const glm::vec3 &scale) {
//    SetScale((parent_ == scene_ || !parent_) ? scale : scale / parent_->GetWorldScale());
}

void Node::SetWorldTransform(const glm::vec3 &position, const glm::quat &rotation) {
    SetWorldPosition(position);
    SetWorldRotation(rotation);
}

Component *Node::CreateComponent(string type, CreateMode mode, unsigned id) {
    // Do not attempt to create replicated components to local nodes, as that may lead to component ID overwrite
    // as replicated components are synced over
    if (mode == REPLICATED)
        mode = LOCAL;

    // Check that creation succeeds and that the object in fact is a component

    Component *newComponent = dynamic_cast<Component *>(context_->CreateObject(type));
    if (!newComponent) {

        return nullptr;

    }

    AddComponent(newComponent, id, mode);
    return newComponent;
}

void Node::RemoveComponent(Component *component) {
    for (vector<shared_ptr<Component> >::iterator i = components_.begin();
         i != components_.end(); ++i) {
        if ((*i).get() == component) {
            RemoveComponent(i);

            // Mark node dirty in all replication states

            return;
        }
    }
}

void Node::RemoveComponent(vector<shared_ptr<Component> >::iterator i) {


    if (scene_)
        scene_->ComponentRemoved((*i).get());
    (*i)->SetNode(nullptr);
    components_.erase(i);
}

void Node::AddComponent(Component *component, unsigned id, CreateMode mode) {
    if (!component)
        return;

    components_.push_back(shared_ptr<Component>(component));

    if (component->GetNode())

        component->SetNode(this);

    // If zero ID specified, or the ID is already taken, let the scene assign
    if (scene_) {
        component->SetID(id);
        scene_->ComponentAdded(component);
    } else
        component->SetID(id);


}
