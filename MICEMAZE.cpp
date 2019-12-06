#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>
#include <queue>

const auto MAX_COST = std::numeric_limits<int>::max();

struct Edge
{
    int id; // id of the second node (the first one is defined by its position in the graph array)
    int cost;

    Edge(int _secondNodeId, int _cost) : id(_secondNodeId), cost(_cost) {}
};

struct Node
{
    int id = -1;
    int cost = MAX_COST;	//cost from parent
    int parentId = -1;

    Node() = default;
    Node(int _id) : id(_id) {}

    bool operator>(const Node &rhs) const
    {
        return cost > rhs.cost;
    }
};


void dijkstra(std::vector<Node>& nodes, const std::vector<std::vector<Edge>>& graf, int nodeCount, int startNodeId)
{
    nodes[startNodeId].cost = 0;	//in fact it is a destNode, but we have an inversed graph

    auto optimized = std::vector<bool>(nodeCount, false);
    auto Q = std::priority_queue<Node, std::vector<Node>, std::greater<Node>>();
    Q.push(nodes[startNodeId]);

    while (!Q.empty())
    {
        auto currNode = Q.top();
        auto nodeId = currNode.id;
        Q.pop();
        optimized[nodeId] = true;

        for (const auto& neighbour : graf[nodeId])
        {
            if (!optimized[neighbour.id])
            {
                if (nodes[neighbour.id].cost > nodes[nodeId].cost + neighbour.cost)
                {
                    nodes[neighbour.id].cost = nodes[nodeId].cost + neighbour.cost;
                    nodes[neighbour.id].parentId = nodeId;
                    Q.push(nodes[neighbour.id]);
                }
            }
        }
    }
}


int main() 
{
    auto startCellId = -1, cellCount = 0, connectionCount = 0;
    auto timeLimit = 0;

    std::cin >> cellCount;
    std::cin >> startCellId;
    --startCellId;	//first node index = 0 instead of 1
    std::cin >> timeLimit;
    std::cin >> connectionCount;

    // initialize nodes nodes
    auto cells = std::vector<Node>(cellCount);
    for (auto i = 0; i < cellCount; ++i) 
    {
        cells[i].id = i;
    }

    // define graph
    auto cellMaze = std::vector<std::vector<Edge>>(cellCount);

    for (auto i = 0; i < connectionCount; ++i) 
    {
        int cell1, cell2, time;
        std::cin >> cell1 >> cell2 >> time;
        cellMaze[cell2 - 1].emplace_back(Edge(cell1 - 1, time)); //inversed graph
    }
    std::cout << std::endl;

    dijkstra(cells, cellMaze, cellCount, startCellId);

    // count sucessful mice
    auto sucessfulMiceCount = 0;
    for (const auto& node: cells) 
    {
        if (node.cost <= timeLimit)
        {
            sucessfulMiceCount += 1;
        }  
    }
    std::cout << sucessfulMiceCount;
    return 0;
}
