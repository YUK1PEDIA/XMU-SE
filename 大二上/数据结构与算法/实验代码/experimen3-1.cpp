//邻接矩阵实现图的基本操作
#include <iostream>
#include <vector>
#include <cstdio>
#include <map>
#include <assert.h>
#include <queue>
using namespace std;
#define MAX 100

//  v:图顶点保存的值; w:边的权值; max:最大权值，表示无穷,用来判断图中两点是否有关系; flag == true代表有向图，否则为无向图
template <class v, class w, w max = INT_MAX, bool flag = false>
class graph {
    private:
        vector<v> _verPoint;            //顶点集合
        map<v, int> _indexMap;			//顶点与下标的映射
        vector<vector<w> > _matrix;		//邻接矩阵，存每条边的权值
        
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
        bool visited[MAX] = {false};
        //根据用户输入的顶点集合来开辟邻接矩阵
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
        

        //打印邻接矩阵
        void PrintGraph() {
            //以下为打印邻接矩阵
            printf("  ");
            for (int i = 0; i < _verPoint.size(); i++)
                cout << _verPoint[i] << " ";
            printf ("\n");

            for (int i = 0; i < _matrix.size(); i++) {
                cout << _verPoint[i] << " ";                    //输出邻接矩阵
                for (int j = 0; j < _matrix[i].size(); j++) {
                    if (_matrix[i][j] == max)                   //若该点与遍历到的点无关，即无边的关系，则矩阵中对应位置输出0
                        printf("0 ");
                    else
                        cout << _matrix[i][j] << " ";           //若有关则输出权值
                }
                printf ("\n");
            }
            printf ("\n");
        }

        //判断图是否存在边<x,y>或(x,y)
        bool Adjacent(const v &x, const v &y) {
            return _matrix[_indexMap[x]][_indexMap[y]] != max;
        }

        //列出图中x相邻的边
        vector<v> GetNeighborsPoint(const v &x) {
            int index = _indexMap[x];
            //断言处理，保证键值对的键值大于等于0，防止越界出现
            assert(index >= 0);
            vector<v> result;
            for (int i = 0; i < _matrix[index].size(); i++) {
                //若边有关系，则压入结果向量中
                if (_matrix[index][i] != max) 
                    result.push_back(_verPoint[i]);
            }
            return result;
        }

        //在图中插入顶点x
        void InsertVertex(const v &x) {
            _verPoint.push_back(x);
            _indexMap[x] = _verPoint.size() - 1;
            for (int i = 0; i < _matrix.size(); i++)
                _matrix[i].push_back(max);
            vector<w> newLine(_verPoint.size(), max);
            _matrix.push_back(newLine);
        }

        //在图中删除顶点x
        void DeleteVertex(const v &x) {
            int pos = _indexMap[x];
            assert(pos >= 0);
            _verPoint.erase(_verPoint.begin() + pos);
            _indexMap.erase(x);
            _matrix.erase(_matrix.begin() + pos);
            for (int i = 0; i < _matrix.size(); i++)
                _matrix[i].erase(_matrix[i].begin() + pos);
        }

        //删除边<x，y>或(x，y)
        void RemoveEdge(const v &x, const v &y) {
            _matrix[_indexMap[x]][_indexMap[y]] = max;
            if (!flag)      //无向图
                _matrix[_indexMap[y]][_indexMap[x]] = max;
        }

        //设置边的权值（添加边）
        void SetEdgeValue(const v &x, const v &y, const w &z) {
            _matrix[_indexMap[x]][_indexMap[y]] = z;
            if (!flag)      //无向图
                _matrix[_indexMap[y]][_indexMap[x]] = z;
        }

        //从指定顶点开始DFS
        void DFS(const v &x) {
            //定义迭代器pos用于遍历邻接矩阵的键值
            typename map<v, int>::iterator pos = _indexMap.begin();
            //访问顶点
            cout << x << " ";
            //访问过后对应visited数组元素置为true
            visited[x-'a'] = true;
            //index存放当前元素在矩阵中的行数
            int index = _indexMap[x];
            for (int i = 0; i < _matrix[index].size(); i++, pos++)
                if (_matrix[index][i] == 1 && !visited[pos->first-'a'])
                    DFS(pos->first);
        }

        //从指定顶点开始BFS
        void BFS() {
            //定义队列，用于BFS遍历
            queue<v> q;
            //对每个顶点循环
            for (int i = 0; i < _verPoint.size(); i++) {
                if (!visited[_verPoint[i]-'a']) {   //若该点未访问
                    visited[_verPoint[i]-'a'] = true;
                    //访问该点
                    cout << _verPoint[i] << " ";
                    //入队
                    q.push(_verPoint[i]);
                    //若队不为空
                    while (!q.empty()) {
                        //存放队首元素，用于BFS
                        char tmp1 = q.front();
                        //队首元素出队
                        q.pop();
                        //index存放当前元素在矩阵中的行数
                        int index = _indexMap[tmp1];
                        //定义迭代器pos用于遍历邻接矩阵的键值
                        typename map<v, int>::iterator pos = _indexMap.begin();
                        for (int j = 0; j < _verPoint.size(); j++, pos++)
                            if (_matrix[index][j] == 1 && !visited[pos->first-'a']) {
                                cout << pos->first << " ";
                                visited[pos->first-'a'] = true;
                                q.push(pos->first);
                            }
                    }
                }
            }

        }

