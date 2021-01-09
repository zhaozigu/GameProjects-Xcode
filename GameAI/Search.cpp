//
//  Search.cpp
//  GameAI
//
//  Created by guyu on 2021/1/2.
//  Copyright © 2021 guyu2019. All rights reserved.
//

#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>

struct GraphNode
{
    // 领接表
    std::vector<GraphNode*> mAdjacent;
};

struct Graph
{
    std::vector<GraphNode*> mNodes;
};

struct WeightedEdge
{
    // 哪个结点被这条边联系？
    struct WeightedGraphNode* mFrom;
    struct WeightedGraphNode* mTo;
    // 边的权重
    float mWeight;
};

struct WeightedGraphNode
{
    std::vector<WeightedEdge*> mEdges;
};

struct WeightedGraph
{
    std::vector<WeightedGraphNode*> mNodes;
};

struct GBFSScratch
{
    const WeightedEdge* mParentEdge = nullptr;
    float mHeuristic = 0.0f;
    bool mInOpenSet = false;
    bool mInClosedSet = false;
};

using GBFSMap =
std::unordered_map<const WeightedGraphNode*, GBFSScratch>;

struct AStarScratch
{
    const WeightedEdge* mParentEdge = nullptr;
    float mHeuristic = 0.0f;
    float mActualFromStart = 0.0f;
    bool mInOpenSet = false;
    bool mInClosedSet = false;
};

using AStarMap =
std::unordered_map<const WeightedGraphNode*, AStarScratch>;

float ComputeHeuristic(const WeightedGraphNode* a, const WeightedGraphNode* b)
{
    return 0.0f;
}

bool AStar(const WeightedGraph& g, const WeightedGraphNode* start,
    const WeightedGraphNode* goal, AStarMap& outMap)
{
    std::vector<const WeightedGraphNode*> openSet;

    // 设置起点，并且在闭集中标记
    const WeightedGraphNode* current = start;
    outMap[current].mInClosedSet = true;

    do
    {
        // 添加邻接结点到开集
        for (const WeightedEdge* edge : current->mEdges)
        {
            const WeightedGraphNode* neighbor = edge->mTo;
            // 获取暂存数据
            AStarScratch& data = outMap[neighbor];
            // 只检查不在闭集里的
            if (!data.mInClosedSet)
            {
                if (!data.mInOpenSet)
                {
                    // 不在开集中，所以父结点必定是当前的
                    data.mParentEdge = edge;
                    data.mHeuristic = ComputeHeuristic(neighbor, goal);
                    // 实际成本是父结点成本加边的成本
                    data.mActualFromStart = outMap[current].mActualFromStart +
                        edge->mWeight;
                    data.mInOpenSet = true;
                    openSet.emplace_back(neighbor);
                }
                else
                {
                    // 计算当前结点成为父结点时的新实际成本
                    float newG = outMap[current].mActualFromStart + edge->mWeight;
                    if (newG < data.mActualFromStart)
                    {
                        // 采用这个结点
                        data.mParentEdge = edge;
                        data.mActualFromStart = newG;
                    }
                }
            }
        }

        // 如果开集为空，所有路径已经穷尽
        if (openSet.empty())
        {
            break;
        }

        // 在开集中找到成本最低的结点
        auto iter = std::min_element(openSet.begin(), openSet.end(),
            [&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b) {
            // 计算 a/b 的 f(x) 值
            float fOfA = outMap[a].mHeuristic + outMap[a].mActualFromStart;
            float fOfB = outMap[b].mHeuristic + outMap[b].mActualFromStart;
            return fOfA < fOfB;
        });
        // 设置当前结点并移到闭集
        current = *iter;
        openSet.erase(iter);
        outMap[current].mInOpenSet = true;
        outMap[current].mInClosedSet = true;
    } while (current != goal);

    // 找到路径了没？
    return (current == goal) ? true : false;
}

bool GBFS(const WeightedGraph& g, const WeightedGraphNode* start,
    const WeightedGraphNode* goal, GBFSMap& outMap)
{
    std::vector<const WeightedGraphNode*> openSet;

    // 设置起点，并且在闭集中标记
    const WeightedGraphNode* current = start;
    outMap[current].mInClosedSet = true;

    do
    {
        // 添加邻接点到开集
        for (const WeightedEdge* edge : current->mEdges)
        {
            GBFSScratch& data = outMap[edge->mTo];
            // 只加入不在空集里的结点
            if (!data.mInClosedSet)
            {
                // Set the adjacent node's parent edge
                data.mParentEdge = edge;
                if (!data.mInOpenSet)
                {
                    // 计算结点启发式成本，添加到开集
                    data.mHeuristic = ComputeHeuristic(edge->mTo, goal);
                    data.mInOpenSet = true;
                    openSet.emplace_back(edge->mTo);
                }
            }
        }

        // 如果开集已空，所有路径已经穷尽
        if (openSet.empty())
        {
            break;
        }

        // 在开集中找到最小成本的点
        auto iter = std::min_element(openSet.begin(), openSet.end(),
            [&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b) {
            return outMap[a].mHeuristic < outMap[b].mHeuristic;
        });

        // 设置 current 结点，并从开集移动到闭集
        current = *iter;
        openSet.erase(iter);
        outMap[current].mInOpenSet = false;
        outMap[current].mInClosedSet = true;
    } while (current != goal);

    // 我们找到路径了没？
    return (current == goal) ? true : false;
}

