#include <iostream>
#include <string.h>
#include <vector>
#include <cstdio>
#include <map>
using namespace std;
#define MAX 100
#define N 20
#define INFINITE 2147483647

//len用来记录总路程，rec用于记录走过点的顺序，res用于记录可行的结果
int len = 1000000, rec[N*N], res[N*N];

//times用来记录每条边被走过的次数，n_v和n_e分别是点数和边数，Final_Len用于记录最终路线长度
int times[N][N], n_v = 9, n_e = 9, Final_Len = 10000;

//景点名称
string scenic_area[N] = {"南普陀", "芙蓉湖", "情人谷", "芙蓉隧道", "人类博物馆", "上弦场", "演武场", "胡里山炮台", "曾厝垵"};

//  v:图顶点保存的值; w:边的权值; max:最大权值，表示无穷,用来判断图中两点是否有关系; flag == true代表有向图，否则为无向图
template <class v, class w, w max = INT_MAX, bool flag = false>
class graph {
    private:
        vector<v> _verPoint;            //顶点集合
        map<v, int> _indexMap;			//顶点与下标的映射
        
        int _getPosPoint(const v &point) {
            if (_indexMap.find(point) != _indexMap.end())
                return _indexMap[point];
            else {
                cout << point << " not found" << endl;
                return -1;
            }
        }

    public:
        //定义访问数组记录是否访问过
        //bool visited[MAX] = {false};
        //根据用户输入的顶点集合来开辟邻接矩阵

        vector<vector<w> > _matrix;		//邻接矩阵，存每条边的权值
        graph(const vector<v> &src) {
            _verPoint.resize(src.size());
            for (int i = 0; i < src.size(); i++) {
                _verPoint[i] = src[i];
                _indexMap[src[i]] = i;
            }

            //初始化邻接矩阵
            _matrix.resize(src.size());
            for (int i = 0; i < src.size(); i++)
                _matrix[i].resize(src.size(), max);
        }

        //添加边的关系，输入两个点以及这两个点的连线边权值
        //用来初始化图顶点之间的关系
        void AddEdge(const v &pointA, const v &pointB, const w &weight) {
            //获取这个顶点在邻接矩阵中的下标
            int posA = _getPosPoint(pointA);
            int posB = _getPosPoint(pointB);
            _matrix[posA][posB] = weight;
            if (!flag)      //若为无向图，使邻接矩阵对称即可
                _matrix[posB][posA] = weight;
        }

        //判断是否走完了选中的全部目标，若所有目标点均已访问过，则返回true，否则返回false
        bool judge(int des[], int n) { //des表示需要经过的点集，n表示des数组的长度
            bool *flags = new bool[n_v];
            memset(flags, false, n_v); //初始化
            //标记已经走过的点
            for (int i = 0; rec[i] != -1; i++) {
                flags[rec[i]] = true;
            }
            //遍历所有选中的点是否走过，若存在未走过的点，返回false
            for (int i = 0; i < n; i++) {
                if (flags[des[i]] == false)
                    return false;
            }
            return true;
        }

        //寻路函数，列出所有可能的路线，并找出最短路线
        void find_way(int des[], int n, int x, int count = 0) {
            //des数组存的选中的目标点，n是目标点个数，x为起点，count是已经走过点的数量
            if (judge(des, n)) { //若找到一条路
                int sum = 0; //记录结果总长度
                int cnt = 0;
                //记录最终路程总长度与经过的点的数量
                for (int i = 1; rec[i] != -1; i++) {
                    sum += _matrix[rec[i-1]][rec[i]];
                    cnt++;
                }
                //记录最终经过的总结点数
                if (cnt < Final_Len)
                    Final_Len = cnt;

                if (sum < len) {
                    cout << "已找到一条路：";
                    len = sum;
                    for (int i = 0; rec[i] != -1; i++) {
                        res[i] = rec[i]; //存储当前的最优解
                        //输出当前的路径
                        cout << scenic_area[res[i]];
                        if (rec[i+1] != -1) {
                            cout << "->";
                        } else {
                            cout << endl;
                        }
                    }
                    cout << "这条路的长度为：" << len << "m" << endl;
                    cout << "-----------------------------------------------" << endl;
                }
                return;
            }

            //寻找可以走的路径
            for (int y = 0; y < n_v; y++) {
                //若该点可以走且经过次数小于2，则可以走
                if (_matrix[x][y] > 0 && times[x][y] < 2) {
                    times[x][y]++;
                    times[y][x]++;
                    rec[count] = x;
                    count++; //留痕

                    //递归遍历下一个点
                    find_way(des, n, y, count);

                    //完成搜索后需要回溯到上一层递归，因此需要恢复使用的变量
                    times[x][y]--;
                    times[y][x]--;
                    rec[count] = -1;
                    count--;
                }
            }
        }

