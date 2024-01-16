#include <iostream>
#include <cstdio>
#include <malloc.h>
#include <string.h>
using namespace std;
#define MAXVALUE 32767		//极大值相当于无穷大

typedef struct {
	char data; //数据域
	int weight;	//结点的权值
	int parent, lch, rch; //双亲与孩子的下标
} htNode, *huffmanTree;

typedef char** huffmanCode;	//第一个*是代表它是指针变量，说明它是数组
							//第二个*说明它是指针数组，代表这个char类型数组里每个元素都是*huffman			
int NODENUM; //输入的数据个数

//初始化哈夫曼树
int initHuffmanTree(huffmanTree& HT) { 
	HT = (htNode*)malloc(sizeof(htNode) * (2 * NODENUM)); //给HT(哈夫曼树变量)分配2 * NODENUM个htNOde大小的htNode类型的数组
	for (int i = 1; i <= 2 * NODENUM - 1; i++) //下标从1开始到2 * NODENUM
		HT[i].parent = HT[i].lch = HT[i].rch = -1; //双亲和孩子的值都置为-1
	cout << "请输入哈夫曼树各个结点的权值" << endl; //提示用户输入权重
	for (int i = 1; i <= NODENUM; i++)								
		cin >> HT[i].weight; //给每个结点赋予权值
	cin.ignore();	//消去上面cin存在缓冲区的回车
	cout << "请输入各结点的名称" << endl;
	for (int i = 1; i <= NODENUM; i++) {
		char a;
		cin >> a;
		cin.ignore(); //消除缓冲区的回车
		HT[i].data = a; //给每个结点赋予数据
	}
	return 1;
}

//构建哈夫曼树
void creatHuffmanTree(huffmanTree& HT, int n) { 
	if (n <= 1) //如果结点数小于等于1，不创建
		return;
	int min1, min2;	//定义两个数，来存储每次选取最小两个结点的权值
	int rnode, lnode; //定义两个下标值，来存储每次选取最小两个结点的下标
	for (int i = n + 1; i <= 2 * n -1; i++)	{ //要生成n-1个结点，所以要操作n—1次且从下标为n+1开始存储
		int min1 = MAXVALUE; int lnode = -1; //让最小值初始化为极大值，这样叶子结点的最大值再大也不会超过这个值了							
		int min2 = MAXVALUE; int rnode = -1;
		for (int j = 1; j <= i - 1; j++) { //因为起先是在前n个中选择最小的两个结点的权值，但新生成一个后就得在前n+1个中选择最小的两个结点的权值					
										   //假设n = 10 总结点数就得为19，那我们就只要比较18次就可以得出结果了，记住比较的次数比生成的总结点数少1
				if (HT[j].weight < min1 && HT[j].parent == -1) {
					min2 = min1;	rnode = lnode; //碰到比min1小的，那min1的值就给第二小的min2，下标也给它
					min1 = HT[j].weight; lnode = j;	//然后最小的给min1，下标同理
				}
				else if (HT[j].weight < min2 && HT[j].parent == -1) { //这是第二小的判断
					min2 = HT[j].weight;
					rnode = j;
				}
		}
		HT[lnode].parent = HT[rnode].parent = i; //最小两个结点的parent变为生成结点的下标
		HT[i].lch = lnode; HT[i].rch = rnode; //生成结点的左孩子为最小的min1的下标，右孩子同理
		HT[i].weight = HT[lnode].weight + HT[rnode].weight;	//生成结点的权值等于最小结点的权值相加
	}
}

//编写哈夫曼编码
void createHuffmanCode(huffmanTree HT, huffmanCode &HC, int n) { 
	HC = (huffmanCode)malloc(sizeof(huffmanCode) * n + 1); //申请n + 1个huffmanCode大小huffmanCode类型的临时空间
														   //因为下标是从一开始，所以我们要申请比结点多一个的结点，和哈夫曼树的结构对应，方便输出
	char* cd = (char*)malloc(sizeof(char) * n);	//申请n个char大小char类型的临时空间，这个临时数组记录每次遍历出来的编码
	int start = 0,c = 0,f = 0; //start为cd数组记录下标，c初始为叶子结点下标，而后就是孩子结点的下标，f记录双亲结点的下标
	cd[n - 1] = '\0'; //这个就是给printf留着的，因为printf不会生成'\0'，如果用puts就不用这句语句了
	for (int i = 1; i <= n; i++) { //只要叶子结点的编码
		start = n - 1; //这句要赋值n的话，start--要写在判断后方
		c = i;
		f = HT[c].parent;
		while (f != -1)	{ //根节点没有双亲
			start--;
			if (HT[f].lch == c)	//是左孩子就是0，右孩子就为1
				cd[start] = '0';
			else
				cd[start] = '1';
			c = f; f = HT[c].parent; //向根结点接近
		}
		HC[i] = (char*)malloc(sizeof(char) * (n - start)); //给数组里的数组申请n - start个char大小的char*类型的临时空间
		strcpy(HC[i], &cd[start]); //里记录的编码给HC的第i个数组
	}
	free(cd); //释放临时空间
}

//展示哈夫曼树
void show(huffmanTree HT, int n) { 
	cout << "哈夫曼树如下：" << endl;
	printf ("index\tweight\tparent\tLchild\tRchild\n");
	for (int i = n + 1; i <= 2 * n - 1; i++)
		printf ("%d.	%d\t%d\t%d\t%d\n", i-n, HT[i].weight, HT[i].parent, HT[i].lch, HT[i].rch);
}

int main() {
	printf ("请输入数据个数：");
	cin >> NODENUM; //scanf ("%d", &NODENUM);
	cin.ignore(); //char tmp1 = getchar();
	huffmanTree HT; //定义哈夫曼树的变量 
	initHuffmanTree(HT); //初始化该哈夫曼树 
	huffmanCode HC; //哈夫曼编码数组 
	creatHuffmanTree(HT,NODENUM); //创建哈夫曼树 
	createHuffmanCode(HT,HC,NODENUM); //编写哈夫曼编码 
	show(HT,NODENUM);
	for (int i = 1; i <= NODENUM; i++) { //遍历输出编码
		printf("%c:",HT[i].data);
		printf("%s\n", HC[i]);
	}
	system ("pause");
	return 0;
}