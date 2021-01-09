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
#include <unordered_map>
#include "SDL.h"
#include "Math.hpp"
#include "SpriteComponent.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"

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
    
    SDL_Texture* GetTexture(const std::string& fileName);
    
    class Grid* GetGrid() { return mGrid; }
    std::vector<class Enemy*>& GetEnemies() { return mEnemies; }
    class Enemy* GetNearestEnemy(const Vector2& pos);
private:
    void LoadData();
    void UnloadData();
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
    
    // 已加载的 textures
    std::unordered_map<std::string, SDL_Texture*> mTextures;
    
    std::vector<class Enemy*> mEnemies;
    class Grid* mGrid;
    float mNextEnemy;
};

#endif /* Game_hpp */

