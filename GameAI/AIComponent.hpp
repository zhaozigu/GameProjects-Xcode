//
//  AIComponent.hpp
//  GameAI
//
//  Created by guyu on 2021/1/2.
//  Copyright © 2021 guyu2019. All rights reserved.
//

#ifndef AIComponent_hpp
#define AIComponent_hpp

#include "Component.hpp"
#include <unordered_map>
#include <string>

class AIComponent : public Component
{
public:
    AIComponent(class Actor* owner);
    
    void Update(float deltaTime) override;
    void ChangeState(const std::string& name);
    
    // 添加新状态
    void RegisterState(class AIState* state);
private:
    // 映射状态名到 AIState 实例
    std::unordered_map<std::string, class AIState*> mStateMap;
    // 当前状态
    class AIState* mCurrentState;
};


#endif /* AIComponent_hpp */
