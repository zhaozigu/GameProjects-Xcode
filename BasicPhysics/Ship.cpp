//
//  Ship.cpp
//  Sprites
//
//  Created by guyu on 2020/12/27.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#include "Ship.hpp"
#include "Game.hpp"

Ship::Ship(Game* game)
: Actor(game)
, sc(new SpriteComponent(this, 150))
, ic(new InputComponent(this))
{
  sc->SetTexture(game->GetTexture("Assets/Ship.png"));

  // 设置按键
  ic->SetForwardKey(SDL_SCANCODE_W);
  ic->SetBackKey(SDL_SCANCODE_S);
  ic->SetClockwiseKey(SDL_SCANCODE_A);
  ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
  ic->SetMaxForwardSpeed(300.0f);
  ic->SetMaxAngularSpeed(Math::TwoPi);
}

void Ship::UpdateActor(float deltaTime)
{
    
}

Ship::~Ship()
{
    if (sc) delete sc;
    if (ic) delete ic;
}

void Ship::ActorInput(const uint8_t* keyState)
{
    
}
