//
//  AIComponent.cpp
//  GameAI
//
//  Created by guyu on 2021/1/2.
//  Copyright © 2021 guyu2019. All rights reserved.
//

#include "AIComponent.hpp"
#include "AIState.hpp"
#include "SDL_log.h"

AIComponent::AIComponent(class Actor* owner)
:Component(owner)
,mCurrentState(nullptr)
{
}


void AIComponent::RegisterState(class AIState* state)
{
   mStateMap.emplace(state->GetName(), state);
}

void AIComponent::Update(float deltaTime)
{
    if (mCurrentState)
    {
        mCurrentState->Update(deltaTime);
    }
}

void AIComponent::ChangeState(const std::string& name)
{
    // 退出当前的状态
    if (mCurrentState)
    {
        mCurrentState->OnExit();
    }
    
    // 在映射中找到新状态
    auto iter = mStateMap.find(name);
    if (iter != mStateMap.end())
    {
        mCurrentState = iter->second;
        // 进入状态
        mCurrentState->OnEnter();
    }
    else
    {
        SDL_Log("无法在映射中找到AIState %s", name.c_str());
        mCurrentState = nullptr;
    }
}
