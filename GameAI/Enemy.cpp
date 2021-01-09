//
//  Enemy.cpp
//  GameAI
//
//  Created by guyu on 2021/1/9.
//  Copyright © 2021 guyu2019. All rights reserved.
//

#include "Enemy.hpp"
#include "Game.hpp"
#include "SpriteComponent.hpp"
#include "NavComponent.hpp"
#include "Grid.hpp"
#include "Tile.hpp"
#include "CircleComponent.hpp"
#include <algorithm>

Enemy::Enemy(class Game* game)
:Actor(game)
{
    // 注册到 game 中
    game->GetEnemies().emplace_back(this);
    
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("Assets/Airplane.png"));
    // 从起点开始
    SetPosition(GetGame()->GetGrid()->GetStartTile()->GetPosition());
    // 在起点开启向导
    NavComponent* nc = new NavComponent(this);
    nc->SetForwardSpeed(150.0f);
    nc->StartPath(GetGame()->GetGrid()->GetStartTile());
    // 碰撞半径
    mCircle = new CircleComponent(this);
    mCircle->SetRadius(25.0f);
}

Enemy::~Enemy()
{
    auto iter = std::find(GetGame()->GetEnemies().begin(),
                          GetGame()->GetEnemies().end(),
                          this);
    GetGame()->GetEnemies().erase(iter);
}

void Enemy::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    
    // 到了终点？
    Vector2 diff = GetPosition() - GetGame()->GetGrid()->GetEndTile()->GetPosition();
    if (Math::NearZero(diff.Length(), 10.0f))
    {
        SetState(EDead);
    }
}
