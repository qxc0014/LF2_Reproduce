#include "AnimSpriteComponent.h"
AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(5.0f)
{
}
//重载更新素材
void AnimSpriteComponent::Update(float deltaTime)
{
	//std::cout << "方向:" << m_owner->GetDir() << std::endl;
	SpriteComponent::Update(deltaTime);
	if (mAnimTextures.size() > 0)
	{
		// Update the current frame based on frame rate
		// and delta time
		mCurrFrame += mAnimFPS * deltaTime;//24*deltaTime
		while (mCurrFrame >= mAnimTextures.size()/2)
		{
			mCurrFrame -= mAnimTextures.size()/2;
		}
		
		switch (m_owner->GetDir())
		{
			case Actor::Direction::Right:
			case Actor::Direction::RightDown:
			case Actor::Direction::RightUp:
				break;
			case Actor::Direction::Left:
			case Actor::Direction::LeftDown:			
			case Actor::Direction::LeftUp:
				mCurrFrame += mAnimTextures.size()/2;
				break;
			case Actor::Direction::LeftStanding:
				mCurrFrame = mAnimTextures.size()*3/4-1;
				break;
			case Actor::Direction::RightStanding:
				mCurrFrame = mAnimTextures.size()/4-1;
				break;	
		}
		// Set the current texture
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}
//导入素材
void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}