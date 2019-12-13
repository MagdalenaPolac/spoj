#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

struct Activity 
{
	int startTime = 0 ;
	int endTime = 0;
	
	Activity() = default;
	Activity(int start, int end) : startTime(start), endTime(end) {}
};

class DP 
{
public:
	explicit DP(int maxClasses)
		: _maxClasses(maxClasses)
	{
		_subsetCards.resize(maxClasses);
	}
		
	long long countNumOfSubsets(std::vector<Activity>& classes, const int digitToDisplayCount) 
	{
		std::sort(classes.begin(), classes.end(), [](const Activity& a, const Activity& b) { return a.endTime < b.endTime; });

		auto withCount = 0ll;
		auto withoutCount = 1ll;

		_subsetCards[0] = withCount + withoutCount;
		_subsetEnds.push_back(classes[0].endTime);

		for (auto i = 1; i < _maxClasses; ++i) 
		{
			withoutCount = _subsetCards[i - 1];

			if (classes[i].startTime < _subsetEnds[0])
			{
				withCount = 1;
			}
			else 
			{
				auto it = upper_bound(_subsetEnds.begin(), _subsetEnds.end(), classes[i].startTime);
				auto diff = distance(_subsetEnds.begin(), it);
				--diff; //one subset before the found one (because they are sorted by their ends)
				withCount = 1 + _subsetCards[diff];
			}
			_subsetCards[i] = (withCount + withoutCount) % digitToDisplayCount;
			_subsetEnds.push_back(classes[i].endTime);
		}
		return _subsetCards[_maxClasses - 1];
	}

private:
	std::vector<int> _subsetEnds;
	std::vector<long long> _subsetCards;
	int _maxClasses;
};

int main() 
{
	while (true) 
	{
		int classCount;
		std::cin >> classCount;
		if (classCount == -1) break;

		std::vector<Activity> classes;
		for (auto i = 0; i < classCount; ++i) 
		{
			int start, end;
			std::cin >> start >> end;
			classes.emplace_back(start, end);
		}

		DP dp(classCount);
        const auto digitsToDisplay = 100000000;
		std::cout << std::setfill('0') << std::setw(8) << dp.countNumOfSubsets(classes, digitsToDisplay) << std::endl;

		classes.clear();
	}
	return 0;
}
