#include <iostream>
#include <algorithm>
using namespace std;

struct Ind {	//索引表Index
	int ori;	//记录分组后每组数据的起始位置下标 
	int key;	//记录每组最大的数据 
};

class level_s {
	private:
		int N;	//数据个数 
		int n_index;	//分组个数 
		int *data;		//存储数据，用动态变量存
		int *index_data;	//存储每组存放数量，用动态变量存
		Ind *in_t;	//Ind类型数组，索引表
	public:
		level_s() {	//类的初始化
			N = 0;
			n_index = 0;
			data = NULL;
			index_data = NULL;
			in_t = NULL;
		} 
		level_s(int Num, int in_Num) {
			N = Num;
			n_index = in_Num;
			data = new int[N+10];	//调用new函数创建动态数组，指针返回给类中的table
			index_data = new int[n_index+10];
			in_t = new Ind[n_index+5];
		}
		~level_s() {	//析构函数，完成对象被删除前的一些清理工作（如：归还对象额外申请的资源等）
			delete[]data;  //调用delete删除动态变量
			delete[]index_data;
			delete[]in_t;
		}
		
		void create (int *T, int *T_index, int n_index1) {	//创建块与索引表，存放输入数据，T为数据，T_index为每块数据数量，n_index为分的块数
			data = T;
			index_data = T_index;
			n_index = n_index1;
			
			int k = 0;
			for (int i = 0; i < n_index; i++) {
				in_t[i].key = data[0];
				in_t[i].ori = index_data[i];
				for (int j = 0; j < index_data[i]; j++) {
					if (in_t[i].key < data[k]) in_t[i].key = data[k];
					k++;
				}
			}
		}
		
		int search_region (int n) {	//查找数据位于第几个区域
			for (int i = 0; i < n_index; i++) {
				if (n <= in_t[i].key)
					return i;
			}
			cout << "表中无此数据";
			return -1;
		}

		int search_position (int n, int r) {	//查找数据位于区域的第几个位置
			for (int i = 0; i < index_data[r]; i++) {
				if (r == 0) {
					if (n == data[i])
						return i;
				}
				else {
					int cnt = 0;
					for (int j = 0; j < r; j++)
						cnt += in_t[j].ori;
					if (n == data[cnt+i])
						return i;
				}
			}
			cout << "表中无此数据" << endl;;
			return -1;
		}

		void print_Index () {
			cout << "===============索引表================" << endl;
			int k = 0;
			for (int i = 0; i < n_index; i++) {
				cout << "第" << i + 1 << "块Max_Key:" << in_t[i].key << " " << "First_Index:" << k << endl;;
				k += in_t[i].ori;
			}
			cout << "=====================================" << endl;
		}
};

int main() {
	int N1;	//存入数据个数
	int N_index1;	//要对数据分的块数
	int *T1 = NULL;	//存入数据，调用new函数用动态变量存
	int *index_T1 = NULL;	//每块存放的数据个数
	int R = 0, P = 0, n = 0;
	cout << "请输入要存储的数据个数：";
	cin >> N1;
	T1 = new int[N1+10];
	cout << "请输入这些数据：";
	int i = 0;
	for (i = 0; i < N1; i++)
		cin >> T1[i];	//存入数据
	cout << "请输入要分为几块：";
	cin >> N_index1;
	cout << "请输入每块存储多少数据：";
	index_T1 = new int[N_index1+10];
	for (i = 0; i < N_index1; i++)
		cin >> index_T1[i];
	level_s List1 (N1, N_index1);	//创建类List1
	List1.create (T1, index_T1, N_index1);	//调用类中创建链表函数create，并对其进行分块处理
	List1.print_Index ();
	cout << "请输入要查找的数据：";
	cin >> n;
	R = List1.search_region(n);	//得到要查找的对象在第几块
	if (R >= 0) {
		P = List1.search_position(n, R);	//得到要查找的对象在对应块的第几个位置
		if (P >= 0)
			cout << "位置为第" << R+1 << "区域第" << P+1 << "个" << endl; 
	}
	system ("pause");
	return 0;
}