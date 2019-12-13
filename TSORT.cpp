#include <iostream>
#include <vector>

class Sorter 
{
public:
	static void quickSort(std::vector<int>& nums, int left, int right)
	{
		auto index = partition(nums, left, right);
		if (left < index - 1)
		{
			quickSort(nums, left, index - 1);
		}
		if (index < right)
		{
			quickSort(nums, index, right);
		}
	}

private:
	static int partition(std::vector<int>& nums, int left, int right)
	{
		auto pivotIdx = (left + right) / 2;
		auto pivot = nums[pivotIdx];
		while (left <= right)
		{
			while (nums[left] < pivot) ++left;
			while (nums[right] > pivot) --right;
			if (left <= right)
			{
				std::swap(nums[left], nums[right]);
				++left;
				--right;
			}
		}
		return left;
	}
};

int main()
{
	auto numberCount = 0;
	std::cin >> numberCount;
	
	auto numbers = std::vector<int>(numberCount);
	for (auto i = 0; i < numberCount; ++i)
	{
		int number;
		std::cin >> number;
		numbers[i] = number;
	}
	
	Sorter::quickSort(numbers, 0, numberCount - 1);
	
	for (const auto& number : numbers)
	{
		std::cout << number << std::endl;
	}
	return 0;
}
