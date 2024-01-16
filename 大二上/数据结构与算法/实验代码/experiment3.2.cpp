#include <iostream>
#include <vector>
#include <assert.h>
#include <unordered_map>
#include <queue>
using namespace std;
#define MAX 100

//定义visited数组用于DFS与BFS
bool visited[MAX];

//定义结构体模板，用于储存图中个顶点边的信息
template <class w>
struct Edge
{
    int dstPos = -1;
    w weight; //权值
    Edge<w> *next = nullptr;
    //结构体构造函数，引用该函数可以给定义的结构体进行数值初始化的操作
    Edge(int _dstPos, const w &_weight) : dstPos(_dstPos), weight(_weight), next(nullptr) {}
};

// v:节点的值，w:节点的权值  若flag == false，则表示该图为无向图
template <class v, class w, bool flag = false>
class linkTable {
    //定义结构体操作
    typedef Edge<w> Edge;

    private:
        vector<Edge *> _matrix;             //结构体指针向量，用来存邻接表
        unordered_map<v, int> _indexMap;    //定义键值对保存图节点对应邻接表数组的下标
        vector<v> _points;                  //顶点集合

        int _getPointsPos(const v &point) {
            typename unordered_map<v, int>::iterator pos = _indexMap.find(point);
            //若没找到，则返回-1
            if (pos == _indexMap.end()) 
                return -1;
            //找到了，则返回键值对中的值
            return pos->second;
        }

        void DFSHelper(int pos) {
            visited[pos] = true;
            cout << _points[pos] << " ";

            Edge *edge = _matrix[pos];
            while (edge != nullptr) {
                if (!visited[edge->dstPos]) {
                    DFSHelper(edge->dstPos);
                }
                edge = edge->next;
            }
        }

    public:
        //创建邻接表
        linkTable(const vector<v> &src) {
            int size = src.size();
            //断言处理，保证键值对的键值大于0，防止越界出现
            assert(size > 0);
            //重新调整顶点集合大小
            _points.resize(size);
            //遍历容器，对容器内元素进行赋值操作，并存下每个元素的键值对
            for (int i = 0; i < size; i++) {
                _points[i] = src[i];
                _indexMap[src[i]] = i;
            }
            _matrix.resize(size, nullptr);
        }

        //添加图中顶点之间的边关系
        void AddEdge(const v &src, const v &dst, const w &weight) {
            //寻找两顶点在哈希表中的位置
            int posSrc = _getPointsPos(src);
            int posDst = _getPointsPos(dst);
            
            //确保目标定点不是源顶点，防止闭环
            //创建新边
            Edge *edge = new Edge(posDst, weight);
            //先将新边的next指针指向了原先在'posSrc'位置的链表头
            edge->next = _matrix[posSrc];
            //再将_matrix[posSrc]指向新创建的边，完成边在邻接链表中的添加
            _matrix[posSrc] = edge;

            //若为无向图
             if (!flag) {
                edge = new Edge(posSrc, weight);
                edge->next = _matrix[posDst];
                _matrix[posDst] = edge;
            }
        }

        //在图中插入新节点并与已有顶点建立边关系，x:待插入节点，y:被插入节点，weight:权值，ver:节点个数
        void InsertVertex(const v &x, const v &y, const w &weight, int &ver) {
            //在哈希表中新加入待插入节点的键值对
            _indexMap[x] = ver++;
            //重新对顶点数组分配大小，并将待插入节点加入顶点数组中
            _points.resize(ver);
            _points[ver-1] = x;
            //增加邻接表的容量
            _matrix.resize(ver);
            //寻找两顶点在哈希表中的位置
            int posSrc = _getPointsPos(x);
            int posDst = _getPointsPos(y);
            //创建新边
            Edge *edge = new Edge(posDst, weight);
            edge->next = _matrix[posSrc];
            _matrix[posSrc] = edge;

            //若为无向图
            if (!flag) {
                edge = new Edge(posSrc, weight);
                edge->next = _matrix[posDst];
                _matrix[posDst] = edge;
            }
        }

