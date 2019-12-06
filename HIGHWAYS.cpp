#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>
#include <queue>

const auto MAXPRICE = std::numeric_limits<int>::max();

struct Edge 
{
    int id; // id of the second node (the first one is defined by its position in the graph array)
    int cost;

    Edge(int _secondNodeId, int _cost) : id(_secondNodeId), cost(_cost) {}
};

struct Node 
{
    int id = -1 ;
    int cost = MAXPRICE;	//cost from parent
    int parentId = -1;

    Node() = default;
    Node(int _id) : id(_id) {}

    bool operator>(const Node &rhs) const 
    {
        return cost > rhs.cost;
    }
};

int dijkstra(std::vector<Node>& nodes, const std::vector<std::vector<Edge>>& graf, int nodeCount, int startNodeId, int destNodeId)
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

        if (nodeId == destNodeId) break;

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
    return nodes[destNodeId].cost;
}

int main() 
{
    auto testCount = 0;
    std::cin >> testCount;

    for (auto testNum = 0; testNum < testCount; ++testNum) 
    {
        auto  nodeCount = 0, edgeCount = 0, startNodeId = -1, destNodeId = -1;
        std::cin >> nodeCount >> edgeCount >> startNodeId >> destNodeId;
        --startNodeId;	//first node index = 0 instead of 1
        --destNodeId;

        // initialize nodes
        auto nodes = std::vector<Node>(nodeCount);
        for (auto i = 0; i < nodeCount; ++i) 
        {
            nodes[i].id = i;
        }

        // define graph
        auto graf = std::vector<std::vector<Edge>>(nodeCount);
        for (auto i = 0; i < edgeCount; ++i) 
        {
            int x, y, w;
            std::cin >> x >> y >> w;
            graf[x - 1].emplace_back(Edge(y - 1, w));
            graf[y - 1].emplace_back(Edge(x - 1, w)); //bidirectional graph
        }

        auto cost = dijkstra(nodes, graf, nodeCount, startNodeId, destNodeId);

        (cost == MAXPRICE) ? std::cout << "NONE" : std::cout << cost;
        std::cout << std::endl;
    }
    return 0;
}
