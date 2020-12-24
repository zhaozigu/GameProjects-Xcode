//
//  Game.cpp
//  PingPong
//
//  Created by 千凡谷梦 on 2020/12/24.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#include "Game.hpp"

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsRunning(true)
{
    
}

bool Game::Initialize()
{
    // 初始化 SDL 库
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        SDL_Log("不能初始化 SDL: %s", SDL_GetError());
        return false;
    }
    
    // 创建 SDL 窗体
    mWindow = SDL_CreateWindow(
                               "PingPong",        // 标题
                               100,               // 窗体左上角的 x 坐标
                               100,               // 窗体左上角的 y 坐标
                               1024,              // 窗体宽度
                               768,               // 窗体高度
                               0                  // 标志位
                               );
    
    if (!mWindow)
    {
        SDL_Log("创建窗体失败: %s", SDL_GetError());
        return false;
    }
    
    // 创建渲染器
    mRenderer = SDL_CreateRenderer(
                                   mWindow,
                                   -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                                   );
    if (!mRenderer)
    {
        SDL_Log("创建渲染器失败: %s", SDL_GetError());
        return false;
    }
    return true;
}

void Game::Shutdown()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    
    // 有 event 在队列就一直循环
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            default:
                break;
        }
    }
}

void Game::UpdateGame()
{
    
}


void Game::GenerateOutput()
{
    // 设置 Tiffany 蓝
    SDL_SetRenderDrawColor(
                           mRenderer,
                           129,             // R
                           216,             // G
                           209,             // B
                           255             // A
                           );
    // 清理后缓冲区
    SDL_RenderClear(mRenderer);
    
    // 交换前后缓冲区
    SDL_RenderPresent(mRenderer);
    
}
