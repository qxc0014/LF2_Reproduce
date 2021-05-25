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
	pos.x() +=  mForwardSpeed * deltaTime;
	pos.y() +=  mUpdownSpeed * deltaTime;
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
