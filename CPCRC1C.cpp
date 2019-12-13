#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

//result[0] - the least significant digit
void convertToVector(int input, std::vector<int>& result)
{
	if (input == 0)
	{
		result.emplace_back(0);
	}
	while (input)
	{
		result.emplace_back(input % 10);
		input /= 10;
	}
}

class DP 
{
public:
	DP(int _maxCount)
		: _maxCount(_maxCount) 
	{
		_s = std::vector<long long>(_maxCount, -1);
		_s[0] = 45ll; //0+1+2+...+9

		_sigma = std::vector<long long>(_maxCount, -1);
		_sigma[0] = 45ll;

		for (auto i = 0, temp = 0; i < 10; ++i) 
		{
			temp += i;
			_val[i] = temp;
		}
		initSigmaS(_maxCount - 1);
	}

	long long getSum(const std::vector<int>& number) 
	{

		auto iMax = static_cast<int>(number.size());
		auto sum = 0ll;

		//i = 0
		if (number[0] != 0) 
		{
			sum += _val[number[0] - 1];

			for (auto j = 1; j < iMax; ++j)
			{
				sum += number[0] * number[j];
			}
		}

		for (auto j = 0; j < iMax; ++j)
		{
			sum += number[j];
		}

		//i > 0
		for (auto i = 1; i < iMax; ++i) 
		{
			sum += number[i] * _sigma[i - 1];
			for (auto j = 0; j <= number[i] - 1; ++j)
			{
				sum += pow(10, i)*j;
			}
			for (auto j = i + 1; j < iMax; ++j)
			{
				sum += number[i] * pow(10, i)*number[j];
			}
		}
		return sum;
	}

private:
	std::vector<long long> _s;
	std::vector<long long> _sigma;
	int _val[10];
	int _maxCount;

	//s[0] - sum of digits for numbers from 0 to 9
	//s[1] - sum of digits for numbers from 10 to 99
	//s[2] - sum of digits for numbers from 100 to 999
	//etc.
	//sigma[0] - sum of digits for numbers from 0 to 9
	//sigma[1] - sum of digits for numbers from 0 to 99
	//sigma[2] - sum of digits for numbers from 0 to 999
	//etc.
	void initSigmaS(int up) 
	{
		//s[1],....
		for (auto i = 1; i <= up; ++i) 
		{
			_s[i] = 45 * pow(10, i);
			for (auto j = 0; j <= i - 1; ++j)
			{
				_s[i] += 9 * _s[j];
			}
		}

		//sigma[1],...
		for (auto i = 1; i <= up; ++i) 
		{
			_sigma[i] = 0;
			for (auto j = 0; j <= i; ++j)
			{
				_sigma[i] += _s[j];
			}
		}
	}
};

int main() 
{

	DP dp(10);
	while (true) 
	{
		auto a = -1, b = -1;
		std::cin >> a >> b;
		if (a == -1 && b == -1) break;

		auto vecA = std::vector<int>();
		auto vecB = std::vector<int>();
		if (a == 0)
		{
			vecA.emplace_back(0);
		}
		else
		{
			convertToVector(a - 1, vecA);
		}
		convertToVector(b, vecB);

		auto sumB = dp.getSum(vecB);
		auto sumA = dp.getSum(vecA);
		std::cout << sumB - sumA << std::endl;
	}
	return 0;
}
