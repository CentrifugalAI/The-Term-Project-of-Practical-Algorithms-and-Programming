#include <vector>
#include <iostream>

typedef struct Data
{
    /* data */
};

typedef struct Vertex
{
    Data data_field;             // 数据域，用来描述顶点的相关信息
    long long int index;         // 索引号，用来表示一个顶点位于顶点数组的什么位置，顶点序号从1开始计数
    std::vector<bool> relations; // 和其它顶点的关系，该向量的长度应该等于顶点数组向量的长度
};

class Martrix
{
    std::vector<Vertex> vertexs; // 顶点数组
    long long int vertexCnt;
    void addVertex(const Data &data_field, std::vector<bool> arelations);
    void deleteVertex(long long int aindex);
};

void Martrix::addVertex(const Data &data_field, std::vector<bool> arelations)
{
    Vertex temp{data_field, ++this->vertexCnt, arelations};
    this->vertexs.push_back(temp); // 将新的顶点加入顶点数组中
    for (auto ver : this->vertexs)
    {
        ver.relations.push_back(arelations[ver.index]); // 遍历顶点数组，更新关系列表
    }
}

void Martrix::deleteVertex(long long int aindex)
{
    for (auto ver : this->vertexs)
    {
        ver.relations.erase(ver.relations.begin() + aindex); // 遍历顶点数组，更新关系列表
    }
    this->vertexs.erase(this->vertexs.begin() + aindex);
}