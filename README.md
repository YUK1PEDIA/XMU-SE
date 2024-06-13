[TOC]



# 多媒体技术

## 音频数字化

**数字音频**

- 通过模数转换器（A/D Converter）将**声波波形**转换成**一连串的二进制数据**来再现原始声音
- 以每秒上万次的速率对声波进行**采样**，每一次**采样**都记录下原始模拟声波**在某一时刻的状态**，称之为**样本**
- 为每个**样本**分配一定的存储位（bit）来表达声波的振幅状态，称之为**样本精度/采样精度**

![image-20240604193007245](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604193007245.png) 



### 音频的数字化

- 将模拟音频转化为数字音频
  - **采样**：每隔一段时间就记录一次声音信号的幅度
  - **量化**：把采样得到的**声音信号幅度转换为数字值**
  - **时间上**的离散叫**采样**，**幅度上**的离散叫**量化**
- 采样频率
  - 将模拟音频数字化时，**每秒钟所抽取声波幅度样本的次数**，采样频率的计算单位是kHz
  - 一般来讲，**采样频率越高，声音失真越小**，但用于存储音频的数据量也越大
- 奈奎斯特采样定律
  - **采样频率不应低于声音信号最高频率的两倍**
  - 可以这样来理解奈奎斯特理论：声音信号可以看成由许许多多**正弦波**组成的，一个振幅为A、频率为f的正弦波**至少需要两个采样样本表示**，因此，**如果一个信号中的最高频率为Fm，采样频率最低要选择2*Fm**。例如，电话话音的信号频率约为3.4 kHz，采样频率就选为8 kHz。
- 样本精度
  - 模拟音频中，声音的幅度通常用电压表示；**在数字音频中，电压通常用数字表示**。例如0.5V电压用20表示，2V电压用80表示
  - 电压是连续变量，即使在某电平范围内，仍有无穷多个，如1.2V、1.21V、1.215V...
  - 用数字表示音频幅度时，只能把无穷多个电压幅度用有限个数字表示，即**把某一个幅度范围内的电压用一个数字表示**，这个过程称为**量化**
  - **样本精度是每个采样点能够表示的数字范围**，常用的有8位、12位和16位。例如8位量化及表示每个采样点可以表示 2^8 = 256个（0-255）不同量化值
  - 量化的过程是，**先将整个幅度划分为有限个小幅度（量化阶距），把落入某个阶距内的养值归为一类，并赋予相同的量化值**

![image-20240604194027727](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604194027727.png) 



### 数字音频文件大小的计算（重点）

![image-20240604194132677](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604194132677.png) 

![image-20240604194155050](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604194155050.png)



![image-20240604194333355](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604194333355.png)

### 例题

![image-20240604194402595](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604194402595.png) 

**答案：C**

![image-20240604194408532](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604194408532.png) 

**答案：D**



![image-20240604195509036](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604195509036.png) 

**答案**

(1)

![image-20240604200650674](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604200650674.png) 

![image-20240604200702227](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604200702227.png) 



(2)

![image-20240604200717619](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604200717619.png) 



(3)

![image-20240604200803735](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604200803735.png) 





## 数字图像（了解即可）

图像：物体在平面坐标上的直观再现，是其所表示物体的信息的**直接描述和概况表示**

- 数字图像：像素组成的二维或三维排列，可以用矩阵表示
- 图像可以用一个二元函数表示 f(x, y)
  - x、y分别表示横坐标和纵坐标，函数 f 的值表示**亮度**或**灰度值**
  - 数字图像：当x、y和函数 f 的值都是**有限、离散的**



### 像素

概念：组成数字图像的元素，每个像素包括**位置和亮度信息**

- **对于单色（灰度）图像而言**，每个像素的亮度用一个数值来表示，通常数值范围在0到255之间，0表示黑、255表示白，其它值表示处于黑白之间的灰度。

- **彩色图像可以用红、绿、蓝三元组的二维矩阵来表示**。通常三元组的每个数值也是在0到255之间，**0表示相应的基色在该像素中没有**，而255则代表**相应的基色在该像素中取得最大值。**



### 数字图像的类型

- **二值图像**
  - 灰度值只有0和1两个的图像。**0代表黑色，1代表白色**
- **灰度图像**
  - 一般指具有256级灰度值的图像。数据类型一般为8位无符号整数。**0代表黑色，255表示白色。其他表示从黑到白的过渡色**
- **索引图象**
  - 包括存放图像数据的二维矩阵，还包括一个颜色索引矩阵（MAP）。两个矩阵建立映射关系
