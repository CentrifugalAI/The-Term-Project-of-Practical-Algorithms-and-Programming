#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int MaxV = 100;

/*定义队列*/
typedef struct Queue
{
    int *Data;
    int Front, Rear;
    int MaxSize;
} * queue;

/*定义边*/
typedef struct Edge
{
    int v1, v2;
    int Weight;
} * edge;

/*定义邻接结点*/
struct AdjV
{
    int AdjVnum;
    int Weight;
    AdjV *Next;
};

/*定义邻接表头*/
typedef struct Ver
{
    AdjV *edgeFirst;
    // bool tag;	//标记是否被访问, 该题不需要此标记, 入度为0后, 邻接表就不会在访问它了
    int Indegree; //该结点的入度数
} AdjList[MaxV];

/*定义图*/
typedef struct Graph
{
    int Nv, Ne;
    AdjList L;
} * graph;

/*创建队列并初始化*/
queue Createqueue(int MaxSize) //给定队列最大长度
{
    queue Q = (queue)calloc(1, sizeof(Queue));
    Q->Data = (int *)calloc(MaxSize, sizeof(int));
    Q->MaxSize = MaxSize;
    return Q;
}

/*入队操作*/
void AddQ(queue Q, int x)
{
    Q->Rear = (Q->Rear + 1) % Q->MaxSize;
    Q->Data[Q->Rear] = x;
}

/*出队操作*/
int DeleteQ(queue Q)
{
    Q->Front = (Q->Front + 1) % Q->MaxSize;
    return Q->Data[Q->Front];
}

/*
队列空: Q->Front == Q->Rear;
队列满: (Q->Rear + 1) % Q->MaxSize == Q->Front;
*/

/*创造有Nv各结点的无边图*/
graph CreateGraph(int Nv)
{
    graph G = (graph)calloc(1, sizeof(Graph));
    G->Nv = Nv;
    return G;
}

/*给图插入边*/
void Insertedge(graph G, edge E)
{
    AdjV *A = (AdjV *)malloc(sizeof(AdjV));
    A->AdjVnum = E->v2;
    A->Next = G->L[E->v1].edgeFirst;
    G->L[E->v1].edgeFirst = A;
}

/*创建图表*/
graph BuildGraph()
{
    int Nv;
    cin >> Nv;
    graph G = CreateGraph(Nv);
    cin >> G->Ne;
    edge E = (edge)malloc(sizeof(Edge));
    for (int i = 0; i < G->Ne; i++)
    {
        cin >> E->v1 >> E->v2;
        Insertedge(G, E);
        G->L[E->v2].Indegree++; //计算入度
    }
    free(E);
    return G;
}

/*拓扑排序*/
bool TopSort(graph G, int TopOrder[])
{
    queue Q = Createqueue(G->Nv);
    for (int i = 0; i < G->Nv; i++)
        if (G->L[i].Indegree == 0)
            AddQ(Q, i);

    int cnt = 0;
    AdjV *A;
    while (Q->Front != Q->Rear) //如果队列非空
    {
        int v = DeleteQ(Q);
        TopOrder[cnt++] = v;
        A = G->L[v].edgeFirst;
        while (A)
        {
            if (--G->L[A->AdjVnum].Indegree == 0) //如果入度减1为0
                AddQ(Q, A->AdjVnum);
            A = A->Next;
        }
    }
    /*如果队列空以后*/
    free(Q->Data);
    free(Q);
    if (cnt != G->Nv)
        return false; //说明有回路, 有回路就会有一些点入度不可能降为0
    else
        return true;
}

/*删除图, 释放图占用的储存空间*/
void DeleteGraph(graph G)
{
    AdjV *A;
    for (int i = 0; i < G->Nv; i++)
        while (G->L[i].edgeFirst)
        {
            A = G->L[i].edgeFirst;
            G->L[i].edgeFirst = A->Next;
            free(A);
        }
    free(G);
}

int main()
{
    int TopOrder[MaxV]; //储存拓扑排序
    graph G = BuildGraph();
    if (!TopSort(G, TopOrder))
        cout << "have circle" << endl;
    else
    {
        cout << "the result is " << endl;
        for (int i = 0; i < G->Nv; i++)
            cout << TopOrder[i] << " ";
        cout << endl;
    }
    DeleteGraph(G);

    system("pause");
    return 0;
}
