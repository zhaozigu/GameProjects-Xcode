//
//  Ship.hpp
//  Sprites
//
//  Created by guyu on 2020/12/27.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#ifndef Ship_hpp
#define Ship_hpp

#include "Actor.hpp"
#include "SpriteComponent.hpp"
#include "InputComponent.hpp"

class Ship : public Actor
{
public:
    Ship(class Game* game);
    ~Ship();
    void UpdateActor(float deltaTime) override;
    void ActorInput(const uint8_t* keyState) override;
private:
    float mLaserCooldown;
    
    SpriteComponent* sc;
    InputComponent* ic;
};


#endif /* Ship_hpp */
