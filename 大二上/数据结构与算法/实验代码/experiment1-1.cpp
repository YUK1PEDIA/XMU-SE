#include <iostream>
#include <cstdio>
using namespace std;

typedef struct node {
	int data;
	struct node *next;
}Node;

void print() {	//输出程序交互界面
	cout << "链表基本操作" << endl;
	cout << "输入1创建空链表" << endl;
	cout << "输入2用尾插法创建链表 读到-1时停止创建" << endl;
	cout << "输入3用头插法创建链表 读到-1时停止创建" << endl;
	cout << "输入4销毁链表" << endl;
	cout << "输入5可求当前链表表长" << endl;
	cout << "输入6在当前链表中插入节点" << endl;
	cout << "输入7在链表中按位置删除表中节点" << endl;
	cout << "输入8在链表中按节点数值删除表中节点" << endl;
	cout << "输入9输出当前链表" << endl;
	cout << "输入0关闭程序" << endl;
}

Node *InitList () {			//创建一个空链表
	Node *head;
	head = (Node*) malloc (sizeof(Node));
	head->next = NULL;
	return head;
}

void NodeDestory (Node* head) {		//销毁链表
	free (head->next);
	head->next = NULL;
	head->data = 0;
}

int ListLength (Node* head) {		//求链表表长
	int ans = 1;
	Node *p = head;
	while (p->next != NULL) {
		ans++;
		p = p->next;
	}
	return ans;
}

Node *create1 () {		//创建链表（尾插法），当读入-1时停止创建链表，并返回头指针
	Node *head, *p1, *p2;
	int n = 0;
	p1 = p2 = (Node*) malloc (sizeof(Node));
	head = NULL;
	scanf ("%d", &p1->data);
	while (p1->data != -1) {
		n++;
		if (n == 1)
			head = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1 = (Node*) malloc (sizeof(Node));
		scanf ("%d", &p1->data);
	}
	p2->next = NULL;
	return head;
}

Node *create2 () {		//头插法，新节点插在头节点之后，读到-1时停止创建链表
	Node *head, *p1;
	head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	int x;
	while (scanf ("%d", &x) == 1 && x != -1) {
		p1 = (Node*)malloc(sizeof(Node));
		p1->data = x;
		p1->next = head->next;
		head->next = p1;
	}
	head = head->next;	//将指向头节点的指针往后挪
	return head;
}

void insert (Node *head, int number, int data) {	//在链表中插入新节点，第一个参数是链表头的地址，第二个是插入的位置，第三个是新节点数据
	int i = 0;
	Node *q = (Node*)malloc(sizeof(Node));
	q->data = data;
	Node *p = head;			//用链表头的地址是为了函数的操作能影响到链表头
	while (p != NULL) {
		if (i == number) {
			q->next = p->next;
			p->next = q;
			break;
		}
		else {
			i++;
			p = p->next;
		}
	}
}

void node_delete1 (Node *head, Node **head1, int number) {	//按位删除节点，head1为二级指针指向head
	int i = 1;
	Node *p = head, *q = p->next;
	if (number == 0)
		*head1 = q;
	else {
		while (q != NULL) {
			if (i == number) {
				p->next = q->next;
				free(q);
				break;
			}
			else {
				i++;
				p = q;
				q = q->next;
			}
		}
	}
}

void node_delete2 (Node *head, Node **head1, int number) {	//按数据删除节点
	Node *p = head, *q = p->next;
	if (p->data == number) {
			*head1 = q;
			return;
	}
	while (q != NULL) {
		if (q->data == number) {
			p->next = q->next;
			free(q);
			q = p->next;
		}
		else {
			p = q;
			q = q->next;
		}
	}
}

void node_print (Node *head) {		//输出链表
    Node *p = head;
    do {
        cout << p->data << ' ';
        p = p->next;
    } while (p != NULL);
	cout << '\n';
}

int GetElem (Node* head, int e, int i) {	//将链表的第i个元素通过e输出
	int cnt = 0;
	Node *p = head;
	while (cnt < i) {
		p = p->next;
		cnt++;
	}
	e = p->data;
	return e;
}

int main() {
	print();
	int x = 0, length = 0, num = 0, data = 0;
	Node *head, **head1 = &head;
	cin >> x;
	while (x != 0) {
		switch (x) {
			case 1: head = InitList ();
					cout << "链表已生成" << endl;
					break;
			case 2: cout << "请输入数据（读到-1时停止创建）：";
					head = create1 ();
					cout << "当前链表如下" << endl;
					node_print (head);
					break;
			case 3: cout << "请输入数据（读到-1时停止创建）：";
					head = create2 ();
					cout << "当前链表如下" << endl;
					node_print (head);
					break;
			case 4: NodeDestory (head);
					cout << "链表已销毁" << endl;
					break;
			case 5: length = ListLength (head);
					cout << "当前链表长度为：" << length << endl;
					break;
			case 6: cout << "请输入插入位置与插入数据：";
					cin >> num >> data;
					insert (head, num, data);
					cout << "当前链表如下" << endl;
					node_print(head);
					break;
			case 7: cout << "请输入删除第几个节点：";
					cin >> num;
					node_delete1 (head, head1, num);
					cout << "当前链表如下" << endl;
					node_print(head);
					break;
			case 8: cout << "请输入删除数据：";
					cin >> data;
					node_delete2 (head, head1, data);
					cout << "当前链表如下" << endl;
					node_print(head);
					break;
			case 9: cout << "当前链表如下" << endl;
					node_print (head);
					break;
		}
		cin >> x;
	}
	return 0;
}