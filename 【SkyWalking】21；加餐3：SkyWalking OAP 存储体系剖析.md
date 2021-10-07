### 介绍Model与底层ES索引之间的映射关系

![image-20211007230945505](【SkyWalking】21；加餐3：SkyWalking OAP 存储体系剖析.assets/image-20211007230945505.png)

![image-20211007231033550](【SkyWalking】21；加餐3：SkyWalking OAP 存储体系剖析.assets/image-20211007231033550.png)

在server-core模块中，对整个持久化层有一个整天的抽象，具体的位置如下

![image-20211007231351899](【SkyWalking】21；加餐3：SkyWalking OAP 存储体系剖析.assets/image-20211007231351899.png)

上述的这些，持久化插件都是在此基础上进行了扩展，首先OAP存储了两种类型的数据：时间相关的数据和非时间相关的数据（与“时序”这个专有名词区分一下）

注册到OAP集群的Service、ServiceInstance以及同步的EndpointName、NetworkAddress都是非时间相关的数据，一个稳定的服务产生的这些数据是有限的

可以用几个固定的ES索引来存储这些数据，时间相关的数据会随着时间越来越大，而这设计显然不能落地的，一般会考虑切分，常见的切分方式按照时间窗口以及DownSampling进行切分，这里简单介绍DownSample，翻译为向下采样

![image-20211007233257241](【SkyWalking】21；加餐3：SkyWalking OAP 存储体系剖析.assets/image-20211007233257241.png)



**Model与ES索引**

![image-20211007233833023](【SkyWalking】21；加餐3：SkyWalking OAP 存储体系剖析.assets/image-20211007233833023.png)

我们回到server-core模块继续分析，常见的orm框架，会将数据中的表、结构映射为Java类，表中的一行数据会映射成一个Java Bean对象，在OAP的存储抽象中，也有类似的操作，skywalking会将







### 介绍 ModelInstaller是如何在OAP启动时初始化ES索引的





### 介绍OAP对不同持久化数据的抽象，以及对应的DAO层设计



### 介绍定期删除过期数据的核心原理