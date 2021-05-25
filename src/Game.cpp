#include "Base.h"
#include "Game.h"
#include "Actor.h"
#include "Person.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"
#include "InputComponent.h"
Game::Game(/* args */):
mWindow(nullptr),
mRenderer(nullptr),
mIsRunning(true),
mUpdatingActors(false)
{
}
bool Game::Initialize(){
    //初始化sdl
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if(sdlResult != 0 ){
        SDL_Log("Unable to initialize SDL: %s",SDL_GetError());
        return false;
    }
    //创建窗口
    mWindow = SDL_CreateWindow(
        "Game Programming in C++(Chapter 2)",
        100,
        100,
        1024,
        768,
        0
    );
    if(!mWindow){
        SDL_Log("Failed to create window: %s",SDL_GetError());
        return false;
    }
    //创建渲染器
    mRenderer = SDL_CreateRenderer(
        mWindow,
        -1,
        SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
    );
    if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
    if(IMG_Init(IMG_INIT_PNG) == 0){
        SDL_Log("Unable to initialize SDL_image: %s",SDL_GetError());
        return false;
    }
    LoadData();
    mTicksCount = SDL_GetTicks();
    return true;
}
void Game::LoadData(){
    // Create player's person
	m_person = new Person(this);
	m_person->SetPosition(Eigen::Vector2d(100.0f, 384.0f));
	m_person->SetScale(1.0f);

    InputComponent* Move = new InputComponent(m_person,10);
    //先创建一个actor
    Actor* m_backgroud = new Actor(this);
    m_backgroud->SetPosition(Eigen::Vector2d(512.0f,384.0f));
    //再将静态背景作为插件插入到actor中,多态
    BGSpriteComponent* bg = new BGSpriteComponent(m_backgroud);
    bg->SetScreenSize(Eigen::Vector2d(1024.0f, 768.0f));
    	std::vector<SDL_Texture*> bgtexs = {
            GetTexture("../Assets/0.bmp")
		//GetTexture("../Assets/Farback01.png"),
       // GetTexture("../Assets/Farback02.png")
		
	};
    bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(0.0f);//设置滚动速度
    
}
void Game::RunLoop(){
    while(mIsRunning){
        //处理输入
        ProcessInput();
        //更新游戏
        UpdateGame();
        //处理输出
        GenerateOutput();
    }
}
void Game::ProcessInput(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type)
        {
        //用于检测关闭窗口的指令
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }
    
    const Uint8* state = SDL_GetKeyboardState(NULL);
    
    if(state[SDL_SCANCODE_ESCAPE]){
        mIsRunning = false;
    }
    for(auto actor:m_Actors){
        actor->ProcessInput(state);
    }
}
void Game::UpdateGame(){
    //更新时间
    while(!SDL_TICKS_PASSED(SDL_GetTicks(),mTicksCount + 16));//给个帧率上限
    float deltaTime = (SDL_GetTicks() - mTicksCount )/1000.0f;
    if(deltaTime > 0.05f){
        deltaTime = 0.05f;//给个下限
    }
    mTicksCount = SDL_GetTicks();
    mUpdatingActors = true;

	for (auto actor : m_Actors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// Move any pending actors to mActors
	for (auto pending : m_PendingActors)
	{
		m_Actors.emplace_back(pending);
	}
	m_PendingActors.clear();

	// Add any dead actors to a temp vector
	std::vector<Actor*> deadActors;
	for (auto actor : m_Actors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// Delete dead actors (which removes them from mActors)
	for (auto actor : deadActors)
	{
		delete actor;
	}

}
void Game::GenerateOutput(){
    //指定颜色
    SDL_SetRenderDrawColor(
        mRenderer,
        255,//R
        255,//G
        255,//B
        255 //A
    );

    //清除后台缓冲区
    SDL_RenderClear(mRenderer);
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}
    //交换前后台缓冲区
    SDL_RenderPresent(mRenderer);

}
SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	// Is the texture already in the map?
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// Load from file
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}
void Game::AddSprite(SpriteComponent* sprite){
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for(;
        iter != mSprites.end();
        ++iter){
            if(myDrawOrder < (*iter)->GetDrawOrder()){
                break;
            }
        }
        mSprites.insert(iter,sprite);
    std::cout << "添加精灵" <<mSprites.size() << std::endl;
}
void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}
void Game::addActor(Actor* actor){
    if(mUpdatingActors){
        m_PendingActors.emplace_back(actor);
    }else{
        m_Actors.emplace_back(actor);
    }
}
void Game::removeActor(Actor* actor){
    auto iter = std::find(m_Actors.begin(),m_Actors.end(),actor);
    if(iter != m_Actors.end())
    m_Actors.erase(iter);
}

void Game::Shutdown(){
    while(!m_Actors.empty()){
        delete m_Actors.back();
    }
    //销毁渲染器
    SDL_DestroyRenderer(mRenderer);
    //关闭窗口
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}
Game::~Game()
{
}