        //删除图中某顶点和与其相连的边
        void DeleteVertex(const v &x) {
            //在哈希表中寻找指定顶点的下标值
            int pos = _indexMap[x];
            assert(pos >= 0);
            //找到指定点x的位置
            int tmpPos = _getPointsPos(x);
            //遍历邻接表中各个顶点，删掉与指定点相关的边
            for (int i = 0; i < _matrix.size(); ++i) {
                Edge *preEdge = nullptr;
                Edge *edge = _matrix[i];
                while (edge != nullptr) {
                    //若找到了与指定点相连的边，将其删除
                    if (edge->dstPos == tmpPos) {
                        if (preEdge != nullptr) {
                            preEdge->next = edge->next;
                        } else {
                            _matrix[i] = edge->next;
                        }

                        //释放内存
                        delete edge;
                        edge = preEdge != nullptr ? preEdge->next : _matrix[i];
                    } else {
                        preEdge = edge;
                        edge = edge->next;
                    }
                }
            }
            //在顶点集中删除指定点x
            _points.erase(_points.begin() + pos);
            //在哈希表中删除指定点x
            _indexMap.erase(x);
            //在邻接表中删除指定点x
            _matrix.erase(_matrix.begin() + pos);
        }

        //从第一个顶点开始对图进行DFS搜索
        void DFS(const v &start) {
            int pos = _getPointsPos(start);
            DFSHelper(pos);
            cout << endl;
            //DFS结束后重新初始化visited数组
            for (int i = 0; i < MAX; ++i)
                visited[i] = false;
        }
        
        //从第一个顶点开始对图进行BFS搜索
        void BFS(const v &start) {
            int pos = _getPointsPos(start);

            //创建队列用于BFS
            queue<int> q;
            //顶点入队
            q.push(pos);
            visited[pos] = true;

            while (!q.empty()) {
                int front = q.front();
                q.pop();
                cout << _points[front] << " ";

                Edge *edge = _matrix[front];
                while (edge != nullptr) {
                    if (!visited[edge->dstPos]) {
                        q.push(edge->dstPos);
                        visited[edge->dstPos] = true;
                    }
                    edge = edge->next;
                }
            }
            cout << endl;
            //BFS结束后重新初始化visited数组
            for (int i = 0; i < MAX; ++i)
                visited[i] = false;
        }

        //打印邻接表信息
        void PrintGraph() {
            for (int i = 0; i < _matrix.size(); ++i) {
                Edge *edge = _matrix[i];
                if (edge == nullptr)
                    continue;
                while (edge != nullptr) {
                    cout << _points[i] << "->";
                    cout << _points[edge->dstPos] << "权值：" << edge->weight << endl;
                    edge = edge->next;
                }
                cout << "--------------------------------" << endl;
            }
        }
};

    //打印交互界面
void print() {
                cout << "===============图的基本操作================" << endl;
                cout << "     输入1:打印当前图的邻接表" << endl;
                cout << "     输入2:在图中添加顶点" << endl;
                cout << "     输入3:在图中删除顶点以及与之相关的边" << endl;
                cout << "     输入4:在图中对两顶点添加边关系" << endl;
                cout << "     输入5:从第一个顶点开始对图进行DFS" << endl;
                cout << "     输入6:从第一个顶点开始对图进行BFS" << endl;
                cout << "     输入0:退出程序" << endl;
                cout << "===========================================" << endl;
}

