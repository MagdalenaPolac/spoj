#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    auto computerCount = 0;
    auto connectionCount = 0;
    auto testCount = 0; //num of test cases

    std::cin >> testCount;

    for (auto testIndex = 0; testIndex < testCount; ++testIndex)
    {
        std::cin >> computerCount;
        connectionCount = computerCount - 1;

        if (computerCount == 1)
        {
            std::cout << 0 << std::endl;
            continue;
        }

        auto network = std::vector<std::vector<int>>(computerCount);
        auto visitedComputers = std::vector<bool>(computerCount, false);

        for (auto i = 0; i < connectionCount; ++i)
        {
            int computer1, computer2;
            std::cin >> computer1 >> computer2;
            network[computer1].push_back(computer2);
            network[computer2].push_back(computer1);
        }

        auto ranks = std::vector<int>(computerCount);
        auto currentComputers = std::vector<int>();

        //initialize node ranks
        for (auto i = 0; i < computerCount; ++i)
        {
            ranks[i] = network[i].size();
            if (ranks[i] == 1)
            {
                currentComputers.push_back(i);
            }
        }

        auto TTL = 0;
        auto notVisitedCount = computerCount;
        auto nextComputers = std::vector<int>();
        do
        {
            for (auto computer : currentComputers)
            {
                visitedComputers[computer] = true;
                --notVisitedCount;

                for (auto neighbour : network[computer])
                {
                    --ranks[neighbour];
                    if (ranks[neighbour] == 1 && !visitedComputers[neighbour])
                    {
                        nextComputers.push_back(neighbour);
                    }
                }
            }
            ++TTL;
            currentComputers = nextComputers;
            nextComputers.clear();
        } while (notVisitedCount > 1);

        std::cout << TTL << std::endl;
    }
    return 0;
}
