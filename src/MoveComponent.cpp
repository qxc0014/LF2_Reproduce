#include "Base.h"
#include "MoveComponent.h"
MoveComponent::MoveComponent(Actor* actor,int order):
Component(actor,order)
{

}
void MoveComponent::Update(float deltaTime){
    	// Update position based on speeds and delta time
	Eigen::Vector2d pos =  m_owner->GetPosition();
    float mForwardSpeed = m_owner->GetForwardSpeed();
    float mUpdownSpeed = m_owner->GetUpdownSpeed();
    float UpAcc = m_owner->GetUpAcc();
    std::cout << "加速度：" << UpAcc << std::endl;
    float velodyne = m_owner->GetJumpSpeed() + UpAcc * deltaTime;
    std::cout << "速度：" << velodyne << std::endl;
    float oldjumHeight = m_owner->GetJumpHeight();
    float curjumpHeight = oldjumHeight + velodyne * deltaTime;
    if(curjumpHeight > 0.0f && m_owner->GetDir() == Actor::Direction::Jump){
        curjumpHeight = 0.0;
        m_owner->SetUpAcc(0.0f);
        m_owner->SetDir( m_owner->GetOldDir());
    }
    m_owner->SetJumpHeight(curjumpHeight);
    m_owner->SetJumpSpeed(velodyne);
    std::cout << "高度：" << curjumpHeight << std::endl;
	pos.x() +=  mForwardSpeed * deltaTime;
    std::cout << "状态："<< m_owner->GetDir() << std::endl;
     if(m_owner->GetDir() == Actor::Direction::Jump){
          pos.y() = m_owner->GetOldPosition().y() + curjumpHeight;
     }else{
        
        pos.y() +=   mUpdownSpeed * deltaTime;
    }
	// Restrict position to left half of screen
	if (pos.x() < 25.0f)
	{
		pos.x() = 25.0f;
	}
	else if (pos.x() > 1000.0f)
	{
		pos.x() = 1000.0f;
	}
	if (pos.y() < 25.0f)
	{
		pos.y() = 25.0f;
	}
	else if (pos.y() > 743.0f)
	{
		pos.y() = 743.0f;
	}
	m_owner->SetPosition(pos);
}

MoveComponent::~MoveComponent()
{
}
