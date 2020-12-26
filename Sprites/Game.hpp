//
//  Game.hpp
//  Sprites
//
//  Created by guyu on 2020/12/26.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp
#include <vector>
#include <string>
#include "SDL.h"
#include "Math.hpp"
#include "SpriteComponent.hpp"

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
    
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
    
    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);
private:
    SDL_Texture* LoadTexture(const char* fileName);
    
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
    
    // 游戏中的所有actors
    std::vector<class Actor*> mActors;
    // 绘制的所有精灵组件
    std::vector<class SpriteComponent*> mSprites;
    // 待定的actors
    std::vector<class Actor*> mPendingActors;
    // 跟踪现在是否在更新actor
    bool mUpdatingActors;
};

#endif /* Game_hpp */

