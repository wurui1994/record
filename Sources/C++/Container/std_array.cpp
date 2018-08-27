#include <iostream>
#include <array>
#include <cstdlib> // std::rand, std::srand
#include <ctime> // std::time
#include <algorithm>

template<typename T, size_t N>
void PrintIntArray(std::array<T, N>& arr, char* pre)
{
    std::cout << pre;
    for (auto ele:arr)
    {
        std::cout << ele << " ";
    }
    std::cout << std::endl;
}

int RandomNumber()
{
    return (std::rand() % 100);
}

void ArrayExample1()
{
    std::array<int, 10> foo1;

    // 随机生成一个数组
    std::srand(unsigned(std::time(0)));
    std::generate(foo1.begin(), foo1.end(), RandomNumber);
    PrintIntArray(foo1, "随机生成的foo1：");

    // 排序
    std::sort(foo1.begin(), foo1.end());
    PrintIntArray(foo1, "排序后的foo1：");

    // 反转
    std::reverse(foo1.begin(), foo1.end());
    PrintIntArray(foo1, "反转后的foo1：");

    // 值返回
    std::cout << "大小：" << foo1.size() << std::endl;
    std::cout << "最大值：" << foo1.max_size() << std::endl;

    // 是否为空
    std::array<int, 0> foo2;
    std::cout << "foo1 是否为空：" << std::boolalpha
              << foo1.empty() << std::endl;
    std::cout << "foo2 是否为空：" << std::boolalpha
              << foo2.empty() << std::endl;

    // 操作第一个元素（即下标为 0 的元素）
    foo1[0] = 123;
    std::cout << "修改后的第一个元素为：" << foo1.at(0)
              << std::endl;

    // 用 0 填充
    foo1.fill(0);
    PrintIntArray(foo1, "用 0 填充后的foo1：");

    // front、back 返回的分别是对第一个或最后一个元素的引用
    foo1.front() = 7;
    foo1.back() = 13;
    PrintIntArray(foo1, "修改第一个及最后一个元素后的foo1：");
}


int main()
{
    ArrayExample1();
    return 0;
}