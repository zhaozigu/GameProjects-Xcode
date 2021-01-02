//
//  AnimSpriteComponent.cpp
//  Sprites
//
//  Created by guyu on 2020/12/26.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#include "AnimSpriteComponent.hpp"
#include "Math.hpp"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
:SpriteComponent(owner, drawOrder)
, mCurrFrame(0.0f)
, mAnimFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
  SpriteComponent::Update(deltaTime);
  
  if (mAnimTextures.size() > 0)
  {
    // 基于帧速和增量时间更新当前帧
    mCurrFrame += mAnimFPS * deltaTime;
    
    // 如果需要，绕回动画开始处
    while (mCurrFrame >= mAnimTextures.size())
    {
      mCurrFrame -= mAnimTextures.size();
    }
    
    // 设置当前texture
    SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
  }
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
  mAnimTextures = textures;
  if (mAnimTextures.size() > 0)
  {
    // 激活texture为第一帧
    mCurrFrame = 0.0f;
    SetTexture(mAnimTextures[0]);
  }
}
