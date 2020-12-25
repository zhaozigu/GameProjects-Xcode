//
//  main.cpp
//  Sprites
//
//  Created by guyu on 2020/12/26.
//  Copyright © 2020 guyu2019. All rights reserved.
//

#include "Game.hpp"

int main(int argc, const char * argv[]) {
    Game game;
    bool success = game.Initialize();
    
    if (success)
    {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
