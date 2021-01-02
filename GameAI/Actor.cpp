//
//  Actor.cpp
//  Sprites
//
//  Created by 千凡谷梦 on 2020/12/26.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#include "Actor.hpp"
#include "Game.hpp"
#include "Component.hpp"
#include <algorithm>

Actor::Actor(Game* game)
:mState(EActive)
, mPosition(Vector2::Zero)
, mScale(1.0f)
, mRotation(0.0f)
, mGame(game)
{
    mGame->AddActor(this);
}

Actor::~Actor()
{
    mGame->RemoveActor(this);
    // 需要删除组件
    // 因为~Component调用RemoveComponent，所以需要来一个循环
    while (!mComponents.empty())
    {
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime)
{
    if (mState == EActive)
    {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime)
{
    for (auto comp : mComponents)
    {
        comp->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component* component)
{
    // 插入排序：在一个已经排序好的向量中找到插入点
    // (找到第一个比我大的地方)
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for (;
         iter != mComponents.end();
         ++iter)
    {
        if (myOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }
    
    // 在迭代器之前插入元素
    mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}


void Actor::ProcessInput(const uint8_t* keyState)
{
    if (mState == EActive)
    {
        // 首先处理组件的输入
        for (auto comp : mComponents)
        {
            comp->ProcessInput(keyState);
        }
        
        ActorInput(keyState);
    }
}

void Actor::ActorInput(const uint8_t* keyState)
{
}
