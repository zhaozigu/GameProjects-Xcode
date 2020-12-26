//
//  BGSpriteComponent.cpp
//  Sprites
//
//  Created by guyu on 2020/12/26.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#include "BGSpriteComponent.hpp"
#include "Actor.hpp"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder)
:SpriteComponent(owner, drawOrder)
,mScrollSpeed(0.0f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
  SpriteComponent::Update(deltaTime);
  for (auto& bg : mBGTextures)
  {
    // 更新x偏移
    bg.mOffset.x += mScrollSpeed * deltaTime;
    // 如果完全偏离屏幕，重置偏移
    if (bg.mOffset.x < -mScreenSize.x)
    {
      bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
    }
  }
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
  // 绘制每个背景 texture
  for (auto& bg : mBGTextures)
  {
    SDL_Rect r;
    // 设定屏幕大小尺寸
    r.w = static_cast<int>(mScreenSize.x);
    r.h = static_cast<int>(mScreenSize.y);
    // 居中放置
    r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x);
    r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y);
    
    // 绘制这个背景
    SDL_RenderCopy(renderer,
                   bg.mTexture,
                   nullptr,
                   &r
                   );
  }
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
  int count = 0;
  for (auto tex : textures)
  {
    BGTexture temp;
    temp.mTexture = tex;
    // texture大小是屏幕宽度
    temp.mOffset.x = count * mScreenSize.x;
    temp.mOffset.y = 0;
    mBGTextures.emplace_back(temp);
    count++;
  }
}

