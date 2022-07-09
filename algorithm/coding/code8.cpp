#include <vector>
const int MAXN = 10000;

typedef struct Rule
{
    int index;
    int word = 0;              // 词数
    int inDeg = 0;             // 入度
    int outDeg = 0;            // 出度
    std::vector<Rule> inRule;  // 前向节点数组
    std::vector<Rule> outRule; // 后向节点数组
};

Rule rules[MAXN]; // 定义节点数组

// 预处理：索引设置
void pre(Rule *rules)
{
    for (int i = 0; i <= MAXN; ++i)
    {
        (rules + i)->index = i;
    }
}

// 该函数用于遍历整个 DAG图,获取一个规则的单词数
void renewWord(Rule &arule)
{
    for (auto i : arule.outRule)
    {
        if (!i.word) // 如果一个规则的词数为0，说明这个规则还没有被遍历过
        {
            renewWord(rules[i.index]);
            arule.word += rules[i.index].word;
        }
        else // 否则说明这个规则已经遍历过
        {
            arule.word += rules[i.index].word; // 如果已经遍历过则直接从记忆化数组中取
        }
    }
}