using NodeToParentMap =
std::unordered_map<const GraphNode*, const GraphNode*>;

bool BFS(const Graph& graph, const GraphNode* start, const GraphNode* goal, NodeToParentMap& outMap)
{
    // 是否找到路径
    bool pathFound = false;
    
    std::queue<const GraphNode*> q;
    // 起点入列
    q.emplace(start);

    while (!q.empty())
    {
        // 第一个元素出列
        const GraphNode* current = q.front();
        q.pop();
        if (current == goal)
        {
            pathFound = true;
            break;
        }
        
        for (const GraphNode* node : current->mAdjacent)
        {
            const GraphNode* parent = outMap[node];
            if (parent == nullptr && node != start)
            {
                outMap[node] = current;
                q.emplace(node);
            }
        }
    }

    return pathFound;
}

void testBFS()
{
    Graph g;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            GraphNode* node = new GraphNode;
            g.mNodes.emplace_back(node);
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            GraphNode* node = g.mNodes[i * 5 + j];
            if (i > 0)
            {
                node->mAdjacent.emplace_back(g.mNodes[(i - 1) * 5 + j]);
            }
            if (i < 4)
            {
                node->mAdjacent.emplace_back(g.mNodes[(i + 1) * 5 + j]);
            }
            if (j > 0)
            {
                node->mAdjacent.emplace_back(g.mNodes[i * 5 + j - 1]);
            }
            if (j < 4)
            {
                node->mAdjacent.emplace_back(g.mNodes[i * 5 + j + 1]);
            }
        }
    }

    NodeToParentMap map;
    bool found = BFS(g, g.mNodes[0], g.mNodes[9], map);
    std::cout << found << '\n';
}

void testHeuristic(bool useAStar)
{
    WeightedGraph g;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            WeightedGraphNode* node = new WeightedGraphNode;
            g.mNodes.emplace_back(node);
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            WeightedGraphNode* node = g.mNodes[i * 5 + j];
            if (i > 0)
            {
                WeightedEdge* e = new WeightedEdge;
                e->mFrom = node;
                e->mTo = g.mNodes[(i - 1) * 5 + j];
                e->mWeight = 1.0f;
                node->mEdges.emplace_back(e);
            }
            if (i < 4)
            {
                WeightedEdge* e = new WeightedEdge;
                e->mFrom = node;
                e->mTo = g.mNodes[(i + 1) * 5 + j];
                e->mWeight = 1.0f;
                node->mEdges.emplace_back(e);
            }
            if (j > 0)
            {
                WeightedEdge* e = new WeightedEdge;
                e->mFrom = node;
                e->mTo = g.mNodes[i * 5 + j - 1];
                e->mWeight = 1.0f;
                node->mEdges.emplace_back(e);
            }
            if (j < 4)
            {
                WeightedEdge* e = new WeightedEdge;
                e->mFrom = node;
                e->mTo = g.mNodes[i * 5 + j + 1];
                e->mWeight = 1.0f;
                node->mEdges.emplace_back(e);
            }
        }
    }
    bool found = false;
    if (useAStar)
    {
        AStarMap map;
        found = AStar(g, g.mNodes[0], g.mNodes[9], map);
    }
    else
    {
        GBFSMap map;
        found = GBFS(g, g.mNodes[0], g.mNodes[9], map);
    }
    std::cout << found << '\n';
}

struct GameState
{
    // 井字棋
    enum SquareState { Empty, X, O };
    SquareState mBoard[3][3];
};

struct GTNode
{
    std::vector<GTNode*> mChildren;
    GameState mState;
};

void GenStates(GTNode* root, bool xPlayer)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (root->mState.mBoard[i][j] == GameState::Empty)
            {
                GTNode* node = new GTNode;
                root->mChildren.emplace_back(node);
                node->mState = root->mState;
                node->mState.mBoard[i][j] = xPlayer ? GameState::X : GameState::O;
                GenStates(node, !xPlayer);
            }
        }
    }
}

