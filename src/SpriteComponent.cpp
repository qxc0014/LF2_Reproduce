#include "Game.h"
#include "SpriteComponent.h"
#include "Actor.h"
SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner,100)
	,mTexture(nullptr)
	,mDrawOrder(drawOrder)
	,mTexWidth(0)
	,mTexHeight(0)
{
	std::cout << "进入SpriteComponent构造函数" << std::endl;
	//在创建一个新的组件时，就要确定好它的归属
	m_owner->GetGame()->AddSprite(this);
	
}

SpriteComponent::~SpriteComponent()
{
	m_owner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		// Scale the width/height by owner's scale
		r.w = static_cast<int>(mTexWidth * m_owner->GetScale());
		r.h = static_cast<int>(mTexHeight * m_owner->GetScale());
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(m_owner->GetPosition()[0] - r.w / 2);
		r.y = static_cast<int>(m_owner->GetPosition()[1] - r.h / 2);
        
		// Draw (have to convert angle from radians to degrees, and clockwise to counter)
		SDL_RenderCopyEx(renderer,//渲染器
			mTexture,//贴图
			nullptr,
			&r,//方框
            -(180.0f/M_PI) *m_owner->GetRotation() ,//方框旋转的角度
			nullptr,
			SDL_FLIP_NONE);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// Set width/height
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