- **RGB彩色图像**
  - 称为真彩色图像。由R、G、B来表示每个像素的颜色。颜色值直接存放在矩阵中，无需索引。即 M * N * 3





### 颜色模型

- RGB 相加颜色模型
  - 红色+绿色+蓝色
- CMY 相减颜色模型
  - 青色+品红+黄色
- HSL 颜色模型
  - 色调、饱和度、亮度
- YUV 颜色模型
  - Y表示亮度，U表示色度，V表示浓度

![image-20240604202832624](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604202832624.png) 



**颜色空间变换**

![image-20240604202944696](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604202944696.png) 

![image-20240604203005025](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604203005025.png) 

![image-20240604203013873](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604203013873.png) 





### 例题

![image-20240604203116078](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604203116078.png) 

**答案**

![image-20240604203128814](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604203128814.png) 





## 像素空间关系

### 像素间联系

- 像素p的邻域
  - 4近邻：*N*4 (*p*)
  - 对角近邻：*N*D (*p*)
  - 8近邻：*N*8 (*p*)

![image-20240604203533327](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604203533327.png) 

![image-20240604203541963](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604203541963.png) 

![image-20240604203548390](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604203548390.png) 



- **连通性**是描述**区域**和**边界**的基本概念
- **两个像素具有连通性的两个必要条件**
  - 两个像素**是否相邻**
  - 他们的**灰度值**是否满足**相似性准则**
    - **设V是具有相似灰度的集合**。对于二进制图像，可令V={1}；对于具有256灰度级的灰度图像，V是这256数值中的一个子集
- 连通性
  - 4连通
  - 8连通
  - m连通（混合连通）

![image-20240604203830022](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604203830022.png) 

![image-20240604203836507](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604203836507.png) 

![image-20240604203848882](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604203848882.png) 

![image-20240604203909892](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604203909892.png) 



- **通路**

![image-20240604204217626](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604204217626.png) 



- **距离度量**

![image-20240604204324442](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604204324442.png) 



- **欧氏距离**

![image-20240604204404446](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604204404446.png) 

![image-20240604205923215](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604205923215.png) 





- **D4距离**

![image-20240604204425653](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604204425653.png) 

![image-20240604205940809](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604205940809.png) 



- **D8距离**

D8距离又可以这样理解：从点p向点q出发，每次能走一下个点必须是在当前像素点的8邻域中，一步一步走到q点，一共经过的像素点数就是D8距离

![image-20240604204520348](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604204520348.png) 



#### 例题

![image-20240604204542920](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604204542920.png) 

**答案**

![image-20240604204555021](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604204555021.png) 



![image-20240604204649092](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604204649092.png) 

**答案**

![image-20240604204700527](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240604204700527.png) 











## 数据压缩与编码

### 信息量和信息熵

**数据压缩的理论基础是信息论**。根据信息论原理，可以找到最佳数据压缩编码方法，**数据压缩的理论极限是信息熵**

- 无失真编码（熵编码）
  - 编码过程中不丢失信息，即要求保存信息熵
- 有失真编码
  - 可允许信息部分损失以换取较高的压缩比
- **信息量 = 数据量 - 冗余量**

![image-20240605193431662](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240605193431662.png) 

![image-20240605193452058](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240605193452058.png) 



#### 信息的度量

- **信息是用不确定性的度量定义的**
  - 一个消息的**可能性越小**，其**信息越多**
  - 而消息的**可能性越大**，其**信息越少**





#### 信息熵的计算（重点）

- 信息论定义了一种度量信息量的方法

![image-20240605193613322](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240605193613322.png) 



- 信源的熵H(X)定义为：**信源X发出的n个随机事件xj(j=1,2,...,n)的自信息量的统计平均**

![image-20240605193802096](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240605193802096.png) 

当a取2时，H(X)的单位为“比特”(bit)或者“香农”(Sh)



![image-20240605194015900](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240605194015900.png) 

![image-20240605194024401](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240605194024401.png) 

![image-20240605194449074](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240605194449074.png) 

##### 信息熵的计算

**公式**

![image-20240605195043966](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240605195043966.png) 



**例子**

![image-20240605195102369](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240605195102369.png) 

**X的信息熵计算**

列X的信息熵计算为：p(男) = 3/5 = 0.6；p(女) = 2/5 = 0.4。根据上面的计算公式可得

列X的信息熵为：H(X) = -(0.6 * log2(0.6) + 0.4 * log2(0.4)) = 0.97



**Y的信息熵计算**

列Y的信息熵计算为：p(优) = 4/5 = 0.8；p(差) = 1/5 = 0.2。根据上面的计算公式可得

列Y的信息熵为：H(Y) = -(0.8 * log2(0.8) + 0.2 * log(0.2)) = 0.72







