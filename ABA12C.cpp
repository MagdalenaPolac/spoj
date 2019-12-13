#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

class DP
{
public:
    DP(const std::vector<int>& prices, int maxPrice)
        : _prices(prices),
          _limitPrice(maxPrice + 1)
    {
        _values = std::vector<int>(prices.size(), -1);
        _values[0] = prices[0];
        _values[1] = prices[1];
    }

    int getBestPrice(int n) 
    {
        auto currentPrice = _values[n];
        if (currentPrice == -1) 
        {
            currentPrice = _limitPrice;
            for (auto j = 1; j <= n; ++j)
            {
                if (_prices[j] != -1)
                {
                    currentPrice = std::min(currentPrice, _prices[j] + getBestPrice(n - j));
                }
            }
        }
        _values[n] = currentPrice;
        return currentPrice;
    }

private:
    int _limitPrice;
    std::vector<int> _values;
    const std::vector<int>& _prices;
};

int main() 
{
    auto testCount = 0;
    std::cin >> testCount;

    for (auto testIdx = 0; testIdx < testCount; ++testIdx) 
    {
        auto friendCount = 0;
        auto appleCount = 0;
        std::cin >> friendCount >> appleCount;

        auto prices = std::vector<int>();
        prices.reserve(appleCount + 1);
        prices.emplace_back(0);

        for (auto applesInPacket = 0; applesInPacket < appleCount; ++applesInPacket) 
        {
            auto packetPrice = -1;
            std::cin >> packetPrice;
            prices.push_back(packetPrice);
        }

        const auto maxAcceptedPrice = 1000;
        auto dp = DP(prices, maxAcceptedPrice);
        auto price = dp.getBestPrice(appleCount);
        if (price > maxAcceptedPrice)  price = -1;

        std::cout << price << std::endl;
    }
    return 0;
}
