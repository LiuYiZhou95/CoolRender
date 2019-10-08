//
// Created by liuyizhou on 2019/7/18.
//
#include "Scene.h"
#include "Component.h"
Scene::Scene(Context *context):
    Node(context),
    elapsedTime_(0)
{

}

Scene::~Scene()
{

}

void Scene::NodeAdded(Node *node){
    if (!node || node->GetScene()==this)
        return;

    //首先将节点的父节点移除
    Scene* oldScene=node->GetScene();
    if (oldScene) {
        oldScene->NodeRemoved(node);
    }
    node->SetScene(this);

}

void Scene::NodeRemoved(Node* node){
    if (!node || node->GetScene() != this)
        return;

}

void Scene::ComponentRemoved(Component* component)
{
    if (!component)
        return;

    unsigned id = component->GetID();

    localComponents_.erase(id);

    component->SetID(0);
    component->OnSceneSet(nullptr);
}

void Scene::ComponentAdded(Component* component)
{
    if (!component)
        return;

    unsigned id = component->GetID();



        KL_HashMap<unsigned, Component*>::iterator i = localComponents_.find(id);
        if ((i->first != localComponents_.end()->first )&& i->second != component)
        {
            ComponentRemoved(i->second);
        }

        localComponents_[id] = component;


    component->OnSceneSet(this);
}
