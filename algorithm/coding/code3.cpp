#include <bits/stdc++.h>
#define ull unsigned long long
ull base = 131;
ull hashs[100001];
char str[10001]; // 最大支持10001个字符的字符串
ull hashe(char str[])
{
    int len = strlen(str);
    ull result = 0;
    for (int i = 0; i < len; ++i)
    {
        result = (result * base + (ull)(str[i])) % 2021201613; // 学号当模数（bushi
    }
    return result;
}
int main()
{
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> str;
        hashs[i] = hashe(str);
    }
    std::sort(hashs + 1, hashs + n + 1);
    ull result = 1;
    for (int i = 1; i < n; i++)
    {
        if (hashs[i] != hashs[i + 1])
            result++;
    }
    std::cout << result;
    return 0;
}