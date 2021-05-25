#include "MoveComponent.h"
class InputComponent:public MoveComponent
{
private:
    float mMaxForwardSpeed;
    float mMaxAngularSpeed;
public:
    InputComponent(class Actor* actor,int order);
    void ProcessInput(const uint8_t * state) override;
    void Update(float deltaTime) override;
    void SetForwardSpeed(float RLspeed,float UDspeed){
       m_owner->SetForwardSpeed(RLspeed);
       m_owner->SetUpdownSpeed(UDspeed);
    }
    ~InputComponent();
};

