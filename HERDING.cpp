#include <cassert>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

bool followCatPath(std::vector<int>& nextNodeMap, int startNodeIndex, std::vector<int>& groupMap, int groupIndex)
{
	auto nodeIndex = startNodeIndex;
	while (true)
	{
		if (groupMap[nodeIndex] != -1)
		{
			auto nodeGroup = groupMap[nodeIndex];
			auto uniquePath = (nodeGroup == groupIndex); // cycle
			return uniquePath;
		}
		groupMap[nodeIndex] = groupIndex;
		nodeIndex = nextNodeMap[nodeIndex];
	}
}

class CityMap
{
public: 
	CityMap(int NSCellCount, int EWCellCount)
		: _NSCellCount(NSCellCount), _EWCellCount(EWCellCount)
	{}

	int goE(int index) { return index + 1; }
	int goW(int index) { return index - 1; }
	int goS(int index) { return index + _EWCellCount; }
	int goN(int index) { return index - _EWCellCount; }

	int go(int index, char direction)
	{
		switch (direction)
		{
		case 'S':
			return goS(index);
		case 'N':
			return goN(index);
		case 'W':
			return goW(index);
		case 'E':
			return goE(index);
		default:
			assert(false && "Unknown direction");
		}
	}

private:
	int _NSCellCount = 0;
	int _EWCellCount = 0;
};

int main()
{
	auto NSCellCount = 0, EWCellCount = 0;
	std::cin >> NSCellCount >> EWCellCount;

	auto _newLine = std::string();
	std::getline(std::cin, _newLine);

	auto cityCellCount = NSCellCount * EWCellCount;
	auto cityMap = CityMap(NSCellCount, EWCellCount);
	auto catPaths = std::vector<int>(cityCellCount, -1);
	auto catAreas = std::vector<int>(cityCellCount, -1);
	auto startPoints = std::vector<bool>(cityCellCount, true);

	auto cellIndex = 0;
	for (auto i = 0; i < NSCellCount; ++i)
	{
		auto inputLine = std::string();
		std::getline(std::cin, inputLine);
		for (auto j = 0; j < EWCellCount; ++j)
		{
			auto direction = inputLine[j];
			auto nextCell = cityMap.go(cellIndex, direction);
			catPaths[cellIndex] = nextCell;
			startPoints[nextCell] = false;
			++cellIndex;
		}
	}

	auto uniqueAreaCount = 0;
	auto areaIndex = 0;

	// acyclic paths
	for (auto cellIndex = 0; cellIndex < cityCellCount; ++cellIndex)
	{
		if (startPoints[cellIndex])
		{
			auto uniquePath = followCatPath(catPaths, cellIndex, catAreas, areaIndex++);
			if (uniquePath) ++uniqueAreaCount;
		}
	}

	// cyclic paths
	for (auto cellIndex = 0; cellIndex < cityCellCount; ++cellIndex)
	{
		if (catAreas[cellIndex] == -1)
		{
			auto uniquePath = followCatPath(catPaths, cellIndex, catAreas, areaIndex++);
			if (uniquePath) ++uniqueAreaCount;
		}
	}

	std::cout << uniqueAreaCount;
	return 0;
}
