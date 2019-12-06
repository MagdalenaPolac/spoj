#include <algorithm>
#include <iostream>
#include <vector>

int main() 
{
    auto nodeCount = 0;
    auto edgeCount = 0;
    auto testCount = 0; //num of test cases

    std::cin >> testCount;

    for (auto testIndex = 0; testIndex < testCount; ++testIndex) 
    {
        std::cin >> nodeCount;
        edgeCount = nodeCount - 1;

        if (nodeCount == 1) 
        {
            std::cout << 0 << std::endl;
            continue;
        }

        auto graph = std::vector<std::vector<int>>(nodeCount);
        auto visitedNodes = std::vector<bool>(nodeCount, false);

        for (auto i = 0; i < edgeCount; ++i) 
        {
            int x, y;
            std::cin >> x >> y;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }

        auto ranks = std::vector<int>(nodeCount);
        auto currentNodes = std::vector<int>();

        //initialize node ranks
        for (auto i = 0; i < nodeCount; ++i)
        {
            ranks[i] = graph[i].size();
            if (ranks[i] == 1)
            {
                currentNodes.push_back(i);
            }
        }

        auto TTL = 0;
        auto notVisitedCount = nodeCount;
        auto nextNodes = std::vector<int>();
        do 
        {
            for (auto node : currentNodes) 
            {
                visitedNodes[node] = true;
                --notVisitedCount;

                for (auto neighbour : graph[node]) 
                {
                    --ranks[neighbour];
                    if (ranks[neighbour] == 1 && !visitedNodes[neighbour])
                    {
                        nextNodes.push_back(neighbour);
                    }
                }
            }
            ++TTL;
            currentNodes = nextNodes;
            nextNodes.clear();
        } while (notVisitedCount > 1);

        std::cout << TTL << std::endl;
    }
    return 0;
}
