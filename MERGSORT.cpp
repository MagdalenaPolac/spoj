#include <cassert>
#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <vector>

class Sorter 
{
public:
	void sortArray(std::vector<int>& nums)
	{
		if (nums.empty()) return;

		assert(nums.size() < std::numeric_limits<int>::max());
		auto numsSize = static_cast<int>(nums.size());
		helper = std::vector<int>(numsSize);
		mergeSort(nums, 0, numsSize - 1);
	}

private:
	std::vector<int> helper;

	void mergeSort(std::vector<int>& nums, int low, int high)
	{
		if (low < high)
		{
			auto middle = (low + high) / 2;
			mergeSort(nums, low, middle);
			mergeSort(nums, middle + 1, high);
			merge(nums, low, middle, high);
		}
	}

	void merge(std::vector<int>& nums, int low, int middle, int high)
	{
		for (auto i = low; i <= high; ++i)
		{
			helper[i] = nums[i];
		}
		auto hLeft = low;
		auto hRight = middle + 1;
		auto current = low;

		while (hLeft <= middle && hRight <= high)
		{
			if (helper[hLeft] <= helper[hRight])
			{
				nums[current++] = helper[hLeft++];
			}
			else
			{
				nums[current++] = helper[hRight++];
			}
		}
		auto remaining = middle - hLeft;
		for (auto i = 0; i <= remaining; ++i)
		{
			nums[current + i] = helper[hLeft + i];
		}
	}
};

int main()
{
	auto input = std::string();
	std::getline(std::cin, input);

	auto numbers = std::vector<int>();
	auto numberStream = std::istringstream(input);
	for (int number; numberStream >> number;)
	{
		numbers.push_back(number);
	}

	Sorter().sortArray(numbers);

	for (auto number : numbers)
	{
		std::cout << number << ' ';
	}
	return 0;
}
