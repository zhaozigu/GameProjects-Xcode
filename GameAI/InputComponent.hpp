//
//  InputComponent.hpp
//  BasicPhysics
//
//  Created by guyu on 2020/12/27.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#ifndef InputComponent_hpp
#define InputComponent_hpp

#include "MoveComponent.hpp"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
    // 值低者优先更新
    InputComponent(class Actor* owner);

    void ProcessInput(const uint8_t* keyState) override;
    
    // Getters/setters
    float GetMaxForward() const { return mMaxForwardSpeed; }
    float GetMaxAngular() const { return mMaxAngularSpeed; }
    int GetForwardKey() const { return mForwardKey; }
    int GetBackKey() const { return mBackKey; }
    int GetClockwiseKey() const { return mClockwiseKey; }
    int GetCounterClockwiseKey() const { return mCounterClockwiseKey; }

    void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
    void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
    void SetForwardKey(int key) { mForwardKey = key; }
    void SetBackKey(int key) { mBackKey = key; }
    void SetClockwiseKey(int key) { mClockwiseKey = key; }
    void SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }
private:
    // 方向和转向速度的最大值
    float mMaxForwardSpeed;
    float mMaxAngularSpeed;
    
    int mForwardKey;
    int mBackKey;
    
    int mClockwiseKey;
    int mCounterClockwiseKey;
};

#endif /* InputComponent_hpp */
