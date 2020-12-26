//
//  Component.cpp
//  Sprites
//
//  Created by guyu on 2020/12/26.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#include "Component.hpp"
#include "Actor.hpp"

Component::Component(Actor* owner, int updateOrder)
:mOwner(owner)
,mUpdateOrder(updateOrder)
{
  // 添加到actor的组件向量
  mOwner->AddComponent(this);
}

Component::~Component()
{
  mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}
