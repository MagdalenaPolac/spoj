#include<iostream>

struct Point 
{
    int x = 0;
    int y = 0;

    Point() = default;
    Point(int _x, int _y) : x(_x), y(_y) {}

    bool operator==(const Point& rhs) 
    {
        return (x == rhs.x) && (y == rhs.y);
    }
};


bool isOnDiagonal(const Point& centerPoint, const Point& testPoint1, const Point& testPoint2)
{
    if (((testPoint1.x - centerPoint.x == testPoint1.y - centerPoint.y)
        && (testPoint2.x - centerPoint.x == testPoint2.y - centerPoint.y))
        || ((testPoint1.x - centerPoint.x == -(testPoint1.y - centerPoint.y))
        && (testPoint2.x - centerPoint.x == -(testPoint2.y - centerPoint.y)))) 
    {
        auto test1 = testPoint1.x - centerPoint.x;
        auto test2 = testPoint2.x - centerPoint.x;
        if (test1 == 0 
            || test2 == 0
            || (test1 > 0 && test2 < 0)
            || (test1 < 0 && test2 > 0))
        {
            return true;
        }
    }
    return false;
}

int main() 
{
    auto n = 0; //num of rows <= 100
    auto m = 0; //num of cols <= 100
    auto k = 0; //num of test cases <= 10

    std::cin >> n >> m;
    std::cin >> k;

    for (auto i = 0; i < k; ++i)
    {
        //get data
        auto temp_x = 0;
        auto temp_y = 0;

        std::cin >> temp_y >> temp_x;
        auto mousePoint = Point(temp_x, temp_y);

        std::cin >> temp_y >> temp_x;
        auto cat1Point = Point(temp_x, temp_y);

        std::cin >> temp_y >> temp_x;
        auto cat2Point = Point(temp_x, temp_y);

        //test data
        auto canEscape = false;
        if (mousePoint == cat1Point || mousePoint == cat2Point)
        {
            canEscape = false;
        }
        else 
        {
            auto mouseOnDiagonal = isOnDiagonal(mousePoint, cat1Point, cat2Point);
            canEscape = !mouseOnDiagonal;
        }
        (canEscape) ? std::cout << "YES" : std::cout << "NO";
        std::cout << std::endl;
    }
    return 0;
}
