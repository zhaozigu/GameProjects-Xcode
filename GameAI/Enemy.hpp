//
//  Enemy.hpp
//  GameAI
//
//  Created by guyu on 2021/1/9.
//  Copyright © 2021 guyu2019. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp
#include "Actor.hpp"

class Enemy : public Actor
{
public:
    Enemy(class Game* game);
    ~Enemy();
    void UpdateActor(float deltaTime) override;
    class CircleComponent* GetCircle() { return mCircle; }
private:
    class CircleComponent* mCircle;
};


#endif /* Enemy_hpp */
