//
// Created by liuyizhou on 2019/7/18.
//
#include "Context.h"
#include "Object.h"
#include "Common.h"
#include <vector>
//#include "File.h"
#include "Graphics/Graphics.h"
Context::~Context()

{
    KL_HashMap<string ,Object*>::iterator iter = subsystem_.begin();
    for(;iter != subsystem_.end();iter ++)
    {
        delete iter->second;
    }
    subsystem_.clear();
}

void Context::registerSubsystem(Object* subsystem)
{
    if(!subsystem)
        return;
    subsystem_[subsystem->getType()] = subsystem;
}

Object* Context::getSubsystem(string type) const
{
    KL_HashMap<string,Object*>::const_iterator i = subsystem_.find(type);
    if(i != subsystem_.end())
        return i ->second;
    else
        return 0;
}

void Context::removeSubsystem(string ObjectType)
{
    KL_HashMap<string , Object*>::iterator i = subsystem_.find(ObjectType);
    if(i != subsystem_.end())
        subsystem_.erase(i);
}

Object* Context::CreateObject(string objectType)
{
//    HashMap<string, shared_ptr<ObjectFactory> >::ConstIterator i = factories_.Find(objectType);
//    if (i != factories_.End())
//        return i->second_->CreateObject();
//    else
        return shared_ptr<Object>().get();
}