#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 30; //名字数量
const int M = 50; 

struct name {  //名字结构体
    char s[30];
    int v;   //ascll码值之和
} NAME[N]; //定义结构体数组

struct hash {  //哈希表结构体
    char name[30];   //名字
    int key;   //名字对应的关键字，相当于“键”
    int sum;   //用来记录搜索当前元素的搜索长度
} HASH[M];

//初始化
void init() {
    int i, j, sum;
    for(i = 0; i < N; ++i)
        NAME[i].v=0;
    
    strcpy(NAME[0].s, "houguoyu");//候国玉
    strcpy(NAME[1].s, "sunxiaochuan");//孙晓川
    strcpy(NAME[2].s, "huangsizhe");//黄思哲
    strcpy(NAME[3].s, "liuhexiang");//刘鹤翔
    strcpy(NAME[4].s, "tanhengyue");//潭衡岳
    strcpy(NAME[5].s, "wuzhenyu");//乌镇域
    strcpy(NAME[6].s, "songzetao");//宋泽涛
    strcpy(NAME[7].s, "wangzijiang");//王子将
    strcpy(NAME[8].s, "jiangyuan");//江雨安
    strcpy(NAME[9].s, "tangchengyao");//唐澄姚
    strcpy(NAME[10].s, "qiuchang");//邱畅
    strcpy(NAME[11].s, "lijing");//李晶
    strcpy(NAME[12].s, "liwei");//李伟
    strcpy(NAME[13].s, "wanglei");//王磊
    strcpy(NAME[14].s, "zhangwei");//张伟
    strcpy(NAME[15].s, "dingzhen");//丁真
    strcpy(NAME[16].s, "zhangweiwei");//张维为
    strcpy(NAME[17].s, "chenping");//陈平
    strcpy(NAME[18].s, "chenze");//陈泽
    strcpy(NAME[19].s, "litong");//黎桐
    strcpy(NAME[20].s, "chenziwei");//陈紫薇
    strcpy(NAME[21].s, "zhangyuchang"); //张宇昌
    strcpy(NAME[22].s, "yangsong");//杨松
    strcpy(NAME[23].s, "xiejiajun");//谢嘉俊
    strcpy(NAME[24].s, "raoyitian");//饶毅天
    strcpy(NAME[25].s, "chenxiaoyu");//陈晓宇
    strcpy(NAME[26].s, "zhangyi");//张艺
    strcpy(NAME[27].s, "longyutao");//龙玉涛
    strcpy(NAME[28].s, "chenhao");//陈浩
    strcpy(NAME[29].s, "guoweibing");//郭炜兵

    for(i = 0; i < N; ++i) {
        sum = 0;
        for(j = 0; j < strlen(NAME[i].s); ++j)
            sum = sum + (NAME[i].s[j] - 'a');

        NAME[i].v = sum;   //名字字母ascll码之和
    }
}

//构造哈希表
void creathash() {
    int i;
    int n, m, counts;
    //初始化
    for(i = 0; i < M; ++i) {
        strcpy(HASH[i].name, "0");
        HASH[i].key = 0;
        HASH[i].sum = 0;
    }

    //遍历30个名字
    for(i = 0; i < N; ++i) {
        counts = 1;
        n = (NAME[i].v) % 47;
        m = n;
        if(HASH[n].sum == 0) {  //若不发生冲突
            strcpy(HASH[n].name, NAME[i].s);
            HASH[n].key = NAME[i].v;
            HASH[n].sum = 1;
        } else {  //如果发生了冲突就处理冲突
            while(1) {
                m= (m + 1) % 47; //除留余数法
                counts++;
                if(HASH[m].key == 0)
                    break;
            }
            strcpy(HASH[m].name,NAME[i].s);
            HASH[m].key = NAME[i].v;
            HASH[m].sum = counts; //当前冲突的元素个数
        }
    }
    return;
}

//查找姓名，输出其姓名、关键字等信息
void searchhash() {
    char name[30];
    //sum用来记录需查找姓名的ascll码之和，n用来存需查找姓名（未出现哈希冲突）对应的键值（除留余数法）
    //m用来存需查找姓名（出现哈希冲突）对应的键值
    int sum, n, m, counts;
    sum = 0;
    n = 0;
    counts = 1;
    printf("请输入要查找人的姓名拼音：\n");
    scanf("%s", name);
    for (int i = 0; i < strlen(name); ++i)
        sum += (name[i] - 'a');
    n = sum % 47;
    m = n;
    if (strcmp(HASH[n].name, name) == 0)
        printf("姓名:%s 关键字:%d 查找长度:1\n", HASH[n].name, sum);
    else if (HASH[n].sum == 0)
        printf("没有找到这条记录\n");
    else {
        while(1) {
            m = (m + 1) % 47;
            counts++;
            if(strcmp(HASH[m].name, name) == 0) {
                printf("姓名:%s 关键字:%d 查找长度:%d\n", HASH[m].name, sum, counts);
                break;
            }
            if(HASH[m].key == 0) {
                printf("没有找到这条记录！\n");
                break;
            }
        }
    }
}

//演示哈希表
void displayhash() {
    int i, sum; //用来存查找长度之和
    float ASL; //存平均查找长度ASL
    ASL = 0.0;
    sum = 0;
    printf("\n地址\t关键字\t\t搜索长度\t姓名\n");
    for(i = 0; i < M; ++i) {
        printf("%d", i);
        printf("\t%d", HASH[i].key);
        printf("\t\t%d", HASH[i].sum);
        printf("\t\t%s", HASH[i].name);
        printf("\n");
    }
    for(i = 0; i < M; ++i) {
        sum += HASH[i].sum;
    }
    ASL = ((sum) * 1.0) / N;
    printf("\n");
    printf("平均查找长度ASL(%d)=%.3lf\n", N, ASL);
    return;
}

//展示姓名拼音和关键字
void display() {
    int i;
    printf("\n\t关键字\t\t姓名\n");
    for(i = 0; i < 30; ++i) {
        printf("\t%d", NAME[i].v);
        printf("\t\t%s", NAME[i].s);
        printf("\n");
    }
    return;
}

void menu() {
    cout << "汉字姓名拼音哈希表展示查找系统" << endl;
    cout << "1.展示姓名拼音和关键字" << endl;
    cout << "2.展示哈希表" << endl;
    cout << "3.查找关键字" << endl;
    cout << "4.退出" << endl << endl;
}

int main() {
    int n;
    int flag;
    flag = 1;
    //给出交互菜单
    menu();

    while(1) {
        if(flag == 1) {
            init();
            creathash();
            flag = 0;
        }
        cin >> n;
        cin.ignore();
        if(n < 1 || n > 4) {
            cout << "输入有误，请重新输入！！！" << endl;
            continue;
        } else {
            switch(n) {
                case 1: {
                    cout << "展示所准备的姓名拼音及其所组成的关键字：" << endl;
                    display();
                    break;
                }
                case 2: {
                    displayhash();
                    break;
                }
                case 3: {
                    searchhash();
                    break;
                }
                case 4: {
                    return 0;
                }
            }
        }
    }
    return 0;
}