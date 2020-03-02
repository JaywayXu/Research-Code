#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>
#include <time.h>
using namespace std;

class Genetic {
private:
    int m_Num;                                // 皇后数量
    bool m_IsSuccess;                         // 是否成功找到最优解
    vector<int>m_optimalSolution;             // 最优解.
    vector<vector<int> >m_population;          // 种群
    vector<double>m_adaptive;                 // 种群的适应值(1/冲突数)。
    vector<double>m_AdaptValue;               // 累积的适应值(定位哪一个被选中的)
    

public:
    Genetic(int numOfQueens, int initialGroupNum);
    double CalcuAdaptive(vector<int> &state);         // 计算适应值（互不相攻击的皇后对数）
    void SetPopulation();
    void Choose();                                    // 选择
    void GeneticCrossover();                          // 杂交
    void GeneticMutate();                             // 变异
    void GeneticCalculation();
    void Print();                                     // 打印最优解
};

Genetic::Genetic(int numOfQueens, int initialGroupNum) {
    m_adaptive.resize(initialGroupNum, 0);
    m_AdaptValue.resize(initialGroupNum, 0);
    m_Num = numOfQueens;
    m_IsSuccess = true;
    SetPopulation();
}

void Genetic::SetPopulation() {
    m_population.clear();
    vector<int> tmpState(m_Num, 0);
    for (int i = 0; i < m_adaptive.size(); ++i) {
        for (int j = 0; j < m_Num; ++j)       // 初始化
            tmpState[j] = rand() % m_Num;
        m_population.push_back(tmpState);
        m_adaptive[i] = CalcuAdaptive(tmpState);
    }
}

double Genetic::CalcuAdaptive(vector<int> &state) {
    int conflict = 0;
    for (int i = 0; i < m_Num; ++i) {
        for (int j = i + 1; j < m_Num; ++j) {
            //如果对角线方向互相攻击，或者垂直方向互相攻击
            if (state[i] == state[j] || abs(state[i] - state[j]) == j - i)
                conflict++;
        }
    }
    if (conflict == 0) {                     // 找到最优解
        m_IsSuccess = false;
        m_optimalSolution = state;             //保存当前的状态    
    }
    return 1.0 / conflict;
}

//自然选择（大体思路是轮盘赌选择）
void Genetic::Choose() {            
    vector<vector<int>> NewPopulation;    //创建一个新的空种群NewPopulation
    m_AdaptValue[0] = m_adaptive[0];
    for (int i = 1; i < m_AdaptValue.size(); i++)
        m_AdaptValue[i] = m_AdaptValue[i - 1] + m_adaptive[i];
    double totalAdaptive = m_AdaptValue[m_AdaptValue.size() - 1];
    //避免陷入局部最优解(不直接选择适应值最高的两个进行杂交)
    for (int i = 0; i < m_population.size(); i++) {

        //比例缩放的轮盘赌
        int magnifyTotalAdaptive = totalAdaptive * 100000;    //实数->整数(放大)
        int random = (rand()*rand()) % magnifyTotalAdaptive;//转动轮盘
        double select = (double)random / 100000;            //按相同比例缩小
        
        //int select = rand()*rand() % ((int)totalAdaptive);
        vector<double>::iterator indexi;
        //二分查找: 在m_AdaptValue中查找适应值与select最接近的个体的下标
        indexi = lower_bound(m_AdaptValue.begin(), m_AdaptValue.end(), select);
        int indexj = indexi - m_AdaptValue.begin();
        //加入新的种群中
        NewPopulation.push_back(m_population[indexj]);
    }
    // double min = 100;
    // double max = 0;
    // for (int i=0; i<m_adaptive.size(); ++i) {
    //     double x = double(m_adaptive[i])/totalAdaptive*100;
    //     if (x > max)
    //         max = x;
    //     if (x < min)
    //         min = x;
    // } cout  << max << ' ' << min<< endl;
    // int x; cin>>x;

    // 更新种群
    m_population.clear();
    m_population = NewPopulation;
}

void Genetic::GeneticCrossover() {    //杂交==>交换基因片段(皇后位置进行交换)
    int first = 0;
    int row1;
    for (int i = 0; i < m_population.size(); i++) {
        if (rand() % 2) {
            ++first;
            if (first % 2 == 0) {
                int crossPoint = rand() % (m_Num - 1);
                for (int j = crossPoint; j < m_Num; j++)swap(m_population[row1][j], m_population[i][j]);  //值交换
            }
            else row1 = i;
        }
    }
}

void Genetic::Print() {
    for (int i = 0; i < m_optimalSolution.size(); ++i) {
        for (int j = 0; j < m_optimalSolution.size(); ++j) {
            if (j == m_optimalSolution[i]) cout << "Q ";
            else cout << ". ";
        }cout << '\n';
    }cout << '\n';
}

//随机突变=> 随机改变某个个体的某个基因(随机改变某个地图中的某个皇后的位置)
void Genetic::GeneticMutate() {        
    int mutateSpot = 0;
    for (int i = 0; i < m_population.size(); ++i) {
        if (rand() % 2 == 0) {
            mutateSpot = rand() % m_Num;
            m_population[i][mutateSpot] = rand() % m_Num;
        }
        //m_adaptive[i] = CalcuAdaptive(m_population[i]);  // 更新适应值
    }
}

void Genetic::GeneticCalculation() {
    clock_t start, finish;
    start = clock();
    int count = 0;
    while (m_IsSuccess) {
        count++;
        // 自然选择
        Choose();
        // 杂交
        GeneticCrossover();
        // 变异
        GeneticMutate();

        for (int i = 0; i < m_population.size(); ++i) {
            m_adaptive[i] = CalcuAdaptive(m_population[i]);  // 更新适应值
        }
    }
    cout<<count<<endl;
    //打印最优解
    //if (m_Num<25) Print();
    Print();
    finish = clock();
    cout << "遗传算法求解时间: " << finish - start << "ms" << endl;
}

int main() {
srand((unsigned)time(NULL));

    while (1) {
    int numOfQueen;
    cout << "请输入皇后数目: ";
    cin >> numOfQueen;
    cout << "【遗传算法求解】" << endl;
    Genetic Q(numOfQueen, 100);
    Q.GeneticCalculation();
    system("pause");}
}
