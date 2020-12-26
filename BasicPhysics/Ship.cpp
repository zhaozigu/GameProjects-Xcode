//
//  Ship.cpp
//  Sprites
//
//  Created by guyu on 2020/12/27.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#include "Ship.hpp"
#include "AnimSpriteComponent.hpp"
#include "Game.hpp"

Ship::Ship(Game* game)
:Actor(game)
,mRightSpeed(0.0f)
,mDownSpeed(0.0f)
{
  // 创建一个动画精灵组件
  AnimSpriteComponent* asc = new AnimSpriteComponent(this);
  std::vector<SDL_Texture*> anims = {
    game->GetTexture("Assets/Ship01.png"),
    game->GetTexture("Assets/Ship02.png"),
    game->GetTexture("Assets/Ship03.png"),
    game->GetTexture("Assets/Ship04.png"),
  };
  asc->SetAnimTextures(anims);
}

void Ship::UpdateActor(float deltaTime)
{
  Actor::UpdateActor(deltaTime);
  // 基于速度和增量时间更新位置
  Vector2 pos = GetPosition();
  pos.x += mRightSpeed * deltaTime;
  pos.y += mDownSpeed * deltaTime;
  
  // 限制在屏幕左半部分
  if (pos.x < 25.0f)
  {
    pos.x = 25.0f;
  }
  else if (pos.x > 500.0f)
  {
    pos.x = 500.0f;
  }
  if (pos.y < 25.0f)
  {
    pos.y = 25.0f;
  }
  else if (pos.y > 743.0f)
  {
    pos.y = 743.0f;
  }
  SetPosition(pos);
}

void Ship::ProcessKeyboard(const uint8_t* state)
{
  mRightSpeed = 0.0f;
  mDownSpeed = 0.0f;
  // 右/左
  if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
  {
    mRightSpeed += 250.0f;
  }
  if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
  {
    mRightSpeed -= 250.0f;
  }
  // 上/下
  if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
  {
    mDownSpeed += 300.0f;
  }
  if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
  {
    mDownSpeed -= 300.0f;
  }
}
