//
//  Actor.hpp
//  Sprites
//
//  Created by guyu on 2020/12/26.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#ifndef Actor_hpp
#define Actor_hpp

#include <vector>
#include "Math.hpp"

class Actor
{
public:
    enum State
    {
        EActive,
        EPaused,
        EDead
    };
    
    Actor(class Game* game);
    virtual ~Actor();
    
    // 从 Game 调用 Update 函数 (不被继承重写)
    void Update(float deltaTime);
    // 更新属于该actor的所有组件 (不被继承重写)
    void UpdateComponents(float deltaTime);
    // actor特有更新代码 (可重写)
    virtual void UpdateActor(float deltaTime);
    
    // Getters/setters
    const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos) { mPosition = pos; }
    float GetScale() const { return mScale; }
    void SetScale(float scale) { mScale = scale; }
    float GetRotation() const { return mRotation; }
    void SetRotation(float rotation) { mRotation = rotation; }
    
    Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }
    
    State GetState() const { return mState; }
    void SetState(State state) { mState = state; }
    
    class Game* GetGame() { return mGame; }
    
    // 添加/移除 组件
    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);
    
    // 被 Game 调用的的 ProcessInput（不可重写）
    void ProcessInput(const uint8_t* keyState);
    // 特定 Actor 输入（可重写）
    virtual void ActorInput(const uint8_t* keyState);
private:
    // Actor的状态
    State mState;
    
    // 变形
    Vector2 mPosition;
    float mScale;
    float mRotation;
    
    std::vector<class Component*> mComponents;
    class Game* mGame;
};

#endif /* Actor_hpp */
