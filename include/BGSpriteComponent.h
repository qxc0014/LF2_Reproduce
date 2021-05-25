#include "Base.h"
#include "SpriteComponent.h"
class BGSpriteComponent : public SpriteComponent
{
private:
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Eigen::Vector2d mOffset;
	};
    std::vector<BGTexture> mBGTextures;
	Eigen::Vector2d mScreenSize;
    class Actor* Bgowner;
    float mScrollSpeed;
public:
    BGSpriteComponent(class Actor* bgActor,int draworder = 10);
    void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
    void SetBGTextures(const std::vector<SDL_Texture*>& textures);
	// Get/set screen size and scroll speed
	void SetScreenSize(const Eigen::Vector2d& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
    ~BGSpriteComponent();
    
};


