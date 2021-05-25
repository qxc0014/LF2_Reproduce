#include "Component.h"

void Component::Update(float deltatime){

 }
Component::Component(Actor* owner,int order):m_owner(owner),m_order(order){
    std::cout << "往actor添加组件" << std::endl; 
        m_owner->addComponent(this);
}
void Component::ProcessInput(unsigned char const*){

}
Component::~Component()
{
    m_owner->removeComponent(this);
}