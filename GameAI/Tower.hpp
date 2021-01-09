//
//  Tower.hpp
//  GameAI
//
//  Created by 千凡谷梦 on 2021/1/10.
//  Copyright © 2021 guyu2019. All rights reserved.
//

#ifndef Tower_hpp
#define Tower_hpp
#include "Actor.hpp"

class Tower : public Actor
{
public:
    Tower(class Game* game);
    void UpdateActor(float deltaTime) override;
private:
    class MoveComponent* mMove;
    float mNextAttack;
    const float AttackTime = 2.5f;
    const float AttackRange = 100.0f;
};

#endif /* Tower_hpp */
