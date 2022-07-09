#include <algorithm>
#include <iostream>
int suma[100][100];
int sumb[100][100];

int main()
{
    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            std::cin >> suma[i][j];                                                         // 输入矩阵
            sumb[i][j] = sumb[i][j - 1] + sumb[i - 1][j] - sumb[i - 1][j - 1] + suma[i][j]; // 求前缀和
        }
    }

    int ans = 1;

    int k = 2;
    while (k <= std::min(n, m)) // 判断条件
    {
        for (int i = k; i <= n; i++)
        {
            for (int j = k; j <= m; j++)
            {
                if (sumb[i][j] - sumb[i - k][j] - sumb[i][j - k] + sumb[i - k][j - k] == k * k) // 如果这个小矩阵的和为k*k，即每一个元素都是 1
                {
                    ans = std::max(ans, k); // 统计答案
                }
            }
        }
        k++;
    }
    std::cout << ans << std::endl;
    return 0;
}