### Huffman编码（重点）

构建哈夫曼编码的具体步骤如下

- 将信源符号的概率按减小的顺序排队
- 把两个最小的概率相加，并继续这一步骤，始终将较高的概率分支放在右边，直到最后变成概率1
- 画出由概率1处到每个信源符号的路径，顺序记下沿路径的0和1，所得就是该符号的哈夫曼编码
- 将每对组合的左边一个指定为0，右边一个指定为1（或者相反）

![image-20240605200326664](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240605200326664.png) 

![image-20240605200335219](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240605200335219.png) 

![image-20240605200342074](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240605200342074.png) 

![image-20240605200349047](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240605200349047.png) 

![image-20240605200359759](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240605200359759.png) 





### 算术编码

基本思想：**算术编码不是将单个信源符号映射成一个码字，而是把整个信源表示为实数线上的0到1之间的一个区间，其长度等于该序列的概率，再在该区间内选择一个代表性的小数，转化为二进制作为实际的编码输出**

- 消息序列中的每个元素都要用来缩短这个区间。消息序列中元素越多，所得到的区间就越小，表示这个区间所需的位数就更多
- 采用算术编码每个符号的平均编码长度可以为小数，因此可以更加接近无损压缩的熵极限



**怎么算？**

**新子区间的起始位置= 前子区间的起始位置 + 当前符号的区间左端 * 前子区间长度**

**新子区间的长度 = 前子区间的长度 * 当前符号的概率（等价于范围长度）**

**最后得到的子区间的长度决定了表示该区域内的某一个数所需的位数**



**例子1**

![image-20240606205723299](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240606205723299.png) 



![image-20240606210420464](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240606210420464.png) 





**例子2**

![image-20240606210739929](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240606210739929.png) 

![image-20240606210752573](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240606210752573.png) 





**自适应算术编码**

![image-20240606210803714](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240606210803714.png) 



![image-20240606210842029](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240606210842029.png) 



**上面的例子可能比较抽象，具体的例子可以看下面的链接**

