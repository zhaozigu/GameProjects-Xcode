//
//  Game.hpp
//  PingPong
//
//  Created by guyu on 2020/12/24.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"

// Vector2 结构体仅存储 x 和 y 坐标
struct Vector2
{
    float x;
    float y;
};

// Game class
class Game
{
public:
    Game();
    // 初始化游戏
    bool Initialize();
    // 运行游戏循环直到游戏结束
    void RunLoop();
    // 关闭游戏
    void Shutdown();
private:
    // 处理进程输入
    void ProcessInput();
    // 更新游戏
    void UpdateGame();
    // 生成输出
    void GenerateOutput();
    
    // 通过 SDL 创建窗体
    SDL_Window* mWindow;
    // 渲染器
    SDL_Renderer* mRenderer;
    // 继续运行
    bool mIsRunning;
    
    // 球拍位置
    Vector2 mPaddlePos;
    // 球的位置
    Vector2 mBallPos;
    
    // 球拍方向
    int mPaddleDir;
    
    // 球的速度
    Vector2 mBallVel;
    
    // 记录运行时间
    Uint32 mTicksCount;
};

#endif /* Game_hpp */
