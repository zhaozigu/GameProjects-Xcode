//
//  SpriteComponent.cpp
//  Sprites
//
//  Created by guyu on 2020/12/26.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#include "SpriteComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
:Component(owner)
,mTexture(nullptr)
,mDrawOrder(drawOrder)
,mTexWidth(0)
,mTexHeight(0)
{
  mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
  mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
  if (mTexture)
  {
    SDL_Rect r;
    // 根据比例放缩
    r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
    r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
    // 居中显示
    r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
    r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);
    
    // 绘制（必须把弧度转换成角度，并且调整方向）
    SDL_RenderCopyEx(renderer,
                     mTexture,
                     nullptr,
                     &r,
                     -Math::ToDegrees(mOwner->GetRotation()),
                     nullptr,
                     SDL_FLIP_NONE);
  }
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
  mTexture = texture;
  // 设置 宽度/高度
  SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