float GetScore(const GameState& state)
{
    for (int i = 0; i < 3; i++)
    {
        bool same = true;
        GameState::SquareState v = state.mBoard[i][0];
        for (int j = 1; j < 3; j++)
        {
            if (state.mBoard[i][j] != v)
            {
                same = false;
            }
        }

        if (same)
        {
            if (v == GameState::X)
            {
                return 1.0f;
            }
            else
            {
                return -1.0f;
            }
        }
    }

    for (int j = 0; j < 3; j++)
    {
        bool same = true;
        GameState::SquareState v = state.mBoard[0][j];
        for (int i = 1; i < 3; i++)
        {
            if (state.mBoard[i][j] != v)
            {
                same = false;
            }
        }

        if (same)
        {
            if (v == GameState::X)
            {
                return 1.0f;
            }
            else
            {
                return -1.0f;
            }
        }
    }

    // 对角线
    if (((state.mBoard[0][0] == state.mBoard[1][1]) &&
        (state.mBoard[1][1] == state.mBoard[2][2])) ||
        ((state.mBoard[2][0] == state.mBoard[1][1]) &&
        (state.mBoard[1][1] == state.mBoard[0][2])))
    {
        if (state.mBoard[1][1] == GameState::X)
        {
            return 1.0f;
        }
        else
        {
            return -1.0f;
        }
    }
    // 平局
    return 0.0f;
}

float MinPlayer(const GTNode* node);

float MaxPlayer(const GTNode* node)
{
    if (node->mChildren.empty())
    {
        return GetScore(node->mState);
    }

    float maxValue = -std::numeric_limits<float>::infinity();
    for (const GTNode* child : node->mChildren)
    {
        maxValue = std::max(maxValue, MinPlayer(child));
    }
    return maxValue;
}

float MinPlayer(const GTNode* node)
{
    if (node->mChildren.empty())
    {
        return GetScore(node->mState);
    }

    float minValue = std::numeric_limits<float>::infinity();
    for (const GTNode* child : node->mChildren)
    {
        minValue = std::min(minValue, MaxPlayer(child));
    }
    return minValue;
}

const GTNode* MinimaxDecide(const GTNode* root)
{
    const GTNode* choice = nullptr;
    float maxValue = -std::numeric_limits<float>::infinity();
    for (const GTNode* child : root->mChildren)
    {
        float v = MinPlayer(child);
        if (v > maxValue)
        {
            maxValue = v;
            choice = child;
        }
    }
    return choice;
}

float AlphaBetaMin(const GTNode* node, float alpha, float beta);

float AlphaBetaMax(const GTNode* node, float alpha, float beta)
{
    if (node->mChildren.empty())
    {
        return GetScore(node->mState);
    }

    float maxValue = -std::numeric_limits<float>::infinity();
    for (const GTNode* child : node->mChildren)
    {
        maxValue = std::max(maxValue, AlphaBetaMin(child, alpha, beta));
        if (maxValue >= beta)
        {
            return maxValue; // Beta 剪枝
        }
        alpha = std::max(maxValue, alpha);
    }
    return maxValue;
}

float AlphaBetaMin(const GTNode* node, float alpha, float beta)
{
    if (node->mChildren.empty())
    {
        return GetScore(node->mState);
    }

    float minValue = std::numeric_limits<float>::infinity();
    for (const GTNode* child : node->mChildren)
    {
        minValue = std::min(minValue, AlphaBetaMax(child, alpha, beta));
        if (minValue <= alpha)
        {
            return minValue; // Alpha 剪枝
        }
        beta = std::min(minValue, beta);
    }
    return minValue;
}

const GTNode* AlphaBetaDecide(const GTNode* root)
{
    const GTNode* choice = nullptr;
    float maxValue = -std::numeric_limits<float>::infinity();
    float beta = std::numeric_limits<float>::infinity();
    for (const GTNode* child : root->mChildren)
    {
        float v = AlphaBetaMin(child, maxValue, beta);
        if (v > maxValue)
        {
            maxValue = v;
            choice = child;
        }
    }
    return choice;
}

void testTicTac()
{
    GTNode* root = new GTNode;
    root->mState.mBoard[0][0] = GameState::O;
    root->mState.mBoard[0][1] = GameState::Empty;
    root->mState.mBoard[0][2] = GameState::X;
    root->mState.mBoard[1][0] = GameState::X;
    root->mState.mBoard[1][1] = GameState::O;
    root->mState.mBoard[1][2] = GameState::O;
    root->mState.mBoard[2][0] = GameState::X;
    root->mState.mBoard[2][1] = GameState::Empty;
    root->mState.mBoard[2][2] = GameState::Empty;

    GenStates(root, true);
    const GTNode* choice = AlphaBetaDecide(root);
    std::cout << choice->mChildren.size();
}
