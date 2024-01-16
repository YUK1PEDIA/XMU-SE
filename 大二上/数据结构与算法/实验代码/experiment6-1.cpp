#include <iostream>
#include <vector>
using namespace std;

//使用三指针算法，一个指针负责红色部分，一个指针负责白色部分，另一个指针负责蓝色部分
void DutchFlag(vector<int>& arr) {
    //定义三指针，red指向红色部分的尾部，white指向白色部分的尾部，blue指向蓝色部分的尾部
    int red = 0, white = 0, blue = arr.size() - 1;

    //用给定的vector模拟荷兰国旗，0表示红色条块，1表示白色条块，2表示蓝色条块
    while (white <= blue) { //用white指针与blue指针分别从vector的头部与尾部向中间靠近
        if (arr[white] == 0) {  // 红色
            swap(arr[red], arr[white]);
            red++;
            white++;
        } else if (arr[white] == 1) {  // 白色
            white++;
        } else {  // 蓝色
            swap(arr[white], arr[blue]);
            blue--;
        }
    }
}
    /*现对上述函数功能进行解释，因为红色条块一定在第一部分，因此将red指针初始化为0。我们需要对杂乱无章的vector元素顺序进行调整，
     *因为白色部分在中间，蓝色部分在末尾，因此调整过程应为移动white和blue指针，直到它们相遇，在相遇之前进行具体的数字顺序调整。
     *若white遍历到的是红色部分，则将其与指向红色的指针red进行交换，就将white指向的红色挪到了第一部分的位置，red和white都往后挪；
     *若遍历到的是白色部分，则直接把white指针往后挪；若遍历到的是蓝色部分，就将其与蓝色的指针blue进行交换，然后blue往前挪，
     *white继续往后挪，直到white和blue相遇，则整个数组就是荷兰国旗的排布
    */

int main() {
    // 示例
    vector<int> flagSequence = {2, 0, 1, 2, 1, 0, 2, 1, 0, 2, 1, 0, 0, 0, 2, 1, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2};

    //排序前
    cout << "排序前国旗如下";
    for (int i = 0; i < flagSequence.size(); ++i) {
        if (i % 6 == 0)
            cout << endl;
        cout << flagSequence[i] << " ";
    }
    cout << endl << endl;

    //对国旗进行排序
    DutchFlag(flagSequence);

    //排序后
    cout << "排序后国旗如下";
    for (int i = 0; i < flagSequence.size(); ++i) {
        if (i % 6 == 0)
            cout << endl;
        cout << flagSequence[i] << " ";
    }

    return 0;
}