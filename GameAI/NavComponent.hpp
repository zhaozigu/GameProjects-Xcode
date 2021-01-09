//
//  NavComponent.hpp
//  GameAI
//
//  Created by 千凡谷梦 on 2021/1/10.
//  Copyright © 2021 guyu2019. All rights reserved.
//

#ifndef NavComponent_hpp
#define NavComponent_hpp

#include "MoveComponent.hpp"
#include "Math.hpp"

class NavComponent : public MoveComponent
{
public:
    NavComponent(class Actor* owner, int updateOrder = 10);
    void Update(float deltaTime) override;
    void StartPath(const class Tile* start);
    void TurnTo(const Vector2& pos);
private:
    const class Tile* mNextNode;
};


#endif /* NavComponent_hpp */
