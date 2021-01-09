//
//  Grid.hpp
//  GameAI
//
//  Created by guyu on 2021/1/9.
//  Copyright © 2021 guyu2019. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include "Actor.hpp"
#include <vector>

class Grid : public Actor
{
public:
    Grid(class Game* game);
    
    // 处理鼠标点击位置
    void ProcessClick(int x, int y);
    
    // 使用A*寻路算法
    bool FindPath(class Tile* start, class Tile* goal);
    
    // 尝试建塔
    void BuildTower();
    
    // 获取游戏起点和终点
    class Tile* GetStartTile();
    class Tile* GetEndTile();

    void UpdateActor(float deltaTime) override;
private:
    // 选择特殊的块
    void SelectTile(size_t row, size_t col);
    
    void UpdatePathTiles(class Tile* start);
    
    // 当前选择的小块
    class Tile* mSelectedTile;
    
    // 二维数组存储小块
    std::vector<std::vector<class Tile*>> mTiles;
    
    float mNextEnemy;
    
    // 网格的行列数
    const size_t kNumRows = 7;
    const size_t kNumCols = 16;
    // 起始点距离左上角位置
    const float kStartY = 192.0f;
    // 每个小块的长/宽
    const float kTileSize = 64.0f;
    // 两个敌人的间隔
    const float kEnemyTime = 1.5f;
};


#endif /* Grid_hpp */
