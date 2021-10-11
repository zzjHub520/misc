

# 安装zookeeper



![image-20211011230916395](kafka的Linux单机安装.assets/image-20211011230916395.png)

![image-20211011231130392](kafka的Linux单机安装.assets/image-20211011231130392.png)

![image-20211011231228015](kafka的Linux单机安装.assets/image-20211011231228015.png)

![image-20211011231617345](kafka的Linux单机安装.assets/image-20211011231617345.png)

![image-20211011231702974](kafka的Linux单机安装.assets/image-20211011231702974.png)

![image-20211011231738050](kafka的Linux单机安装.assets/image-20211011231738050.png)

可以Ctrl+c退出来



---

# kafka的安装



![image-20211011231949295](kafka的Linux单机安装.assets/image-20211011231949295.png)

![image-20211011232210531](kafka的Linux单机安装.assets/image-20211011232210531.png)

![image-20211011232312559](kafka的Linux单机安装.assets/image-20211011232312559.png)

![image-20211011232525387](kafka的Linux单机安装.assets/image-20211011232525387.png)



- 另外打开一个命令行窗口，对他进行测试

![image-20211011232716635](kafka的Linux单机安装.assets/image-20211011232716635.png)

![image-20211011232819736](kafka的Linux单机安装.assets/image-20211011232819736.png)



---

# 测试

![image-20211011233104576](kafka的Linux单机安装.assets/image-20211011233104576.png)

```
./bin/kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test
```

- 打开一个producer

```
./bin/kafka-console-producer.sh --broker-list localhost:9092 --topic test
```

![image-20211011233557680](kafka的Linux单机安装.assets/image-20211011233557680.png)



- 另外一个窗口打开consumer

```
./bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic test --
```

![image-20211011233812483](kafka的Linux单机安装.assets/image-20211011233812483.png)

![image-20211011233930622](kafka的Linux单机安装.assets/image-20211011233930622.png)





![image-20211011234029340](kafka的Linux单机安装.assets/image-20211011234029340.png)