        //展示欢迎系统
        void print_Welcome() {
            cout << "==============================================" << endl;
            cout << "            欢迎来到旅游咨询系统！" << endl;
            cout << "==============================================" << endl << endl;
        }

        //展示所有景点以及景点介绍
        void print_Scenic() {
            cout << "为了节省您输入景点的时间，您可以直接输入景点开头的数字标号直接进行景点选择~" << endl << endl;
            for (int i = 0; i < 9; i++) {
                cout << "标号:" << i + 1 << endl;
                cout << "景点名称:" << scenic_area[i] << endl;
                cout << "景点介绍:";
                switch(i) {
                    case 0: {
                        cout << "一座具有悠久历史的佛教寺庙，坐落在厦门大学思明校区南大门，以其宁静的环境和独特的建筑风格吸引众多游客~" << endl;
                        break;
                    }
                    case 1: {
                        cout << "厦大内部的一片宁静的校园湖泊，是休闲散步和沉思的理想场所~" << endl;
                        break;
                    }
                    case 2: {
                        cout << "厦大校内水库，环境静谧美丽，风光宜人~" << endl;
                        break;
                    }
                    case 3: {
                        cout << "厦大内由学生进行艺术创作的涂鸦隧道，承载着厦大多届学生的回忆~" << endl;
                        break;
                    }
                    case 4: {
                        cout << "展示人类文明历史和多元文化的博物馆，致力于传承和弘扬人文精神~" << endl;
                        break;
                    }
                    case 5: {
                        cout << "厦大的主要运动场地，重要大会、运动会等均在此召开" << endl;
                        break;
                    }
                    case 6: {
                        cout << "涵盖了众多体育运动场所的运动场，展现了厦大校园的活力与健康的氛围~" << endl;
                        break;
                    }
                    case 7: {
                        cout << "一座历史悠久的海防工事，以其独特的军事建筑风格和壮丽的海景吸引游客~" << endl;
                        break;
                    }
                    case 8: {
                        cout << "夜间会变得格外活跃的小吃街~" << endl;
                        break;
                    }
                }
                cout << "-----------------------------------------------" << endl;
            }
        }

        //让用户输入游玩路线起点
        void print_Ori() {
            cout << endl;
            cout << "请输入游玩路线的起点标号：";
        }

        //让用户输入要经历的点的个数
        void print_Scenic_Number() {
            cout << "请输入要经历的景点的个数：";
        }

        //提醒用户输入需要经历的点的标号
        void print_num() {
            cout << "请输入需要经历的景点标号：";
        }
};

int main() {
    vector<string> vet;

    //压入vector中
    for (int i = 0; i < 9; i++)
        vet.push_back(scenic_area[i]);
    
    //定义键值对，再调用graph来开辟顶点集合的邻接矩阵
    graph<string, int> graph(vet);

    //初始化rec和res字符数组为0
    for (int i = 0; i < N*N; i++) {
        rec[i] = res[i] = -1;
    }

    for (int i = 0; i < n_v; i++) {
        for (int j = 0; j < n_v; j++) {
            graph._matrix[i][j] = -1;
            times[i][j] = 0;
        }
    }

    //创建地图中边的关系
    graph.AddEdge(scenic_area[0], scenic_area[1], 300);
    graph.AddEdge(scenic_area[1], scenic_area[2], 1000);
    graph.AddEdge(scenic_area[1], scenic_area[5], 780);
    graph.AddEdge(scenic_area[2], scenic_area[3], 500);
    graph.AddEdge(scenic_area[3], scenic_area[4], 430);
    graph.AddEdge(scenic_area[4], scenic_area[5], 300);
    graph.AddEdge(scenic_area[5], scenic_area[6], 450);
    graph.AddEdge(scenic_area[5], scenic_area[7], 1200);
    graph.AddEdge(scenic_area[7], scenic_area[8], 2100);
    
    //交互界面
    graph.print_Welcome();
    graph.print_Scenic();
    graph.print_Ori();
    int ori;
    cin >> ori;
    ori--;

    graph.print_Scenic_Number();
    int n;
    cin >> n;

    graph.print_num();

    int *des = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> des[i];
        des[i]--;
    }

    //输出查询到的路径以及最短路径和最短路程
    cout << endl << "查询中..." << endl;
    cout << "-----------------------------------------------" << endl;
    graph.find_way(des, n, ori);
    cout << endl << "最短的路程是：" << endl;
    for (int i = 0; i <= Final_Len; i++) {
        cout << scenic_area[res[i]];
        if (i < Final_Len)
            cout << "->";
    }
    cout << endl << "最短的路程为：" << len << "m" << endl;
    return 0;
}