        //打印交互界面
        void print() {
                cout << "===============图的基本操作================" << endl;
                cout << "     输入1:判断图中边<x,y>或(x,y)是否存在" << endl;
                cout << "     输入2:在图中添加顶点" << endl;
                cout << "     输入3:在图中指定两点间添加边" << endl;
                cout << "     输入4:删除图中指定顶点" << endl;
                cout << "     输入5:删除图中指定两顶点的边" << endl;
                cout << "     输入6:打印当前图的邻接矩阵" << endl;
                cout << "     输入7:查找图中某点与其他顶点的关系" << endl;
                cout << "     输入8:从第一个顶点开始对图进行DFS" << endl;
                cout << "     输入9:从第一个顶点开始对图进行BFS" << endl;
                cout << "     输入0:退出程序" << endl;
                cout << "===========================================" << endl;
        }
};

int main() {
    vector<char> vet;
    //交互界面，提示用户输入顶点信息
    cout << "请输入顶点，每个顶点用空格隔开，输入回车代表输入结束" << endl;
    cout << "如:a b c d e f g" << endl;
    char a;
    while (a != '\n') {
		a = getchar();
        if (a != ' ' && a != '\n')
		    vet.push_back(a);
	}
    //记录输入的第一个顶点
    char first = vet[0];
    //定义了键值对，再调用graph来开辟顶点集合的邻接矩阵
    graph<char, int> graph(vet);
    cout << "请输入需要构造弧的顶点对，每个顶点对内部用空格隔开，顶点对之间用'; '隔开，输入回车表示结束" << endl;
    cout << "如:a b; c d" << endl;
    char p, q;
    while (p != '\n') {
        scanf ("%c %c;", &p, &q);
        graph.AddEdge(p, q, 1);
        p = getchar();
    }
    cout << "当前图如下：" << endl;
    graph.PrintGraph();
    //输出交互界面
    graph.print();
    int x;
    do {
        cin >> x;
        switch (x) {
            case 1: {
                        cout << "请输入需要判断的图中的两个顶点" << endl;
                        cout << "若两点有关系则返回true,否则返回false" << endl;
                        char m, n;
                        cin >> m >> n;
                        if (graph.Adjacent(m, n)) cout << "true" << endl;
                        else cout << "false" << endl;
                        break;
            }
            case 2: {
                        cout << "请输入需要插入的顶点值" << endl;
                        char in;
                        cin >> in;
                        graph.InsertVertex(in);
                        cout << "当前图如下" << endl;
                        graph.PrintGraph();
                        break;
            }
            case 3: {
                        cout << "当前图如下" << endl;
                        graph.PrintGraph();
                        cout << "请输入需要添加边的两顶点" << endl;
                        char p, q;
                        cin >> p >> q;
                        graph.SetEdgeValue(p, q, 1);
                        cout << "当前图如下" << endl;
                        graph.PrintGraph();
                        break;
            }
            case 4: {
                        cout << "当前图如下" << endl;
                        graph.PrintGraph();
                        cout << "请输入需要删除的顶点" << endl;
                        char tmp;
                        cin >> tmp;
                        graph.DeleteVertex(tmp);
                        cout << "删除后的图如下" << endl;
                        graph.PrintGraph();
                        break;
            }
            case 5: {
                        cout << "当前图如下" << endl;
                        graph.PrintGraph();
                        cout << "请输入需要删除边的两顶点" << endl;
                        char a, b;
                        cin >> a >> b;
                        graph.RemoveEdge(a, b);
                        cout << "删除指定边后的图如下" << endl;
                        graph.PrintGraph();
                        break;
            }
            case 6: {
                        cout << "当前图如下" << endl;
                        graph.PrintGraph();
                        break;
            }
            case 7: {
                        cout << "请输入需要查找的顶点" << endl;
                        char u;
                        cin >> u;
                        vector<char> ret = graph.GetNeighborsPoint(u);
                        cout << "结果如下" << endl;
                        for (int i = 0; i < ret.size(); i++)
                           cout << u << "->" << ret[i] << endl;
                        break;
            }
            case 8: {
                        cout << "DFS结果如下" << endl;
                        graph.DFS(first);
                        //DFS执行完后重新初始化visited数组
                        for (int i = 0; i < MAX; i++)
                            graph.visited[i] = false;
                        cout << endl;
                        break;
            }
            case 9: {
                        cout << "BFS结果如下" << endl;
                        graph.BFS();
                        //BFS执行完后重新初始化visited数组
                        for (int i = 0; i < MAX; i++)
                            graph.visited[i] = false;
                        cout << endl;
                        break;
            }
        }
    } while (x != 0);
    return 0;
}