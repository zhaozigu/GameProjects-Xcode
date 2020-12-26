//
//  Random.hpp
//  BasicPhysics
//
//  Created by guyu on 2020/12/27.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#ifndef Random_hpp
#define Random_hpp

#include <random>
#include "Math.hpp"

class Random
{
public:
    static void Init();

    // 用特定的数字作种子
    // NOTE: 应该自动生成而不是手动设定
    static void Seed(unsigned int seed);

    // 获取从 0.0f 到 1.0f 之间的浮点数
    static float GetFloat();
    
    // 在给定的范围中获取浮点数
    static float GetFloatRange(float min, float max);

    // 在给定的范围中获得一个 int 值
    static int GetIntRange(int min, int max);

    // 在给定的最小/最大范围中获得一个随机的向量
    static Vector2 GetVector(const Vector2& min, const Vector2& max);
    static Vector3 GetVector(const Vector3& min, const Vector3& max);
private:
    static std::mt19937 sGenerator;
};


#endif /* Random_hpp */
