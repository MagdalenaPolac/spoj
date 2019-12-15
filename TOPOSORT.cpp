#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

class TopoSorter 
{
public:
	// prerequisites: vector of (a, b) pairs, where a depends on b (b must be executed before a)
	std::vector<int> findOrder(int taskCount, const std::vector<std::pair<int, int>>& prerequisites)
	{
		buildGraph(taskCount, prerequisites);
		for (auto i = 0; i < taskCount; ++i)
		{
			if (dependencyCount[i] == 0)
			{
				toProceed.push(i);
			}
		}

		while (!toProceed.empty())
		{
			auto current = toProceed.top();
			toProceed.pop();
			order.push_back(current);
			updateOrder(current);
		}

		for (auto count : dependencyCount)
		{
			if (count != 0)
			{
				return {};
			}
		}
		return order;
	}

private:
	void buildGraph(int taskCount, const std::vector<std::pair<int, int>>& prerequisites)
	{
		dependentOn = std::vector<std::vector<int>>(taskCount);
		dependencyCount = std::vector<int>(taskCount, 0);
		for (auto i = 0; i < prerequisites.size(); ++i)
		{
			dependentOn[prerequisites[i].second].push_back(prerequisites[i].first);
			dependencyCount[prerequisites[i].first] += 1;
		}
	}

	void updateOrder(int index)
	{
		for (auto el : dependentOn[index])
		{
			dependencyCount[el] -= 1;
			if (dependencyCount[el] == 0)
			{
				toProceed.push(el);
			}
		}
	}

	std::vector<std::vector<int>> dependentOn;
	std::vector<int> dependencyCount;
	std::vector<int> order;
	std::priority_queue<int, std::vector<int>, std::greater<int>> toProceed;
};

int main()
{
	auto taskCount = 0;
	std::cin >> taskCount;

	auto prerequisiteCount = 0;
	std::cin >> prerequisiteCount;
	
	
	auto prerequisites = std::vector<std::pair<int, int>>(prerequisiteCount);  
	for (auto i = 0; i < prerequisiteCount; ++i)
	{
		int task, dependentTask;
		std::cin >> task >> dependentTask;
		prerequisites[i] = { dependentTask - 1, task - 1 }; // indexing from 0
	}
	
	auto order = TopoSorter().findOrder(taskCount, prerequisites);
	
	if (order.empty())
	{
		std::cout << "Sandro fails.";
	}
	else
	{
		for (auto task : order)
		{
			std::cout << task + 1 << ' '; // back to the original indexing
		}
	}
	return 0;
}
