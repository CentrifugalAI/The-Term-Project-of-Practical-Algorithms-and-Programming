#include <iostream>
#define MAXN 100000

enum _relations
{
    same = 0,   // 同类
    eating = 1, // 捕食
    eaten = 2,  // 被捕食
};

// 每个数字和一个种类应该是一种一一映射的关系
int fa[MAXN];        // 用来存放每个节点的父亲节点
_relations re[MAXN]; // 用来存放每个节点和它的父亲节点的关系

int find(int a) // 查找
{
    if (a != fa[a])
    {
        fa[a] = find(fa[a]);                         // 将自己的父亲节点往上延展，实现路径压缩
        re[a] = _relations((re[a] + re[fa[a]]) % 3); // 将自己和父亲节点的关系在延展后响应地进行更新
        return fa[a];
    }
    else
        return fa[a]; // 如果自己就是祖先节点的话则直接返回
}

int main()
{
    int n, m, a, b, judge, ans = 0;
    std::cin >> n >> m; // n是动物的种类数，m是论断的条数
    for (int i = 1; i <= n; ++i)
    {
        fa[i] = i, re[i] = same; // 初始状态下,所有节点都设置为祖先节点，自己和祖先节点的关系设置为同类
    }
    for (int i = 1; i <= m; ++i) // 逐条读取信息
    {
        std::cin >> judge >> a >> b;
        if ((a > n || b > n) || (judge == 2 && a == b)) // 分别对应假话条件的第一句和第二句
        {
            ans++;
            continue;
        }
        if (judge == 1)
        {
            int fa1 = find(a), fa2 = find(b);
            if (fa1 == fa2 && re[a] != re[b]) // 如果两个动物种类相同并且权值不用
            {
                ans++; // 这是一句假话
                continue;
            }
            else if (fa1 != fa2) // 如果发现两个动物的祖先不同
            {
                fa[fa1] = fa2; // 合并，将第二个动物的祖先设置为第一个动物的祖先的父亲
                re[fa1] = _relations((3 - re[a] + re[b]) % 3);
            }
        }
        if (judge == 2)
        {
            int fa1 = find(a), fa2 = find(b);
            if (fa1 == fa2)
            {
                if (_relations((re[a] - re[b]) % 3) != eating)
                {
                    ans++;
                    continue;
                }
            }
            else
            {
                fa[fa1] = fa2;
                re[fa1] = _relations((3 - re[a] + re[b] + 1) % 3); //合并
            }
        }
    }
}