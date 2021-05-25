#pragma once
#include "Component.h"
class MoveComponent:public Component
{
public:
    //构造子组件，前提是构造基类组件
    MoveComponent(class Actor* actor,int order);
    //重写更新
    void Update(float deltaTime) override;
    // float GetAngularSpeed() const{
    //     return mAngularSpeed;
    // } 
    // float GetForwardSpeed() const{
    //     return mForwardSpeed;
    // }
    // void SetAngularSpeed(float AngularSpeed){
    //     mAngularSpeed = AngularSpeed;
    // }
    // void SetForwardSpeed(float ForwardSpeed){
    //     mForwardSpeed = ForwardSpeed;
    // }
    
    virtual ~MoveComponent();
};

