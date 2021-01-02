//
//  AIState.hpp
//  GameAI
//
//  Created by guyu on 2021/1/2.
//  Copyright © 2021 guyu2019. All rights reserved.
//

#ifndef AIState_hpp
#define AIState_hpp

#include "AIComponent.hpp"

class AIState
{
public:
    AIState(class AIComponent* owner): mOwner(owner) {
        
    }
    // 特定状态行为
    virtual void Update(float deltaTime) = 0;
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    // 获取状态的名字
    virtual const char* GetName() const = 0;
protected:
    class AIComponent* mOwner;
};

class AIPatrol : public AIState
{
public:
    AIPatrol(class AIComponent* owner)
        :AIState(owner)
    { }

    // 重写行为
    void Update(float deltaTime) override;
    void OnEnter() override;
    void OnExit() override;

    const char* GetName() const override
    { return "Patrol"; }
};

class AIDeath : public AIState
{
public:
    AIDeath(class AIComponent* owner)
        :AIState(owner)
    { }

    void Update(float deltaTime) override;
    void OnEnter() override;
    void OnExit() override;

    const char* GetName() const override
    { return "Death"; }
};

class AIAttack : public AIState
{
public:
    AIAttack(class AIComponent* owner)
        :AIState(owner)
    { }

    void Update(float deltaTime) override;
    void OnEnter() override;
    void OnExit() override;

    const char* GetName() const override
    { return "Attack"; }
};


#endif /* AIState_hpp */
