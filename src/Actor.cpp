#include "Actor.h"
#include "Game.h"
#include "Component.h"
//构造actor类时，需要绑定game类
Actor::Actor(class Game* owner):
m_Gameowner(owner),
m_State(EActive),
m_old_dir(Direction::RightStanding),
m_Rotation(0.0f),
m_Position(Eigen::Vector2d(512.0f,300.0f)),
mjumpSpeed(0.0f),
mjumpHeight(0.0f)
{ 
    m_Gameowner->addActor(this);
}
//析构时需要从game类中删除actor类，同时也要释放所有组件
Actor::~Actor()
{
    //从Game类中删除当前对象
    m_Gameowner->removeActor(this);
    //释放组件库
    while(!m_Components.empty()){
        delete m_Components.back();
    }
}
void Actor::UpdateActor(float deltaTime)
{
}
void Actor::UpdateComponents(float deltatime){
    //调用组件接口，更新所有组件
    
    for(auto iter = m_Components.begin();
        iter != m_Components.end();
        ++iter){
            (*iter)->Update(deltatime);
    }
}
void Actor::Update(float deltaTime)
{
	if (m_State == EActive)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}
//按照组件的优先级插入
void Actor::addComponent(Component* tmp){
    //获取组件的优先级
    int order = tmp->GetUpdateOrder();
    //根据优先级的顺序插入组件
    auto iter = m_Components.begin();
    for(;
        iter != m_Components.end();
        ++iter
    ){
        if(order < (*iter)->GetUpdateOrder() )
        {
            break;
        }
    }
    m_Components.insert(iter,tmp);
    std::cout << m_Components.size() << std::endl;
}
void Actor::ProcessInput(const uint8_t * state){
    if(m_State == EActive){
        for(auto Component:m_Components){
            //调用每个移动组件的键盘处理
            Component->ProcessInput(state);
        }
        ActorInput(state);
    }
}
void Actor::ActorInput(const uint8_t * state){

}
void Actor::removeComponent(class Component* tmp){
    auto iter = std::find(m_Components.begin(),m_Components.end(),tmp);
    if( iter != m_Components.end()){
        m_Components.erase(iter);
    }
}