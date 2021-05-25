#include "BGSpriteComponent.h"
#include "Actor.h"
BGSpriteComponent::BGSpriteComponent(Actor* bgActor,int draworder):
SpriteComponent(bgActor,draworder)
,mScrollSpeed(0.0f)
{
    std::cout << "进入BGSpriteComponent构造函数" << std::endl;
}
void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	for (auto& bg : mBGTextures)
	{
		// Update the x offset
		bg.mOffset.x() += mScrollSpeed * deltaTime;
		// If this is completely off the screen, reset offset to
		// the right of the last bg texture
		if (bg.mOffset.x() < -mScreenSize.x())
		{
			bg.mOffset.x() = (mBGTextures.size() - 1) * mScreenSize.x() - 1;//放置到最后
		}
	}
}
void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	// Draw each background texture
	for (auto& bg : mBGTextures)
	{
		SDL_Rect r;
		// Assume screen size dimensions
		r.w = static_cast<int>(mScreenSize.x());
		r.h = static_cast<int>(mScreenSize.y());
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(m_owner->GetPosition().x() - r.w / 2 + bg.mOffset.x());
		r.y = static_cast<int>(m_owner->GetPosition().y() - r.h / 2 + bg.mOffset.y());

		// Draw this background
		SDL_RenderCopy(renderer,
			bg.mTexture,
			nullptr,
			&r
		);
	}
}
//导入素材，设置贴图
void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.mTexture = tex;
		// Each texture is screen width in offset
		temp.mOffset.x() = count * mScreenSize.x();
		temp.mOffset.y() = 0;
		mBGTextures.emplace_back(temp);
		count++;
	}
}
BGSpriteComponent::~BGSpriteComponent()
{
}