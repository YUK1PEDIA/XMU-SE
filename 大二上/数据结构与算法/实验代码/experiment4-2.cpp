#include<iostream>
#include<queue>
using namespace std; 
#define MVNum 100 //最大顶点数
int visited[MVNum];

//定义图中边的结构体
typedef struct ArcNode {
 	int adjvex;  //该边所指向的顶点的位置 
 	struct ArcNode *nextarc;//指向下一条边的指针 
}ArcNode;

//定义图中顶点的结构体
typedef struct VerNode {
 	char data;//顶点信息
 	ArcNode *firstarc;//指向第一条依附该顶点的边的指针 
}VerNode, AdjList[MVNum];//AdjList表示邻接表类型


//图的结构定义 
typedef struct {
 	AdjList vertices; //定义一个数组vertices,是vertex的复数形式
 	int vexnum,arcnum; //图的当前顶点数和弧数
}ALGraph;

int LocateVex(ALGraph G,int u) {
    //在图G中查找顶点u，存在则返回顶点表中的下标；否则返回-1
 	for(int i=1; i <= G.vexnum; i++)
        if(u == G.vertices[i].data)
            return i;
    //未找到，返回-1
  	return -1;
} 

//创建无向图G 
void CreateGraph(ALGraph &G) { 
 	cout << "请输入总结点数和总边数：" << endl; 
    //输入总顶点数，总边数
 	cin >> G.vexnum >> G.arcnum;
    cin.ignore();

 	cout << "请输入各顶点值： " << endl; 
    //输入各顶点，构造表头结点表 
 	for(int i = 1; i <= G.vexnum; i++) {
  		cin >> G.vertices[i].data;//输入顶点值 
  		G.vertices[i].firstarc = NULL;//初始化表头结点的指针域
	}//for
	getchar();
 	//输入各边，构造邻接表
 
 	cout << "输入一条边依附的两个顶点值"<<endl; 
 	for(int k = 1; k <= G.arcnum; k++) {
        char v1,v2;
        //输入一条边依附的两个顶点 
        cin >> v1 >> v2;
        getchar();
        
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2); //确定顶点在G.vertices中的序号

        ArcNode *p1 = new ArcNode;  //生成一个新的边结点*p1
        p1->adjvex = j;  //邻接点序号为j 

        //头插法将新结点*p1插入顶点vi的边表头部 
        p1->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p1; 
        ArcNode *p2 = new ArcNode;
        p2->adjvex = i;  //邻接点序号为i
        //头插法插入p2 ,因为是无向网，所以是两条 
        p2->nextarc = G.vertices[j].firstarc;
        G.vertices[j].firstarc = p2; 
    }
}

//判断邻接表方式存储的无向图G的顶点i到j是否存在长度为k的简单路径 
int ExistPath(ALGraph G, int i, int j, int k) {
	if(i == j && k == 0)  //找到了一条路径,且长度符合要求 
        return true;
	else if (k > 0) {
        visited[i] = 1; 
        //选定一个顶点，往其所在的链表尾部遍历
        for(ArcNode *p = G.vertices[i].firstarc; p != NULL; p = p->nextarc) {
            int m = p->adjvex; 
            if(!visited[m]) {
                //递归调用函数（DFS思想）
                if(ExistPath(G, m, j, k-1)) 
                    return true; //剩余路径长度减一 
            }
        }
        visited[i]=0;
    }

    //没找到 
    return false; 
}



int main() {
	ALGraph G;
	ArcNode *p;
	CreateGraph(G);
	
	cout << "邻接表如下： " <<endl;
	for(int i = 1; i <= G.vexnum; i++) {
		cout << G.vertices[i].data;
		for(p = G.vertices[i].firstarc; p != NULL; p = p->nextarc)
			printf("->%d", p->adjvex);
		cout << endl; 
	} 
    int x;
    cout << "请输入1或0, 1表示进行简单路径判断, 0表示直接结束程序" << endl;
    cin >> x;
    cin.ignore();

    while (x) {
        cout << "请输入两个顶点名称以及简单路径长度，用空格隔开" << endl;
        int i, j, k;
        cin >> i >> j >> k;

        if (ExistPath(G, i, j, k)) //若存在
            cout << "存在该简单路径" << endl;
        else
            cout << "不存在该简单路径" << endl;
        
        for (int i = 0; i < MVNum; i++)
            visited[i] = 0;

        cout << "请输入1或0, 1表示进行简单路径判断, 0表示直接结束程序" << endl;
        cin >> x;
        cin.ignore();
    }

	return 0;
}