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
#include "Ship.hpp"
#include "Asteroid.hpp"

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
    
    void AddAsteroid(class Asteroid* ast);
    void RemoveAsteroid(class Asteroid* ast);
    std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }
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
    
    // 玩家控制的飞船
    class Ship* mShip;
    std::vector<class Asteroid*> mAsteroids;
};

#endif /* Game_hpp */

