//
//  Grid.cpp
//  GameAI
//
//  Created by guyu on 2021/1/9.
//  Copyright © 2021 guyu2019. All rights reserved.
//

#include "Grid.hpp"
#include "Tile.hpp"
#include "Tower.hpp"
#include "Enemy.hpp"
#include <algorithm>

Grid::Grid(class Game* game)
:Actor(game)
,mSelectedTile(nullptr)
{
    // 7 行, 16 列
    mTiles.resize(kNumRows);
    for (size_t i = 0; i < mTiles.size(); i++)
    {
        mTiles[i].resize(kNumCols);
    }
    
    // 创建小方块
    for (size_t i = 0; i < kNumRows; i++)
    {
        for (size_t j = 0; j < kNumCols; j++)
        {
            mTiles[i][j] = new Tile(GetGame());
            mTiles[i][j]->SetPosition(Vector2(kTileSize/2.0f + j * kTileSize, kStartY + i * kTileSize));
        }
    }
    
    // 设置起止点
    GetStartTile()->SetTileState(Tile::EStart);
    GetEndTile()->SetTileState(Tile::EBase);
    
    // 建立邻接表
    for (size_t i = 0; i < kNumRows; i++)
    {
        for (size_t j = 0; j < kNumCols; j++)
        {
            if (i > 0)
            {
                mTiles[i][j]->mAdjacent.push_back(mTiles[i-1][j]);
            }
            if (i < kNumRows - 1)
            {
                mTiles[i][j]->mAdjacent.push_back(mTiles[i+1][j]);
            }
            if (j > 0)
            {
                mTiles[i][j]->mAdjacent.push_back(mTiles[i][j-1]);
            }
            if (j < kNumCols - 1)
            {
                mTiles[i][j]->mAdjacent.push_back(mTiles[i][j+1]);
            }
        }
    }
    
    // 反向寻路
    FindPath(GetEndTile(), GetStartTile());
    UpdatePathTiles(GetStartTile());
    
    mNextEnemy = kEnemyTime;
}

void Grid::SelectTile(size_t row, size_t col)
{
    // 确保是个有效选择
    Tile::TileState tstate = mTiles[row][col]->GetTileState();
    if (tstate != Tile::EStart && tstate != Tile::EBase)
    {
        // 取消上一个的选择
        if (mSelectedTile)
        {
            mSelectedTile->ToggleSelect();
        }
        mSelectedTile = mTiles[row][col];
        mSelectedTile->ToggleSelect();
    }
}

void Grid::ProcessClick(int x, int y)
{
    y -= static_cast<int>(kStartY - kTileSize / 2);
    if (y >= 0)
    {
        x /= static_cast<int>(kTileSize);
        y /= static_cast<int>(kTileSize);
        if (x >= 0 && x < static_cast<int>(kNumCols) && y >= 0 && y < static_cast<int>(kNumRows))
        {
            SelectTile(y, x);
        }
    }
}

// A* 寻路算法的实现
bool Grid::FindPath(Tile* start, Tile* goal)
{
    for (size_t i = 0; i < kNumRows; i++)
    {
        for (size_t j = 0; j < kNumCols; j++)
        {
            mTiles[i][j]->g = 0.0f;
            mTiles[i][j]->mInOpenSet = false;
            mTiles[i][j]->mInClosedSet = false;
        }
    }
    
    std::vector<Tile*> openSet;
    
    // 设置起点，并添加到闭集
    Tile* current = start;
    current->mInClosedSet = true;
    
    do
    {
        // 将邻接结点添加到开集
        for (Tile* neighbor : current->mAdjacent)
        {
            if (neighbor->mBlocked)
            {
                continue;
            }
            
            // 只检查不在闭集的结点
            if (!neighbor->mInClosedSet)
            {
                if (!neighbor->mInOpenSet)
                {
                    // Not in the open set, so set parent
                    neighbor->mParent = current;
                    neighbor->h = (neighbor->GetPosition() - goal->GetPosition()).Length();
                    // g(x) is the parent's g plus cost of traversing edge
                    neighbor->g = current->g + kTileSize;
                    neighbor->f = neighbor->g + neighbor->h;
                    openSet.emplace_back(neighbor);
                    neighbor->mInOpenSet = true;
                }
                else
                {
                    // 计算 g(x) 成本
                    float newG = current->g + kTileSize;
                    if (newG < neighbor->g)
                    {
                        neighbor->mParent = current;
                        neighbor->g = newG;
                        // f(x) 因 g(x) 改变而改变
                        neighbor->f = neighbor->g + neighbor->h;
                    }
                }
            }
        }
        
        // 开集为空，则所有路径已经穷尽
        if (openSet.empty())
        {
            break;
        }
        
        // 在开集中找到成本最低的结点
        auto iter = std::min_element(openSet.begin(), openSet.end(),
                                     [](Tile* a, Tile* b) {
                                         return a->f < b->f;
                                     });
        // 设置当前结点并从开集移动到闭集
        current = *iter;
        openSet.erase(iter);
        current->mInOpenSet = false;
        current->mInClosedSet = true;
    }
    while (current != goal);
    
    // 是否找到了路径
    return (current == goal) ? true : false;
}

void Grid::UpdatePathTiles(class Tile* start)
{
    // 除了起点和终点，设置成默认值
    for (size_t i = 0; i < kNumRows; i++)
    {
        for (size_t j = 0; j < kNumCols; j++)
        {
            if (!(i == kNumRows / 2 && j == 0) && !(i == kNumRows / 2 && j == kNumCols - 1))
            {
                mTiles[i][j]->SetTileState(Tile::EDefault);
            }
        }
    }
    
    Tile* t = start->mParent;
    while (t != GetEndTile())
    {
        t->SetTileState(Tile::EPath);
        t = t->mParent;
    }
}

void Grid::BuildTower()
{
    if (mSelectedTile && !mSelectedTile->mBlocked)
    {
        mSelectedTile->mBlocked = true;
        if (FindPath(GetEndTile(), GetStartTile()))
        {
            Tower* t = new Tower(GetGame());
            t->SetPosition(mSelectedTile->GetPosition());
        }
        else
        {
            // 防御塔阻碍了路径，不允许建造防御塔
            mSelectedTile->mBlocked = false;
            FindPath(GetEndTile(), GetStartTile());
        }
        UpdatePathTiles(GetStartTile());
    }
}

Tile* Grid::GetStartTile()
{
    return mTiles[3][0];
}

Tile* Grid::GetEndTile()
{
    return mTiles[3][15];
}

void Grid::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    
    // 到了生产新敌人的时刻？
    mNextEnemy -= deltaTime;
    if (mNextEnemy <= 0.0f)
    {
        new Enemy(GetGame());
        mNextEnemy += kEnemyTime;
    }
}
