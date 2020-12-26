//
//  SpriteComponent.hpp
//  Sprites
//
//  Created by guyu on 2020/12/26.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "Component.hpp"
#include "SDL.h"

class SpriteComponent : public Component
{
public:
  // (越低的order对应越深的背面)
  SpriteComponent(class Actor* owner, int drawOrder = 100);
  ~SpriteComponent();
  
  virtual void Draw(SDL_Renderer* renderer);
  virtual void SetTexture(SDL_Texture* texture);
  
  int GetDrawOrder() const { return mDrawOrder; }
  int GetTexHeight() const { return mTexHeight; }
  int GetTexWidth() const { return mTexWidth; }
protected:
  SDL_Texture* mTexture;
  int mDrawOrder;
  int mTexWidth;
  int mTexHeight;
};
#endif /* SpriteComponent_hpp */
