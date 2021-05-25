#pragma once
#include "Base.h"
class Game
{
private:
    //窗口生成
    SDL_Window* mWindow;
    //渲染器
    SDL_Renderer* mRenderer;
    //actor库
    std::vector<class Actor*> m_Actors;
    std::vector<class Actor*> m_PendingActors;
    //人
    class Person* m_person;
    //是否运行
    bool mIsRunning;
    //记录系统时间
    Uint32 mTicksCount;
    //是否正在更新,决定actor插入的容器
    bool mUpdatingActors;
    //精灵库
    std::vector<class SpriteComponent*> mSprites;
    //保存渲染图的map
    std::unordered_map<std::string, SDL_Texture*> mTextures;
public:
    Game(/* args */);
    //添加actor
    void addActor(class Actor* actor);
    //删除actor
    void removeActor(class Actor* actor);
    //添加组件
    void AddSprite(class SpriteComponent* sprite);
    //删除组件
    void RemoveSprite(class SpriteComponent* sprite);
    //游戏初始化
    bool Initialize();
    //导入素材
    void LoadData();
    //循环
    void RunLoop();
    //处理输入
    void ProcessInput();
    //游戏的刷新
    void UpdateGame();
    //生成输出
    void GenerateOutput();
    //关闭游戏
    void Shutdown();
    //从文件中渲染图
    SDL_Texture* GetTexture(const std::string& fileName);
    ~Game();
};