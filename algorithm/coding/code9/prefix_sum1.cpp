#include <iostream>
int N, A[100000], B[100000];
int main()
{
    std::cin >> N;
    for (int i = 0; i < N; i++)
    {
        std::cin >> A[i];
    }
    B[0] = A[0]; // 前缀和数组的第一项和原数组的第一项是相等的。
    for (int i = 1; i < N; i++)
    {
        B[i] = B[i - 1] + A[i]; // 前缀和数组的第 i 项 = 原数组的 0 到 i-1 项的和 + 原数组的第 i 项。
    }
    for (int i = 0; i < N; i++)
    {
        std::cout << B[i] << " ";
    }
    return 0;
}