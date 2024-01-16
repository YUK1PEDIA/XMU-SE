#include <iostream>
using namespace std;

//A[]表示需要查找的有序整型数组  x表示需要查找的整数  n表示数组的长度
int BiSearch(int A[], int key, int n) {
    int left = 1, right = n - 1;
    int mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (key == A[mid]) return mid + 1;
        if (key < A[mid]) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}

int main() {
    cout << "请输入需要查找的数组长度" << endl;
    int n;
    cin >> n;   //输入有序数组长度
    
    cout << "请输入有序数组，每个数字之间用空格隔开" << endl;
    //定义并读入有序整型数组
    int A[n];
    for (int i = 0; i < n; ++i)
        cin >> A[i];

    cout << "请输入需要查找的数字" << endl;
    //定义并读入需要查找的数字x
    int x;
    cin >> x;

    cout << "查找结果如下" << endl;
    if (BiSearch(A, x, n) == -1) {
        cout << "数组中不存在该元素" << endl;
    } else {
        cout << "该元素位置在数组的第" << BiSearch(A, x, n) << "位" << endl;
    }

    return 0;
}