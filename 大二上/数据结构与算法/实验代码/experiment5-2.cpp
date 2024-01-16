#include <iostream>
#include <queue>
using namespace std;

typedef struct BiTnode {
    int data;
    struct BiTnode *left;
    struct BiTnode *right;
} BiTnode;

#define N 100 

//递归查找
BiTnode *Search(BiTnode *root, int x) {
    if (root->data == x){ //找到目标值
        return root;
    } else if (x < root->data){ //若小于当前值，遍历左子树
        return Search(root->left, x);
    } else { //若大于当前值，遍历右子树
        return Search(root->right, x);
    }
}

//二叉树结点创建
BiTnode *CreateTreeNode(int x) {
    BiTnode *p = (BiTnode *)malloc(sizeof(BiTnode));
    p->data = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

//插入的递归算法
BiTnode *Insert(BiTnode *root, int x) {
    if (root == NULL) { //若为空，直接创建节点
        root = CreateTreeNode(x);
        return root;
    }
    if (x < root->data) { //若小于当前值，递归插入左子树
        root->left = Insert(root->left, x);
    }
    if (x > root->data) { //若大于当前值，递归插入右子树
        root->right = Insert(root->right, x);
    }
    return root;
}

//构建二叉排序树，此时root为引用变量，用来接收Insert的返回值，作为二叉树的根节点
void Create(BiTnode *&root, int str[], int n) {
    root = NULL;
    for (int i = 0; i < n; i++){
        root = Insert(root, str[i]);
    }
}

//删除结点
bool Delete(BiTnode *p) {
    BiTnode *q, *s; //辅助遍历二叉排序树
    
    //若p为叶子结点，则直接置空即完成删除
    if (p->left == NULL && p->right == NULL) {
        p = NULL;
    }

    //若左子树为空，则将p置为右子树，并释放左子树空间
    else if (p->left == NULL) {
        q = p;
        p = p->right;
        free(q);
    }

    //若右子树为空，则将p置为左子树，并释放右子树空间
    else if (p->right == NULL) {
        q = p;
        p = p->left;
        free(q);
    }

    //若左右子树均不为空，则找在中序遍历下目标值的直接后继
    else {
        q = p; //q记录要删除结点的前驱节点
        s = p->right; //s记录要删除结点的后继节点

        //直接找到p的右子树的最左端
        while(s->left != NULL) {
            q = s; //记录前驱节点
            s = s->left; //往下遍历
        }

        p->data = s->data; //将当前值的直接后继覆盖当前值
        
        if(q != p) //判断是否执行上述while循环
            q->left = s->right; //将后继节点的子树接到前驱节点的左子树
        else
            q->right = s->right; //将后继节点的子树接到前驱节点的右子树
        free(s);
    }
    return true;
}

bool DeleteBiT(BiTnode *root, int x) {
    if(root == NULL) {
        return false;
    }else {
        if(x == root->data)
            return Delete(root); //删除当前值
        else if(x < root->data)
            return DeleteBiT(root->left, x);
        else
            return DeleteBiT(root->right, x);
    }
}


void LevelOrder(BiTnode *root) {
    queue<BiTnode *> treenode; //队列存储结点
    if(root != NULL)
        treenode.push(root); //根结点入队
    while(!treenode.empty()) {
        BiTnode *p = treenode.front(); 
        treenode.pop(); //根结点出队
        cout<< p->data << " "; //输出队首元素，即当前访问的结点值
        if(p->left != NULL) {
            treenode.push(p->left);//如果有左子树，则将左子树的根结点入队
        }
        if(p->right != NULL) {
            treenode.push(p->right);//如果有右子树，则将右子树的根结点入队
        }
    }
}

int main() {
    BiTnode *root;
    int n;
    cout << "请输入二叉排序树的结点数" << endl;
    cin >> n;
    cin.ignore();

    int str[n];
    cout << "请输入二叉排序树的各结点数据" << endl;
    for(int i = 0; i < n; ++i) {
        cin >> str[i];
    }
    cin.ignore();

    Create(root,str,n); //创建二叉排序树
    cout << "当前二叉排序树的层序遍历序列为如下" << endl;
    //输出二叉排序树
    LevelOrder(root);
    cout << endl;

    cout << "请输入需要查找的结点值key" << endl;
    int key;
    cin >> key;
    cin.ignore();
    BiTnode *p = Search(root, key);
    if (p->right != NULL) {
        cout << "结点key的右孩子结点值为:" << p->right->data << endl;
    } else {
        cout << "当前结点无右孩子" << endl;
    }
    if (p->left != NULL) {
        cout << "结点key的左孩子结点值为:" << p->left->data << endl;
    } else {
        cout << "当前结点无左孩子" << endl;
    }

    cout << "请输入需要删除的节点值key" << endl;
    cin >> key;
    cin.ignore();
    DeleteBiT(root, key);
    cout << "删除结点key后的二叉排序树的层序遍历序列如下:" << endl;
    LevelOrder(root);
    return 0;
}