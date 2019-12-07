#include <cmath>
#include <deque>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

const auto MAX_COST = std::numeric_limits<int>::max();

int decodeNodeNumber(const std::string& symbol) 
{
    auto letter = symbol[0];
    auto number = symbol[1];
    auto x = static_cast<int>(letter) - 96;
    auto y = static_cast<int>(number) - 48;

    if (x < 1 || x > 8 || y < 1 || y > 8)
    {
        return 0;
    }
    return ((y - 1) * 8 + x) - 1;
}

int getY(int input) 
{
    return ((input) / 8) + 1;
}

int getX(int input) 
{
    return ((input) % 8) + 1;
}


std::string codeNodeSymbol(int input) 
{
    auto y = getY(input);
    auto x = getX(input);
    auto letter = static_cast<char>(x + 96);
    auto number = static_cast<char>(y + 48);

    return std::string(1, letter) + std::string(1, number);
}

std::vector<int> getNeighbours(int num, int nodeCount) 
{
    auto neighbours = std::vector<int>();
    auto y = getY(num);
    auto x = getX(num);

    if (num + 17 < nodeCount && y + 2 <= 8 && x + 1 <= 8)
        neighbours.push_back(num + 17);

    if (num + 15 < nodeCount && y + 2 <= 8 && x - 1 >= 1)
        neighbours.push_back(num + 15);

    if (num + 10 < nodeCount && y + 1 <= 8 && x + 2 <= 8)
        neighbours.push_back(num + 10);

    if (num + 6 < nodeCount && y + 1 <= 8 && x - 2 >= 1)
        neighbours.push_back(num + 6);

    if (num - 17 >= 0 && y - 2 >= 1 && x - 1 >= 1)
        neighbours.push_back(num - 17);

    if (num - 15 >= 0 && y - 2 >= 1 && x + 1 <= 8)
        neighbours.push_back(num - 15);

    if (num - 10 >= 0 && y - 1 >= 1 && x - 2 >= 1)
        neighbours.push_back(num - 10);

    if (num - 6 >= 0 && y - 1 >= 1 && x + 2 <= 8)
        neighbours.push_back(num - 6);

    return neighbours;
}

struct Node 
{
    int cost = MAX_COST;
    int parent = -1;
    bool optimized = false;
    bool visited = false;
    std::vector<int> neighbours;

    void resetParams() 
    {
        cost = MAX_COST;
        parent = -1;
        visited = false;
        ///neighbours do not change
    }
};

void resetNodes(std::vector<Node>& nodes)
{
    for (auto& node : nodes)
    {
        node.resetParams();
    }
}

int BFS(std::vector<Node>& nodes, int nodeCount, int startNodeId, int destNodeId) 
{
    auto Q = std::deque<int>();
    nodes[startNodeId].cost = 0;

    Q.push_back(startNodeId);
    nodes[startNodeId].visited = true;

    while (!Q.empty())
    {
        auto nodeId = Q.front();
        Q.pop_front();

        if (nodeId == destNodeId) break;

        if (nodes[nodeId].neighbours.size() < 1)
        {
            nodes[nodeId].neighbours = getNeighbours(nodeId, nodeCount);
        }

        for (auto neighbourId : nodes[nodeId].neighbours) 
        {
            if (!nodes[neighbourId].visited) 
            {
                Q.push_back(neighbourId);
                nodes[neighbourId].cost = nodes[nodeId].cost + 1;
                nodes[neighbourId].visited = true;
                nodes[neighbourId].parent = nodeId;
            }
        }
    }
    return nodes[destNodeId].cost;
}

int main() 
{
    const auto squareCount = 64;
    auto squares = std::vector<Node>(squareCount);

    auto testCount = 0;
    std::cin >> testCount;

    for (int i = 0; i < testCount; ++i) 
    {
        resetNodes(squares);
        std::string startSquareSymbol, destSquareSymbol;
        std::cin >> startSquareSymbol >> destSquareSymbol;

        auto startSquareId = decodeNodeNumber(startSquareSymbol);
        auto destSquareId = decodeNodeNumber(destSquareSymbol);

        std::cout << BFS(squares, squareCount, startSquareId, destSquareId) << std::endl;
    }
    return 0;
}
