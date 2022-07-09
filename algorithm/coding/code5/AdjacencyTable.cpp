#include <vector>
#include <list>

typedef struct Data
{
    /* data */
};

typedef struct Vertex
{
    Data data_field;                    // 数据域，用来描述顶点的相关信息
    long long int index;                // 索引号，用来表示一个顶点位于顶点数组的什么位置，顶点序号从1开始计数
    std::list<long long int> neighbors; // 和其它顶点的关系，该向量的长度应该等于和自己有关系顶点的个数
};

class Table
{
    std::vector<Vertex> vertexs;
    long long int vertexCnt;
    void addVertex(const std::list<long long int> neighbors, const Data &data_field);
    void deleteVertex(long long int index);
};

void Table::addVertex(const std::list<long long int> neighbors, const Data &data_field)
{
    Vertex temp{data_field, ++this->vertexCnt, neighbors};
    this->vertexs.push_back(temp); // 将新的节点加入数组中
    for (auto ver : neighbors)     // 遍历新加入节点的邻居列表
    {
        this->vertexs[ver].neighbors.push_back(temp.index); // 为新加入节点的邻居增添新加入节点的索引号
    }
}

void Table::deleteVertex(long long int index) // 参数是被删除节点的索引号
{
    for (auto ver : vertexs[index].neighbors) // 遍历顶点的所有邻居
    {
        for (std::list<long long int>::iterator it = this->vertexs[ver].neighbors.begin(); it != vertexs[ver].neighbors.end(); it++)
        {
            if (*it == index) // 找到链表中索引和要删除节点的邻居相同的索引
            {
                this->vertexs[ver].neighbors.erase(it); // 在链表中将这个索引删除
                break;
            }
        }
    }
    // 待上面的步骤完成以后，删除这个索引对应的节点
    this->vertexs.erase(this->vertexs.begin() + index);
}