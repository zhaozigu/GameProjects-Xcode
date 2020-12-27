//
//  CircleComponent.cpp
//  BasicPhysics
//
//  Created by guyu on 2020/12/27.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#include "CircleComponent.hpp"
#include "Actor.hpp"

CircleComponent::CircleComponent(class Actor* owner)
:Component(owner)
,mRadius(0.0f)
{
    
}

const Vector2& CircleComponent::GetCenter() const
{
    return mOwner->GetPosition();
}

float CircleComponent::GetRadius() const
{
    return mOwner->GetScale() * mRadius;
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
    // 计算距离的平方
    Vector2 diff = a.GetCenter() - b.GetCenter();
    float distSq = diff.LengthSq();

    // 计算半径之和，再平方
    float radiiSq = a.GetRadius() + b.GetRadius();
    radiiSq *= radiiSq;

    return distSq <= radiiSq;
}

