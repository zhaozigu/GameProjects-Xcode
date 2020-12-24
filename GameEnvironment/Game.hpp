//
//  Game.hpp
//  GameEnvironment
//
//  Created by 千凡谷梦 on 2020/12/24.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"

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
  // 继续运行
  bool mIsRunning;
};

#endif /* Game_hpp */
