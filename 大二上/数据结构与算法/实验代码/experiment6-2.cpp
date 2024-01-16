#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>

using namespace std;

// 随机生成n个部门名称
void Names(char A[][25], int n) {
    srand(static_cast<unsigned int>(time(0)));
    int i, j, k;
    for (i = 0; i < n; i++) {
        k = 2 * (rand() % 10 + 3);  // 部门字数
        for (j = 0; j < k; j++)
            A[i][j] = rand() % 30 + 176;  // 汉字区
        A[i][j] = '\0';
    }
}

// 冒泡排序算法，按字典序排序
void bubbleSort(char A[][25], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // 使用strcmp比较字符串大小
            if (strcmp(A[j], A[j + 1]) > 0) {
                // 交换部门名称
                char temp[25];
                strcpy(temp, A[j]);
                strcpy(A[j], A[j + 1]);
                strcpy(A[j + 1], temp);
            }
        }
    }
}

int main() {
    const int N = 20;
    const int n = 5;

    char departmentNames[N][25];

    // 随机生成n个部门名称
    Names(departmentNames, n);

    cout << "原始部门名称：" << endl;
    for (int i = 0; i < n; i++) {
        cout << departmentNames[i] << endl;
    }

    // 使用冒泡排序按字典序排序
    bubbleSort(departmentNames, n);

    cout << "\n按字典序排序后的部门名称：" << endl;
    for (int i = 0; i < n; i++) {
        cout << departmentNames[i] << endl;
    }

    return 0;
}