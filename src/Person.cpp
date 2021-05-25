#include "Person.h"
#include "Game.h"
#include "AnimSpriteComponent.h"
Person::Person(Game* game):Actor(game)
{
    //创建一个组件
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);

    std::vector<SDL_Texture*> anims = {
		game->GetTexture("../Assets/0_0.png"),
		game->GetTexture("../Assets/0_1.png"),
		game->GetTexture("../Assets/0_2.png"),
		game->GetTexture("../Assets/0_3.png"),
		game->GetTexture("../Assets/0_2.png"),
		game->GetTexture("../Assets/0_1.png"),
		game->GetTexture("../Assets/0_4.png"),
		game->GetTexture("../Assets/0_5.png"),
		game->GetTexture("../Assets/0_6.png"),
		game->GetTexture("../Assets/0_7.png"),
		game->GetTexture("../Assets/0_6.png"),
		game->GetTexture("../Assets/0_5.png"),
	};
	asc->SetAnimTextures(anims);
}
void Person::UpdateActor(float deltaTime)
{
	// Actor::UpdateActor(deltaTime);
	// // Update position based on speeds and delta time
	// Eigen::Vector2d pos = GetPosition();
	// pos.x() += mRightSpeed * deltaTime;
	// pos.y() += mDownSpeed * deltaTime;
	// // Restrict position to left half of screen
	// if (pos.x() < 25.0f)
	// {
	// 	pos.x() = 25.0f;
	// }
	// else if (pos.x() > 1000.0f)
	// {
	// 	pos.x() = 1000.0f;
	// }
	// if (pos.y() < 25.0f)
	// {
	// 	pos.y() = 25.0f;
	// }
	// else if (pos.y() > 743.0f)
	// {
	// 	pos.y() = 743.0f;
	// }
	// SetPosition(pos);
}
void Person::ProcessKeyboard(const uint8_t * state)
{
	// mRightSpeed = 0.0f;
	// mDownSpeed = 0.0f;
	// bool ifscan = false;
	
	// // right/left
	// if (state[SDL_SCANCODE_D])
	// {
	// 	SetDir(Direction::Right);
	// 	ifscan = true;
	// 	mRightSpeed += 100.0f;
	// }
	// if (state[SDL_SCANCODE_A])
	// {
	// 	SetDir(Direction::Left);
	// 	ifscan = true;
	// 	mRightSpeed -= 100.0f;
	// }
	// // up/down
	// if (state[SDL_SCANCODE_S])
	// {
	// 	switch (GetOldDir())
	// 	{
	// 		case Direction::Left:
	// 		case Direction::LeftDown:
	// 		case Direction::LeftStanding:
	// 			SetDir(Direction::LeftDown);
	// 			break;
	// 		case  Direction::Right:
	// 		case Direction::RightDown:
	// 		case Direction::RightStanding:
	// 			SetDir(Direction::RightDown);
	// 			break;	
	// 	}
	// 	ifscan = true;
	// 	mDownSpeed += 50.0f;
	// }
	// if (state[SDL_SCANCODE_W])
	// {
	// 	switch (GetOldDir())
	// 	{
	// 		case Direction::Left:
	// 		case Direction::LeftUp:
	// 		case Direction::LeftStanding:
	// 			SetDir(Direction::LeftUp);
	// 			break;
	// 		case  Direction::Right:
	// 		case Direction::RightUp:
	// 		case Direction::RightStanding:
	// 			SetDir(Direction::RightUp);
	// 			break;	
	// 	}
	// 	ifscan = true;
	// 	mDownSpeed -= 50.0f;
	// }

	// if(ifscan == false && (GetOldDir() == Direction::Left || GetOldDir() == Direction::LeftStanding) ){
	// 	SetDir(Direction::LeftStanding);
	// }else if(ifscan == false && (GetOldDir() == Direction::Right || GetOldDir() == Direction::RightStanding)){
	// 	SetDir(Direction::RightStanding);
	// }

	// //保存行走方向
	// if(GetDir() == Direction::Left || GetDir() == Direction::Right)
	// CopyDir();
}

Person::~Person()
{
}
