//
//  Tower.cpp
//  GameAI
//
//  Created by guyu on 2021/1/10.
//  Copyright © 2021 guyu2019. All rights reserved.
//

#include "Tower.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "Game.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"


Tower::Tower(class Game* game)
:Actor(game)
{
    SpriteComponent* sc = new SpriteComponent(this, 200);
    sc->SetTexture(game->GetTexture("Assets/Tower.png"));
    
    mMove = new MoveComponent(this);
    // mMove->SetAngularSpeed(Math::Pi);
    
    mNextAttack = AttackTime;
}

void Tower::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    
    mNextAttack -= deltaTime;
    if (mNextAttack <= 0.0f)
    {
        Enemy* e = GetGame()->GetNearestEnemy(GetPosition());
        if (e != nullptr)
        {
            Vector2 dir = e->GetPosition() - GetPosition();
            float dist = dir.Length();
            // 目标进入炮弹射程！
            if (dist < AttackRange)
            {
                // 旋转朝向
                SetRotation(Math::Atan2(-dir.y, dir.x));
                // 发射子弹，摧毁敌人
                Bullet* b = new Bullet(GetGame());
                b->SetPosition(GetPosition());
                b->SetRotation(GetRotation());
            }
        }
        mNextAttack += AttackTime;
    }
}
