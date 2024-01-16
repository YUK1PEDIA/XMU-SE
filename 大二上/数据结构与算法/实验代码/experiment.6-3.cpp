#include <iostream>
#include <vector>
using namespace std;

//对arr进行树形选择排序（锦标赛排序）
void treeSelectionSort(vector<int>& arr) {
    //n为容器大小
    int n = arr.size();

    //操作分为两个循环，外循环负责遍历数组，每次选择数组中未排序部分的最小值，并将最小值交换到当前位置
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        // 从i开始构建一棵二叉树，找到从i之后的点开始的最小值
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // 将最小值交换到当前位置
        swap(arr[i], arr[minIndex]);

        //交换之后i++，代表最小的值已经排好序并放在前面的位置，然后进入下一个范围的树形选择排序（锦标赛排序）
    }
}

int main() {
    vector<int> arr = {4, 2, 7, 1, 9, 3, 10, 5, 6, 8};

    cout << "原始序列：" << endl;
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    treeSelectionSort(arr);

    cout << "树形选择排序后的序列：" << endl;
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
