//
//  Bullet.hpp
//  GameAI
//
//  Created by guyu on 2021/1/10.
//  Copyright © 2021 guyu2019. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp
#include "Actor.hpp"

class Bullet : public Actor
{
public:
    Bullet(class Game* game);
    void UpdateActor(float deltaTime) override;
private:
    class CircleComponent* mCircle;
    float mLiveTime;
};

#endif /* Bullet_hpp */