[什么是算术编码、算术编码的编码和解码_算术编码通俗讲解-CSDN博客](https://blog.csdn.net/TOM0078/article/details/135014173)







## JPEG压缩编码

**JPEG标准**

- 达到或接近当前压缩比和图像保真度的技术水平，能覆盖一个较宽的图像质量等级范围，能达到“很好”到“极好”的评估，与原始图像相比，人的视觉难以区分
- 能适合任何种类的连续色调的图像，长宽比不受限制，同时也不受限于景物内容、图像的复杂程度和统计特性等
- 计算复杂度是可控制的，其软件可在各种CPU上完成，算法也可用硬件实现



**JPEG算法的4种操作方式**

![image-20240608142815336](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608142815336.png) 



![image-20240608142955711](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608142955711.png) 



### 离散余弦变换

JPEG实现图片压缩就是靠DCT（离散余弦变换）

![image-20240608143359909](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608143359909.png) 

![image-20240608143947601](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608143947601.png) 

![image-20240608144052029](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608144052029.png) 

![image-20240608144134984](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608144134984.png) 

![image-20240608144141441](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608144141441.png) 





### JPEG编码

对于输入的图像，JPEG编码要经过以下的步骤

- **零偏置**

JPEG编码将图像分为`8*8`的块作为数据处理的最小单位，对于灰度级为`2^n`的像素，通过减去`2^(n-1)`将无符号数变为有符号数。以灰度级n=8的图像为例，将原来图像的灰度范围 [ 0 − 255 ] 减去 128 后，范围变成了 [ − 128 − 127 ]

- **DCT变换（离散余弦变换）**

对零偏置后的图像进行DCT变换，以进行能量集中和去相关，去除图像的空间冗余。变换后的图像能量集中在右上角。

DCT变换同样以`8*8`的块为单位，具体公式如下

![image-20240608155754628](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608155754628.png) 

其中C为DCT变换矩阵

![image-20240608155812706](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608155812706.png) 

f(x, y)为原始图像。**DCT变换是一种无损变换，在变换过程中没有精度损失**

- **量化**

根据人眼的视觉特性，人眼对高频信息的不敏感，在JPEG中采用低频细量化，高频粗量化，以降低视觉冗余。同时由于人眼对色度信号的敏感度低于亮度信号，故对于亮度和色度信号有不同的量化系数 `Q(u, v) `

量化结果可表示为

![image-20240608155947422](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608155947422.png) 

根据不同质量的要求，可以建立不同的量化系数表

- **DC系数的差分编码**

`8*8`图像块经过DCT变换后得到的**DC直流系数**有两个特点

1. 系数的数值比较大
2. 相邻`8*8`图像块的DC系数值变化不大：**冗余**

根据这个特点，JPEG算法使用了**差分脉冲调制编码（DPCM）技术**，对**相邻图像块之间量化DC系数的差值DIFF**进行编码

![image-20240608160305646](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608160305646.png) 

采用熵编码（哈夫曼编码）的方式，亮度信号与色度信号的DC系数采用不同的哈夫曼编码表

- **AC系数的Zig-zag扫描与游程编码**

由于经过DCT变换后，系数大多集中在左上角，即低频分量区，因此采用Z字形扫描按频率的高低顺序读出，可以出现很多连零的机会，以便使用RLE游程编码

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200531180405993.JPG?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDk0OTU1Mg==,size_16,color_FFFFFF,t_70#pic_center) 

尤其在最后，如果都是零，给出EOB(End of Block)即可

![image-20240608160529100](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608160529100.png) 







## MPEG编码（主要是MPEG-1）

MPEG主要包括**MPEG视频**、**MPEG音频**和**MPEG系统**（视音频同步）三个部分

![image-20240608161738538](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608161738538.png) 



### MPEG-1视频

- MPEG-1的标准号为ISO/IEC 11172，是针对数据传输速率大约为1.5Mbps的数字存储媒体的视频及其伴音编码、解码的国际标准
- MPEG-1主要用于在CD-ROM上存储视频和音频信号。视频编码采用SIF（Source Input Format）格式
  - 分辨率：360×240×30（NTSC制式），4:2:0的采样方式，压缩率约26:1，图像质量接近VHS
  - MPEG-1音频编码器的输入为线性PCM信号，双声道，采样频率为32kHz，44.1kHz或者48kHz，输出为32kb/s~384kb/s，可以达到CD质量



#### 1.视频数据的压缩算法

- MPEG-1视频(MPEG-1 Video)压缩数据的基本方法

  - 在空间方向上，采用与**JPEG**类似的算法去掉空间冗余数据
  - 在时间方向上，采用**移动补偿(motion compensation)算法**去掉时间冗余数据

- MPEG专家组为此开发了两项重要技术

  - 定义了视频数据的结构

    - 把视频片段看成一系列静态图像的序列：

      - 把**视频序列分成许多像组**(group of picture，GOP)
      - 把**像组中每一帧图像分成许多像片**(slice)，每个像片由16行组成
      - 把**像片分成16行×16像素/行的宏块**(macroblock)
      - 把**宏块分成若干个8行×8像素/行的图块**(block)
      - 使用子采样格式为`4:2:0`时，一个**宏块**由4个**亮度(Y)图块**和2个**色度图块**(Cb和Cr)组成

      ![image-20240608162302331](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608162302331.png) 

      

  - 定义了三种类型的图像

    - 三种类型图像，采用三种不同算法分别对它们压缩

      - **帧内图像I (intra-picture)**，简称I图像或I帧(I-picture / I-frame)
        - 包含内容完整的图像，**用于为其他帧图像的编码和解码作参考**，称为**关键帧**
      - **预测图像P (predicted picture)**，简称P图像或P帧(P-picture / P-frame)
        - 以在它之前出现的帧内图像I作参考的图像，**对预测图像P进行编码就是对它们之间的差值进行编码**
      - **双向预测图像B (bidirectionally-predictive picture)**，也称双向插值图像B，简称B图像或B帧(B-picture/B-frame) 
        - 以在它之前和之后的帧图像(I和P)作参考的图像，**对B进行编码就是对帧内图像I和预测图像P的差值分别进行编码**

      ![image-20240608162651530](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608162651530.png) 



- 由于MPEG对视频信号作随机存取的重要要求，**有必要每隔一段时间传送1帧只采用帧内编码的图像作为参考图像**，使得预测环路能在某一参考帧丢失后，迅速获得另一个参考帧，从而恢复到正常工作状态
- **GOP**：两个**I帧**之间的图像构成一个组称为GOP (Group of Picture)



#### 2.帧内图像I的压缩编码算法

![image-20240608162948759](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608162948759.png) 

![image-20240608163017093](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608163017093.png) 



#### 3.预测图像P的压缩编码算法

![image-20240608163034268](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608163034268.png) 

![image-20240608163126878](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608163126878.png) 

![image-20240608163205724](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608163205724.png) 

![image-20240608163215303](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608163215303.png) 

![image-20240608163226889](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608163226889.png) 

![image-20240608163235472](C:\Users\MI\AppData\Roaming\Typora\typora-user-images\image-20240608163235472.png) 







