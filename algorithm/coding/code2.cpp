const int SIZE = 1000000;
const int M = 999997;

struct HashTable
{
    struct Node
    {
        int next, value, key;
    } data[SIZE]; // 定义数据域：包括键、值以及

    int head[M], index; // 链表的头指针

    int f(int key) { return key % M; } // 该函数的作用在于获取键所对应的值应该在哪条链上

    int get(int key) // 获取值
    {
        for (int p = head[f(key)]; p; p = data[p].next) // 本循环只会在找到对应链的末尾仍然没有找到对应值的情况下才会主动终止
            if (data[p].key == key)
                return data[p].value;
        return -1;
    }

    int modify(int key, int value) // 修改键对应的值，思路类似于 get 函数
    {
        for (int p = head[f(key)]; p; p = data[p].next)
            if (data[p].key == key)
                return data[p].value = value;
    }

    int add(int key, int value) // 将一个键值对加入到哈希表中
    {
        if (get(key) != -1) // 如果这个键已经存在了，直接返回-1
            return -1;
        data[++index] = (Node){head[f(key)], value, key}; // 将结构体数组中进行相应的更新
        head[f(key)] = index;                             // index事实上是一个节点在结构体数组中的编号（索引）
        return value;
    }
};