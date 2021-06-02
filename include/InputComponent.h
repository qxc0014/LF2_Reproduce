#include "MoveComponent.h"
class InputComponent:public MoveComponent
{
private:
    float mMaxForwardSpeed;
    float mMaxAngularSpeed;
    float mMaxJumpAcc;
public:
    InputComponent(class Actor* actor,int order);
    void ProcessInput(const uint8_t * state) override;
    void Update(float deltaTime) override;
    void SetForwardSpeed(float RLspeed,float UDspeed,float JumpSpeed){
       m_owner->SetForwardSpeed(RLspeed);
       m_owner->SetUpdownSpeed(UDspeed);
       m_owner->SetJumpSpeed(JumpSpeed);
    }
    ~InputComponent();
};

