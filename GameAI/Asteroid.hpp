//
//  Asteroid.hpp
//  BasicPhysics
//
//  Created by guyu on 2020/12/27.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#ifndef Asteroid_hpp
#define Asteroid_hpp

#include "Actor.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "CircleComponent.hpp"

class Asteroid : public Actor
{
public:
    Asteroid(class Game* game);
    ~Asteroid();
    
    class CircleComponent* GetCircle() { return mCircle; }
private:
    class CircleComponent* mCircle;
    class SpriteComponent* sc;
    class MoveComponent* mc;
};

#endif /* Asteroid_hpp */
