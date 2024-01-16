#include <iostream>
#include <stdlib.h>
#include <cstdio>
using namespace std;

typedef struct TreeNode {
	char data;//数据域
	TreeNode* Lchild;//左孩子
	TreeNode* Rchild;//右孩子
}*Tree, TreeNode; //Tree为定义指向树节点的指针，TreeNode为定义树节点

Tree head = new TreeNode; //建立全局变量的头结点

//输出程序交互界面
void print() {
	cout << "===============二叉树基本操作=================" << endl;
	cout << "//           输入1:初始化头结点            //" << endl;
	cout << "//           输入2:创建空二叉树            //" << endl;
	cout << "//           输入3:先序创建二叉树          //" << endl;
	cout << "//           输入4:插入新节点              //" << endl;
	cout << "//           输入5:展示当前二叉树          //" << endl;
	cout << "//           输入6:先序遍历二叉树          //" << endl;
	cout << "//           输入7:中序遍历二叉树          //" << endl;
	cout << "//           输入8:后序遍历二叉树          //" << endl;
	cout << "//           输入9:判断二叉树是否为空      //" << endl;
	cout << "//           输入10:输出二叉树总节点数     //" << endl;
	cout << "//           输入11:输出二叉树深度         //" << endl;
	cout << "//           输入12:输出二叉树叶子个数     //" << endl;
	cout << "//           输入13:清空已有二叉树         //" << endl;
	cout << "//           输入0:退出程序                //" << endl;
	cout << "=============================================" << endl;
}

//头结点的初始化
void Head_Init (Tree& T) {
	head->Rchild = head; //头结点的右指针始终指向自身
	if (!T) //判断树是否为空树
		head->Lchild = NULL; //若为空树，那么头节点的左指针置空
	else
		head->Lchild = T;
}

//创建空二叉树
void InitBitree (Tree& T) {
	head->Lchild = NULL; //将头结点置空
}

//前序创建二叉树
void CreateTree (Tree& T) {
	char x;
	cin >> x;
	if (x =='*') {	//输入*代表当前节点无左孩子或右孩子节点 
		T = NULL; return;	//返回上一层 
	}
	else {
		T = new TreeNode;
		T->data = x;
		CreateTree(T->Lchild);	//递归调用创建二叉树 
		CreateTree(T->Rchild);
	}
}

//插入新节点
void insert (Tree& T, char value) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode)); //创建新节点
	node->data = value; //初始化该结点,将传入的value赋值给新节点的数据域
	node->Lchild = NULL;
	node->Rchild = NULL;
	if (T == NULL) //若是空树
		T = node;
	else { //若不是空树
		while (T != NULL) {
			if (T->Lchild == NULL) {
				T->Lchild = node;
				break;
			}
			if (value < T->data) { //若插入的值比原有的值小，那么将其插入左孩子结点
				if (T->Lchild == NULL) {
					T->Lchild = node;
					return;
				}
				else 
					T = T->Lchild;
			}
			else { //否则就插入右孩子结点
				if (T->Rchild == NULL) {
					T->Rchild = node;
					return;
				}
				else
					T = T->Rchild;
			}
		}
	}
}

//展示二叉树
void show_Tree (Tree& T) {
	if (head->Lchild == NULL) {
		cout << "二叉树为空！" << endl;
		return;
	}
	if (T) {
		cout << T->data;
		if (T->Lchild || T->Rchild) {
			cout << "(";
			show_Tree(T->Lchild);
			cout << ",";
			show_Tree(T->Rchild);
			cout << ")";
		} 
	}
} 

//先序遍历
void Pre_Traversal(Tree& T) {
	if (T) {
		cout << T->data<<" ";
		Pre_Traversal(T->Lchild);
		Pre_Traversal(T->Rchild);
	}
}

//中序遍历
void Ino_Traversal(Tree& T) {
	if (T) {
		Ino_Traversal(T->Lchild);
		cout << T->data<<" ";
		Ino_Traversal(T->Rchild);
	}
}

