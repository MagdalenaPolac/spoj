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
    int id = -1 ;
    int cost = MAX_COST;	//cost from parent
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
        auto  cityCount = 0, highwayCount = 0, startCityId = -1, destCityId = -1;
        std::cin >> cityCount >> highwayCount >> startCityId >> destCityId;
        --startCityId;	//first node index = 0 instead of 1
        --destCityId;

        // initialize nodes
        auto cities = std::vector<Node>(cityCount);
        for (auto i = 0; i < cityCount; ++i) 
        {
            cities[i].id = i;
        }

        // define graph
        auto cityConnections = std::vector<std::vector<Edge>>(cityCount);
        for (auto i = 0; i < highwayCount; ++i) 
        {
            int cityId1, cityId2, travelTime;
            std::cin >> cityId1 >> cityId2 >> travelTime;
            cityConnections[cityId1 - 1].emplace_back(Edge(cityId2 - 1, travelTime));
            cityConnections[cityId2 - 1].emplace_back(Edge(cityId1 - 1, travelTime)); //bidirectional graph
        }

        auto minTravelTime = dijkstra(cities, cityConnections, cityCount, startCityId, destCityId);

        (minTravelTime == MAX_COST) ? std::cout << "NONE" : std::cout << minTravelTime;
        std::cout << std::endl;
    }
    return 0;
}
