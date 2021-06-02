#include "InputComponent.h"

InputComponent::InputComponent(Actor* actor,int order):
MoveComponent(actor,order),
mMaxForwardSpeed(100.0f),
mMaxJumpAcc(3500.0f)
{
}
void InputComponent::Update(float deltaTime){
    MoveComponent::Update(deltaTime);
}
void InputComponent::ProcessInput(const uint8_t * state){

    float mRightSpeed = 0.0f;
	float mDownSpeed = 0.0f;
    float jumpacceleration = 0.0f;
    float JumpInitSpeed = 0.0f;
	bool ifscan = false;
	
	// right/left
	if (state[SDL_SCANCODE_D])
	{
		m_owner->SetDir(Actor::Direction::Right);
		ifscan = true;
		mRightSpeed += mMaxForwardSpeed;
	}
	if (state[SDL_SCANCODE_A])
	{
		m_owner->SetDir(Actor::Direction::Left);
		ifscan = true;
		mRightSpeed -= mMaxForwardSpeed;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		switch (m_owner->GetOldDir())
		{
			case Actor::Direction::Left:
			case Actor::Direction::LeftDown:
			case Actor::Direction::LeftStanding:
				m_owner->SetDir(Actor::Direction::LeftDown);
				break;
			case Actor::Direction::Right:
			case Actor::Direction::RightDown:
			case Actor::Direction::RightStanding:
				m_owner->SetDir(Actor::Direction::RightDown);
				break;	
		}
		ifscan = true;
		mDownSpeed += 50.0f;
	}
	if(state[SDL_SCANCODE_W])
	{
		switch (m_owner->GetOldDir())
		{
			case Actor::Direction::Left:
			case Actor::Direction::LeftUp:
			case Actor::Direction::LeftStanding:
				m_owner->SetDir(Actor::Direction::LeftUp);
				break;
			case  Actor::Direction::Right:
			case Actor::Direction::RightUp:
			case Actor::Direction::RightStanding:
				m_owner->SetDir(Actor::Direction::RightUp);
				break;	
		}
		ifscan = true;
		mDownSpeed -= 50.0f;
	}
	if(m_owner->GetDir() != Actor::Direction::Jump){
		if(ifscan == false && (m_owner->GetOldDir() == Actor::Direction::Left || m_owner->GetOldDir() == Actor::Direction::LeftStanding|| m_owner->GetOldDir() == Actor::Direction::LeftUp || m_owner->GetOldDir() == Actor::Direction::LeftDown) ){
			m_owner->SetDir(Actor::Direction::LeftStanding);
		}else if(ifscan == false && (m_owner->GetOldDir() == Actor::Direction::Right || m_owner->GetOldDir() == Actor::Direction::RightStanding || m_owner->GetOldDir() == Actor::Direction::RightUp || m_owner->GetOldDir() == Actor::Direction::RightDown)){
			m_owner->SetDir(Actor::Direction::RightStanding);
		}
		if(state[SDL_SCANCODE_K]){
			m_owner->SetDir(Actor::Direction::Jump);
			jumpacceleration += mMaxJumpAcc;
			JumpInitSpeed = -1000.0f;
			m_owner->SetUpAcc(jumpacceleration);
			m_owner->SavePosition();
    	}
	}
	//保存行走方向
	//if(m_owner->GetDir() == Actor::Direction::Left || m_owner->GetDir() == Actor::Direction::Right )
	if( m_owner->GetDir() != Actor::Direction::Jump)
	m_owner->CopyDir();
    SetForwardSpeed(mRightSpeed,mDownSpeed,JumpInitSpeed);
    
}
InputComponent::~InputComponent()
{
}