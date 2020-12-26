//
//  Ship.hpp
//  Sprites
//
//  Created by guyu on 2020/12/27.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#ifndef Ship_hpp
#define Ship_hpp

#include "Actor.hpp"

class Ship : public Actor
{
public:
  Ship(class Game* game);
  void UpdateActor(float deltaTime) override;
  void ProcessKeyboard(const uint8_t* state);
  float GetRightSpeed() const { return mRightSpeed; }
  float GetDownSpeed() const { return mDownSpeed; }
private:
  float mRightSpeed;
  float mDownSpeed;
};


#endif /* Ship_hpp */
