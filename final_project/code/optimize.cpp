#include <iostream>
#include <string.h>

const int n;          // 定义转换矩阵的规模
const double rate;    // 定义衰减率
const int unit_times; // 定义一个迭代单元中的迭代次数

struct data
{
    // datafiled
    double getWeight(); // 该函数用于根据页面的具体内容和链接的重要程度确定一个状态的权重
};

struct state
{
    long long int start_state[100] = {1}; // 假设从第一个网站开始访问，事实上，这并不会影响结果
    data datafield[100];                  // 用于辅助分析的数据(取决于每个网页对的权重)
    state()
    {
        memset(start_state, 0, sizeof(start_state));
    }
    void multiply(transfer_matrix &a);
    void unitChange(int times_of_iteration);  // 单元迭代
    void changeState(int times_of_iteration); // 完全迭代
    transfer_matrix get_dumping_matrix(transfer_matrix &temp);
};

struct transfer_matrix
{
    long long int x[100][100];
    transfer_matrix()
    {
        memset(x, 0, sizeof(x)); // 在初始化矩阵时直接进行清空
        for (int i = 1; i <= n; ++i)
        {
            this->x[i][i] = 1; // 转移矩阵初始化为单位矩阵
        }
    }
    void multiply(transfer_matrix &a);
    void pow(long long int m);
};

transfer_matrix start_matrix; // 定义转移矩阵

double data::getWeight()
{
    // 该函数用于根据页面的具体内容和链接的重要程度确定一个状态的权重
}

void transfer_matrix::multiply(transfer_matrix &a) // 定义矩阵乘法
{
    // transfer_matrix b;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            for (int k = 1; k <= n; ++k)
            {
                this->x[i][j] += a.x[i][k] * this->x[k][j];
            }
        }
    }
    // return b;
}

void transfer_matrix::pow(long long int m) // 计算矩阵a的m次方
{
    // for (int i = 1; i <= n; ++i)
    // {
    //     this->x[i][i] = 1; //单位矩阵
    // }
    transfer_matrix temp = *this;
    while (m > 0)
    {
        if (m & 1)
        {
            this->multiply(temp);
        }
        temp.multiply(temp);
        m >>= 1;
    }
    // return result;
}
void state::multiply(transfer_matrix &a) // 定义单列向量的乘法
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            for (int k = 1; k <= n; ++k)
            {
                this->start_state[i] += this->start_state[k] * a.x[k][j];
            }
        }
    }
}

transfer_matrix state::get_dumping_matrix(transfer_matrix &temp) // 获得衰减矩阵
{
    transfer_matrix dumping_matrix;
    memset(dumping_matrix.x, 0, sizeof(dumping_matrix.x));
    for (int i = 1; i <= n; ++i)
    {
        dumping_matrix.x[i][i] = this->start_state[i];
        dumping_matrix.x[i][i] *= datafield[i].getWeight();
        for (int j = 1; j <= n; j++)
        {
            dumping_matrix.x[i][i] *= rate * temp.x[i][j];
        }
    }
    return dumping_matrix;
}

void state::unitChange(int times_of_iteration)
{
    start_matrix.pow(times_of_iteration);                              // 先将矩阵进行迭代
    transfer_matrix dumping_matrix = get_dumping_matrix(start_matrix); // 获取衰减矩阵
    start_matrix.multiply(dumping_matrix);                             // 衰减处理
    this->multiply(start_matrix);                                      // 转换处理
}

void state::changeState(int times_of_iteration) // 用于切分迭代单元的函数
{
    if (times_of_iteration > unit_times) // 迭代次数超过包含一个以上的迭代单元
    {
        // 进行一次单元迭代
        unitChange(unit_times);
        changeState(times_of_iteration - unit_times); // 递归
    }
    else // 迭代次数小于一个以上的迭代单元则直接迭代
    {
        start_matrix.pow(times_of_iteration); // 先将矩阵进行迭代
        this->multiply(start_matrix);
    }
}