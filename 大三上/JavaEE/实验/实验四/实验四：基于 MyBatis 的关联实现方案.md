# 实验四：基于 MyBatis 的关联实现方案

## 实验要求

![1.png](https://s2.loli.net/2024/10/29/C3luTOAIHUj5tnE.png)



## 如何使用 JMeter 对已有的两个 API 进行测试

1. 已有的两个 API 描述链接如上，测试前先打开本地的 JMeter 文件夹，找到 bin 目录下的 jmeter 批处理文件，双击运行

![1.png](https://s2.loli.net/2024/10/29/8MwHV3GJIBXYKiT.png)



2. 一小段时间后命令行出现如下内容，jmeter 图形化界面会自动打开

![1.png](https://s2.loli.net/2024/10/29/qICPKb46zUSEs2B.png)

![1.png](https://s2.loli.net/2024/10/29/AwVIeWx62MXNzZm.png)



3. 打开 JavaEE 的工程文件夹，按以下路径打开文件 **ReadProduct1.jmx** 

![1.png](https://s2.loli.net/2024/10/29/wOYloMc3LryCi8u.png) 

![1.png](https://s2.loli.net/2024/10/29/vq4eBUOCH8YQukP.png)

![1.png](https://s2.loli.net/2024/10/29/ZUqPBV7JrGSaow9.png)

## 注意是 ReadProduct1.jmx，不是ReadProduct.jmx

![2.png](https://s2.loli.net/2024/10/29/fDwlCIP4kEgiNt7.png)



4. 在图形化界面上选择访问哪个 API 接口，**当 `type=auto` 表示访问的 Dao层关联；当 `type=manual` 表示 MyBatis 关联。**

![1.png](https://s2.loli.net/2024/10/29/tZT9gSR6L2oBu7M.png)

![1.png](https://s2.loli.net/2024/10/29/C3luTOAIHUj5tnE.png)



5. 设置好type 后，打开 terminus ，访问 **test** 节点（上次实验 JMeter 是部署在 test 服务器上的），按照下图将需要的文件扔到服务器上。**注意：`name.csv` 文件应该已经有了，这时候只用传配好 API 路径的 `ReadProduct1.jmx` 文件。**

![1.png](https://s2.loli.net/2024/10/29/Hep3TFM2EY56wi1.png)



在服务器的 test 文件夹里看到有了对应的文件

![1.png](https://s2.loli.net/2024/10/29/TnbPqQBE1lNoV8c.png)



6. 输入命令：`vim ReadProduct1.jmx ` 编辑 `ReadProduct1.jmx`

![1.png](https://s2.loli.net/2024/10/29/gF7ZavRPI5i1yjK.png)

![1.png](https://s2.loli.net/2024/10/29/yO1DvduULpZzWSb.png)



7. 在 test 服务器上运行 JMeter 测试命令：`jmeter -n -t ReadProduct1.jmx -l read1-100-10-1.jtl -e -o read1/read1-100-10-1` ，**这条命令的 `read1-100-10-1.jtl` 和 `read1/read1-100-10-1` 的数字分别对应线程数、测试时间、loop 次数。**然后就可以在 test 服务器上的 read1 文件夹中找到 html 文件，拿到本机上看即可

![1.png](https://s2.loli.net/2024/10/29/T7jydmhrWNoVZUp.png)

![2.png](https://s2.loli.net/2024/10/29/uNUCTgkBliEJVaI.png)

![3.png](https://s2.loli.net/2024/10/29/8NgOdMpfn6j4uVR.png)



拿到本地后结果如下：

![1.png](https://s2.loli.net/2024/10/29/kPonWdYSGmBjfqT.png)

