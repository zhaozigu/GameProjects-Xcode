//
//  BGSpriteComponent.hpp
//  Sprites
//
//  Created by guyu on 2020/12/26.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#ifndef BGSpriteComponent_hpp
#define BGSpriteComponent_hpp

#include "SpriteComponent.hpp"
#include <vector>
#include "Math.hpp"

class BGSpriteComponent : public SpriteComponent
{
public:
  // 背景，所以绘制的顺序默认值比较低
  BGSpriteComponent(class Actor* owner, int drawOrder = 10);
  // 从父类中 更新/绘制
  void Update(float deltaTime) override;
  void Draw(SDL_Renderer* renderer) override;
  // 设置被用于背景的texture
  void SetBGTextures(const std::vector<SDL_Texture*>& textures);
  // 读取/设置 屏幕大小和滚动速度
  void SetScreenSize(const Vector2& size) { mScreenSize = size; }
  void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
  float GetScrollSpeed() const { return mScrollSpeed; }
private:
  // 封装背景图像以及偏移量
  struct BGTexture
  {
    SDL_Texture* mTexture;
    Vector2 mOffset;
  };
  std::vector<BGTexture> mBGTextures;
  Vector2 mScreenSize;
  float mScrollSpeed;
};

#endif /* BGSpriteComponent_hpp */
