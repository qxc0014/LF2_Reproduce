#pragma once
#include "Base.h"

class Actor
{
   
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};
    enum Direction{
        LeftStanding,
        RightStanding,
        RightUp,
        RightDown,
        LeftUp,
        LeftDown,
        Left,
        Right,
        Jump
    };
    //绑定game类
    Actor(class Game* owner);
    virtual ~Actor();
    //设置actor位置
    void SetPosition(Eigen::Vector2d Position) { m_Position = Position; }
    //保存当前位置，用于跳跃
    void SavePosition() { 
        
        m_OldPosition = m_Position; 
        
        }
    //设置actor平移速度
    void SetForwardSpeed(float speed){ mForwardSpeed = speed; }
    void SetUpdownSpeed(float speed){ mUpdownSpeed = speed; }
    void SetJumpSpeed(float speed){ mjumpSpeed = speed; }
    void SetJumpHeight(float height){ mjumpHeight = height; }
    //设置actor向上跳跃的加速度
    void SetUpAcc(float acc){ mUpAcc = acc; }
    //返回actor平移速度
    float GetForwardSpeed(){ return mForwardSpeed; }
    float GetUpdownSpeed(){ return mUpdownSpeed; }
    float GetUpAcc(){ return mUpAcc; }
    float GetJumpSpeed(){ return mjumpSpeed; }
    float GetJumpHeight(){ return mjumpHeight; }
    Eigen::Vector2d GetOldPosition(){ return m_OldPosition; }
    //设置actor方向
    void SetRotation(float Rotation) { m_Rotation = Rotation; }
    //设置actor大小
    void SetScale(float scale) { m_scale = scale; }
    //设置actor行走方向
    void SetDir(Direction dir) { m_dir = dir; }
    //得到actor的行走方向
    Direction GetDir() {return m_dir; }
    //得到actor的上一次行走方向
    Direction GetOldDir() {return m_old_dir; }
    //得到actor位置
    Eigen::Vector2d GetPosition(){ return m_Position; }
    //得到actor方向
    float GetRotation(){ return m_Rotation; }
    //得到actor大小
    float GetScale(){ return m_scale; }
    //添加组件
    void addComponent(class Component* tmp);
    //移除组件
    void removeComponent(class Component* tmp);
    //更新内部组件库
    void UpdateComponents(float deltaTime);
    //封装
    class Game* GetGame() { return m_Gameowner; }
	State GetState() const { return m_State; }
	void SetState(State state) { m_State = state; }
    //处理输入，调用输入处理组件
    void ProcessInput(const uint8_t * state);
    //对输入进行继承扩展
    virtual void ActorInput(const uint8_t * state);
    //保存行走方向
    void CopyDir(){ m_old_dir = m_dir; }
    //更新actor的状态
    virtual void UpdateActor(float deltaTime);
    void Update(float deltaTime);
    //当前actor的状态
    State m_State;
private:
    //横向速度
    float mForwardSpeed;
    float mUpdownSpeed;
    //向上跳跃的加速度与速度
    float mUpAcc;
    float mjumpSpeed;
    float mjumpHeight;
    //行走方向
    Direction m_dir;
    //上一次行走方向
    Direction m_old_dir;
    //位置
    Eigen::Vector2d m_Position;
    Eigen::Vector2d m_OldPosition;
    //方向
    float m_Rotation;
    //大小
    float m_scale;
    //组件库
    std::vector<class Component* > m_Components;
    ///当前对象从属于的game类对象指针
    class Game* m_Gameowner;
};
