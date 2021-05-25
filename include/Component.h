#pragma once
#include "Actor.h"
class Component
{
protected:
    //优先级
    int m_order;

    class Actor* m_owner;
public:
    //构造每个组件时直接将其和属于的actor绑定
    Component(class Actor* owner,int order);

    virtual ~Component();
    //更新组件,可继承
    virtual void Update(float deltatime);
    //得到组件的优先级
    int GetUpdateOrder() const { return m_order; }
    virtual void ProcessInput(const uint8_t * state);
};

