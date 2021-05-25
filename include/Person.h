#pragma once
#include "Actor.h"
#include <stdint.h>
class Person : public Actor
{
public:
    float mRightSpeed;
	float mDownSpeed;
public:
    Person(class Game* game);
    void UpdateActor(float deltaTime);
    void ProcessKeyboard(const uint8_t * state);
    ~Person();

};