//后序遍历
void Pos_Traversal(Tree& T) {
	if (T) {
		Pos_Traversal(T->Lchild);
		Pos_Traversal(T->Rchild);
		cout << T->data << " ";
	}
}

//二叉树是否为空
bool TreeEmpty(Tree& T) {
	if (T == NULL)
	{
		cout << "该二叉树为空！"<<endl; 
		return true;
	}
	else
	{
		cout << "该二叉树不为空！"<<endl;
		return false;
	}
}

//求二叉树的节点数
int TreeNodeCount(Tree& T) {
	if (T == NULL)
		return 0;
	else if (T->Lchild == NULL && T->Rchild == NULL)
		return 1;
	else
		return TreeNodeCount(T->Lchild) + TreeNodeCount(T->Rchild)+1; //+1是为了算上root节点 
}

//求二叉树的深度
int TreeDepth(Tree& T) {
	if (T == NULL) return 0;
	else {
		int i = TreeDepth(T->Lchild);
		int j = TreeDepth(T->Rchild);
		return i > j ? i + 1 : j + 1;
	}
}

//计算二叉树的叶子个数
int leaf (Tree& T) {
	if (!T)
		return 0;
	else if (!T->Lchild && !T->Rchild)	//若该节点是整个树的叶子 
		return 1;
	else
		return leaf(T->Lchild) + leaf(T->Rchild); 
} 

//清空二叉树（将二叉树置为空树）
void clearTree (Tree& T) {
	if (T != NULL) {
		clearTree(T->Lchild);
		clearTree(T->Rchild);
		delete T;
		T = NULL;
	}
} 

int main(){
	print();
	Tree T = NULL;
	int x;
	cin >> x;
	while (x != 0) {
		switch (x) {
			case 1: Head_Init(T);
					cout << "头结点初始化完成" << endl;
					break;
			case 2: InitBitree(T);
					cout << "空二叉树创建完成" << endl;
					break;
			case 3: cout << "若其节点的左孩子或右孩子不存在则使用*代替" << endl;
					cout << "如:(ABD**E**CF**G**)" << endl;
					CreateTree(T);
					cout << "创建完成，当前二叉树为：" << endl;
					show_Tree(T);
					cout << endl;
					break;
			case 4: char value;
					cout << "请输入需要插入的数据：";
					cin >> value;
					insert(T, value);
					//T = head->Lchild;
					cout << "当前二叉树为：";
					show_Tree(T);
					cout << endl;
					break;
			case 5: if (!TreeEmpty(T)) {
						cout << "当前二叉树为：";
						show_Tree(T);
						cout << endl;
					}
					break;
			case 6: if (!TreeEmpty(T)) {
						cout << "先序遍历结果为：";
						Pre_Traversal(T);
					}
					break;
			case 7: if (!TreeEmpty(T)) {
						cout << "中序遍历结果为：";
						Ino_Traversal(T);
					}
					break;
			case 8: if (!TreeEmpty(T)) {
						cout << "后序遍历结果为：";
						Pos_Traversal(T);
					}
					break;
			case 9: TreeEmpty(T);
					break;
			case 10: if (!TreeEmpty(T))
						cout << "该树的节点数为：" << TreeNodeCount(T) << endl;
					 else
					 	cout << "该树的节点数为:0" << endl;
					break;
			case 11:if (!TreeEmpty(T)) 
						cout << "该树的深度为：" << TreeDepth(T) << endl;
					 else
					 	cout << "该树的深度为:0" << endl; 
					break;
			case 12:if (!TreeEmpty(T)) 
						cout << "该树的叶子个数为：" << leaf(T) << endl;
					 else
					 	cout << "该树的叶子个数为:0" << endl;
					break;
			case 13:clearTree(T);
					cout << "二叉树已清空！" << endl;
					break;
		}
		cin.ignore(); //删去缓冲区空格，以免造成影响
		cin >> x;
	}
	system("pause");
	return 0;
}