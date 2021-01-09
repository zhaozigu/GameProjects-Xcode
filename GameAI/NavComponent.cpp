//
//  NavComponent.cpp
//  GameAI
//
//  Created by guyu on 2021/1/10.
//  Copyright © 2021 guyu2019. All rights reserved.
//

#include "NavComponent.hpp"
#include "Tile.hpp"

NavComponent::NavComponent(class Actor* owner, int updateOrder)
:MoveComponent(owner, updateOrder)
,mNextNode(nullptr)
{
    
}

void NavComponent::Update(float deltaTime)
{
    if (mNextNode)
    {
        // 如果有下个点，沿路前进
        Vector2 diff = mOwner->GetPosition() - mNextNode->GetPosition();
        if (Math::NearZero(diff.Length(), 2.0f))
        {
            mNextNode = mNextNode->GetParent();
            TurnTo(mNextNode->GetPosition());
        }
    }
    
    MoveComponent::Update(deltaTime);
}

void NavComponent::StartPath(const Tile* start)
{
    mNextNode = start->GetParent();
    TurnTo(mNextNode->GetPosition());
}

void NavComponent::TurnTo(const Vector2& pos)
{
    // 方向向量
    Vector2 dir = pos - mOwner->GetPosition();
    float angle = Math::Atan2(-dir.y, dir.x);
    mOwner->SetRotation(angle);
}
