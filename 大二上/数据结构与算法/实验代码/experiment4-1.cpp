#include<iostream>
#include<string>
using namespace std;
#define MVNum 100
#define MAXInt 32767//定义无穷大
typedef  string VerTex;
typedef int ArcType;

//图的邻接矩阵表示法存储结构
typedef struct {
	//arcnum表示边数,vernum表示顶点数
	int arcnum, vernum;
	//定义存储顶点的数组
	VerTex vex[MVNum];
	//定义存储边的数组
	ArcType arcs[MVNum][MVNum];
}AMGraph;

//辅助数组的定义，用来记录从顶点集U到V-U的权值最小的边
typedef struct {
	//最小边在U中的那个顶点
	VerTex adjvex;
	//最小边上的权值
	ArcType lowcost;
}MinEdge;
//创建辅助数组closedge
MinEdge closedge[MVNum];

//在顶点表中找到传入顶点的位置
int LocateVer(AMGraph G, VerTex v) {
	//遍历顶点表，返回某顶点在顶点表中的位置下标
	for (int i = 0; i < G.vernum; i++) {
		//在顶点表中找到了顶点v
		if (G.vex[i] == v)
			return i;
	}
	//没找到返回-1
	return -1;
}

//采用邻接矩阵表示法创建无向图
void CreateGraph(AMGraph &G) {
	//采用邻接矩阵表示法，创建无向图
	int i = 0, j = 0, k = 0, w;
    cout << "请输入图的总顶点数与总边数" << endl;
	cin >> G.vernum >> G.arcnum;

    cout << "请输入每个点的名称,每个点之间用空格隔开,输入回车结束输入" << endl;
	for (i = 0; i < G.vernum; i++)//依次输入点的信息
		cin >> G.vex[i];
	//消除回车的影响
	cin.ignore();

	//初始化邻接矩阵
	for (i = 0; i < G.vernum; i++)
		for (j = 0; j < G.vernum; j++)
			G.arcs[i][j] = MAXInt;
	
	//在两点之间创建边的关系
	cout << "请输入需要创建边关系的两顶点与边的权值，三个输入用空格隔开" << endl;
	for (k = 0; k < G.arcnum; k++) {
		//定义两个顶点v1,v2
		VerTex v1, v2;
		cin >> v1 >> v2 >> w;

		//确定v1和v2在G中的位置，即顶点数组的下标
		i = LocateVer(G, v1);
		j = LocateVer(G, v2);
		G.arcs[i][j] = G.arcs[j][i] = w;
	}
}

//在辅助数组中找到lowcost最小的顶点
int Min(MinEdge closedge[], int size) {
	//取最小权值边的顶点位置
	int k = -1;//最后接收最小权值邻接点的下标
	for (int i = 0; i < size; i++) {
		//closedge为辅助数组
		if (closedge[i].lowcost > 0) {//i号顶点并未被归入到生成树中
			int min = closedge[i].lowcost;//设置min中间变量存放最小权值
			//向后遍历，寻找最小的lowcost
			for (int j = i; j < size; j++) {
				if (closedge[j].lowcost > 0 && min >= closedge[j].lowcost) {
					min = closedge[j].lowcost;
					k = j;
				}
			}
			break;
		}
	}
	//返回权值最小的邻接点下标
	return k;
}

//构造最小生成树的Prim算法
void Prim(AMGraph G, VerTex u) {
	//从顶点u出发构造G的最小生成树T，输出T的各条边

	//k为顶点u的下标
	int k = LocateVer(G, u);
	
	//对V-U的每一个顶点vj，初始化closedge[j]
	for (int i = 0; i < G.vernum; i++) {
		closedge[i].adjvex = u;//{adjvex,lowcost}
		closedge[i].lowcost = G.arcs[k][i];
	}

	closedge[k].lowcost = 0;

	cout << endl << "Prim算法得到的最小生成树如下" << endl;
	//选择其余n-1个结点，生成n-1条边（n=G.vexnum）
	for (int i = 1; i < G.vernum; i++) {
		//求出T的下一个结点；第k个顶点,closedge[k]中存有当前最小边
		int k = Min(closedge, G.vernum);

		//u为最小边
		ArcType u = closedge[k].lowcost;
		//u1为最小边的一个顶点,u0属于u
		VerTex u1 = closedge[k].adjvex;
		//v0为最小边的另一个顶点，v0属于V-U
		VerTex v1 = G.vex[k];

		//输出当前两顶点与边
		cout << u1 << " " << u << " " << v1 << endl;
		
		//将第k个顶点并入U集
		closedge[k].lowcost = 0;
		for (int j = 0; j < G.vernum; j++) {
			//新顶点并入U后重新选择最小边
			if (G.arcs[k][j] < closedge[j].lowcost) {
				closedge[j].adjvex = G.vex[k];
				closedge[j].lowcost = G.arcs[k][j];
			}
		}
	}
}

int main() {
	AMGraph G;
	CreateGraph(G);
	Prim(G, G.vex[0]);
	return 0;
}
