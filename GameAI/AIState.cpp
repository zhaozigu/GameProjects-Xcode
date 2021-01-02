//
//  AIState.cpp
//  GameAI
//
//  Created by guyu on 2021/1/2.
//  Copyright © 2021 guyu2019. All rights reserved.
//

#include "AIState.hpp"
#include "AIComponent.hpp"
#include "SDL_log.h"

void AIPatrol::Update(float deltaTime)
{
    SDL_Log("更新%s状态", GetName());
    bool dead = true;
    if (dead)
    {
        mOwner->ChangeState("Death");
    }
}

void AIPatrol::OnEnter()
{
    SDL_Log("进入%s状态", GetName());
}

void AIPatrol::OnExit()
{
    SDL_Log("退出%s状态", GetName());
}

void AIDeath::Update(float deltaTime)
{
    SDL_Log("更新%s状态", GetName());
}

void AIDeath::OnEnter()
{
    SDL_Log("进入%s状态", GetName());
}

void AIDeath::OnExit()
{
    SDL_Log("退出%s状态", GetName());
}

void AIAttack::Update(float deltaTime)
{
    SDL_Log("更新%s状态", GetName());
}

void AIAttack::OnEnter()
{
    SDL_Log("进入%s状态", GetName());
}

void AIAttack::OnExit()
{
    SDL_Log("退出%s状态", GetName());
}