int main() {
    //初始化visited数组
    for (int i = 0; i < MAX; ++i)
        visited[i] = false;
    //定义用户输入的顶点个数，同样也是哈希表中最后一个元素的键值
    int vernum;
    cout << "请输入顶点个数：";
    cin >> vernum;
    cout << "请输入顶点，用空格隔开，输入回车表示输入结束" << endl;
    //存输入的顶点字母
    char a;
    //定义容器来存储输入的顶点字母，用来创建邻接表
    vector<char> ver;
    //遍历存储
    for (int i = 0; i < vernum; ++i) {
        cin >> a;
        //消除空格的影响
        cin.ignore();
        ver.push_back(a);
    }

    //记录第一个顶点
    char first = ver[0];

    //记录顶点数组长度,用于插入操作
    int ver1 = ver.size();

    int flag = -1;
    //提示用户想要输出有向图还是无向图
    cout << "想要输出无向图输入1,想要输出有向图输入0" << endl;
    cin >> flag;
    //消除回车影响
    cin.ignore();
    //提示用户输入顶点之间的边关系与权值
    cout << "请输入需要添加边关系的两顶点并输入边的权值，每组数据之间用分号隔开，每组数据的两个顶点以及边的权值之间用空格隔开，输入回车表示输入结束，具体输入样例如下" << endl;
    cout << "a b 1; c d 2; e f 3(回车)" << endl;
    cout << "以上样例表示a与b、c与d、e与f之间分别建立边关系并确认权值" << endl;
    
    //若为无向图
    if (flag) {
        linkTable<char, int> graph(ver);
        char tmp = '0';
        while (tmp != '\n') {
            int weight1;     //边的权值
            char p, q;       //两个顶点
            scanf ("%c %c %d;", &p, &q, &weight1);
            //tmp用于吸收空格并判断是否为回车
            tmp = getchar();
            //添加两顶点边的关系
            graph.AddEdge(p, q, weight1);
        }
        cout << "无向图" << endl;
        graph.PrintGraph();
        //打印交互界面
        print();
        int k;
        do {
            cin >> k;
            switch (k) {
                case 1: {
                    cout << "当前图如下" << endl;
                    graph.PrintGraph();
                    break;
                }
                case 2: {
                    cout << "请输入需要插入的顶点与被插入的顶点，两点间与权重间用空格隔开" << endl;
                    char tmp1, tmp2;
                    int weight;
                    cin >> tmp1 >> tmp2 >> weight;
                    cin.ignore();
                    graph.InsertVertex(tmp1, tmp2, weight, ver1);
                    cout << "当前图如下" << endl;
                    graph.PrintGraph();
                    break;
                }
                case 3: {
                    cout << "请输入需要删除的顶点" << endl;
                    char y;
                    cin >> y;
                    cin.ignore();
                    graph.DeleteVertex(y);
                    cout << "当前图如下" << endl;
                    graph.PrintGraph();
                    break;
                }
                case 4: {
                    cout << "请输入需要添加边的两顶点，用空格隔开" << endl;
                    char x, y;
                    cin >> x >> y;
                    cin.ignore();
                    cout << "请输入边的权值" << endl;
                    int weight;
                    cin >> weight;
                    graph.AddEdge(x, y, weight);
                    cout << "当前图如下" << endl;
                    graph.PrintGraph();
                    break;
                }
                case 5: {
                    cout << "DFS结果如下" << endl;
                    graph.DFS(first);
                    break;
                }
                case 6: {
                    cout << "BFS结果如下" << endl;
                    graph.BFS(first);
                    break;
                }
            }
        } while (k != 0);
    }

    //若为有向图
    else {
        linkTable<char, int, true> graph2(ver);
        char tmp = '0';
        while (tmp != '\n') {
            int weight1;     //边的权值
            char p, q;       //两个顶点
            scanf ("%c %c %d;", &p, &q, &weight1);
            //tmp用于吸收空格并判断是否为回车
            tmp = getchar();
            //添加两顶点边的关系
            graph2.AddEdge(p, q, weight1);
        }
        cout << "有向图" << endl;
        graph2.PrintGraph();
        //打印交互界面
        print();
        int k;
        do {
            cin >> k;
            switch (k) {
                case 1: {
                    cout << "当前图如下" << endl;
                    graph2.PrintGraph();
                    break;
                }
                case 2: {
                    cout << "请输入需要插入的顶点与被插入的顶点，两点间与权重间用空格隔开" << endl;
                    char tmp1, tmp2;
                    int weight;
                    cin >> tmp1 >> tmp2 >> weight;
                    cin.ignore();
                    graph2.InsertVertex(tmp1, tmp2, weight, ver1);
                    cout << "当前图如下" << endl;
                    graph2.PrintGraph();
                    break;
                }
                case 3: {
                    cout << "请输入需要删除的顶点" << endl;
                    char y;
                    cin >> y;
                    cin.ignore();
                    graph2.DeleteVertex(y);
                    cout << "当前图如下" << endl;
                    graph2.PrintGraph();
                    break;
                }
                case 4: {
                    cout << "请输入需要添加边的两顶点，用空格隔开" << endl;
                    char x, y;
                    cin >> x >> y;
                    cin.ignore();
                    cout << "请输入边的权值" << endl;
                    int weight;
                    cin >> weight;
                    graph2.AddEdge(x, y, weight);
                    cout << "当前图如下" << endl;
                    graph2.PrintGraph();
                    break;
                }
                case 5: {
                    cout << "DFS结果如下" << endl;
                    graph2.DFS(first);
                    break;
                }
                case 6: {
                    cout << "BFS结果如下" << endl;
                    graph2.BFS(first);
                    break;
                }
            }
        } while (k != 0);
    }
    return 0;
}