//
//  Asteroid.cpp
//  BasicPhysics
//
//  Created by guyu on 2020/12/27.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#include "Asteroid.hpp"
#include "MoveComponent.hpp"
#include "Game.hpp"
#include "Random.hpp"

Asteroid::Asteroid(Game* game)
    :Actor(game)
    , sc(new SpriteComponent(this))
    , mc(new MoveComponent(this))
{
    // 初始化一个随机的位置和方向
    Vector2 randPos = Random::GetVector(Vector2::Zero,
        Vector2(1024.0f, 768.0f));
    SetPosition(randPos);

    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

    sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));
    mc->SetForwardSpeed(150.0f);
}

Asteroid::~Asteroid()
{
    if (sc) delete sc;
    if (mc) delete mc;
}
