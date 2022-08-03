# [（一）ProtoBuf入门教程](https://www.cnblogs.com/infodriven/p/16246467.html)

在网络通信和通用数据交换等应用场景中经常用的技术是JSON和XML，本教程介绍另外一个数据交换的协议工具ProtoBuf。

## 一、简介

protocol buffers （ProtoBuf）是一种语言无关、平台无关、可扩展的序列化结构数据的方法，它可用于（数据）通信协议、数据存储等。
Protocol Buffers 是一种灵活，高效，自动化机制的结构数据序列化方法－可类比 XML，但是比 XML 更小（3 ~ 10倍）、更快（20 ~ 100倍）、更为简单。
json\xml都是基于文本格式，protobuf是二进制格式。
你可以通过 ProtoBuf 定义数据结构，然后通过 ProtoBuf 工具生成各种语言版本的数据结构类库，用于操作 ProtoBuf 协议数据
本教程介绍的是最新的protobuf proto3版本的语法。

## 二、使用ProtoBuf的例子

### 2.1 创建.proto文件，定义数据结构

使用 ProtoBuf ，首先需要通过 ProtoBuf 语法定义数据结构(消息)，这些定义好的数据结构保存在.proto为后缀的文件中。
例子:
文件名: response.proto

```go
// 指定protobuf的版本，proto3是最新的语法版本
syntax = "proto3";

// 定义数据结构，message 你可以想象成java的class，c语言中的struct
message Response {
  string data = 1;   // 定义一个string类型的字段，字段名字为data, 序号为1
  int32 status = 2;   // 定义一个int32类型的字段，字段名字为status, 序号为2
}
说明：proto文件中，字段后面的序号，不能重复，定义了就不能修改，可以理解成字段的唯一ID。
```

### 2.2 安装ProtoBuf编译器

protobuf的github发布地址： https://github.com/protocolbuffers/protobuf/releases
protobuf的编译器叫protoc，在上面的网址中找到最新版本的安装包，下载安装。
这里下载的是：protoc-3.9.1-win64.zip ， windows 64位系统版本的编译器，下载后，解压到你想要的安装目录即可。

```bash
提示：安装完成后，将 [protoc安装目录]/bin 路径添加到PATH环境变量中
```

打开cmd，命令窗口执行protoc命令，没有报错的话，就已经安装成功。

### 2.3 vscode安装ProtoBuf插件

```undefined
vscode-proto3
```

### 2.4 将.proto文件，编译成指定语言类库

protoc编译器支持将proto文件编译成多种语言版本的代码，我们这里以java为例。
切换到proto文件所在的目录, 执行下面命令

```lua
protoc --java_out=. response.proto
```

然后在当前目录生成了一个ResponseOuterClass.java的java类文件，这个就是我们刚才用protobuf语法定义的数据结构对应的java类文件，通过这个类文件我们就可以操作定义的数据结构。

### 2.6 在代码中使用ProtoBuf对数据进行序列化和反序列化

因为上面的例子使用的是java, 我们先导入protobuf的基础类库。
maven：

```xml
<dependency>
            <groupId>com.google.protobuf</groupId>
            <artifactId>protobuf-java</artifactId>
            <version>3.9.1</version>
</dependency>
```

使用ProtoBuf的例子。

```java
ResponseOuterClass.Response.Builder builder = ResponseOuterClass.Response.newBuilder();
// 设置字段值
builder.setData("hello www.tizi365.com");
builder.setStatus(200);

 ResponseOuterClass.Response response = builder.build();
 // 将数据根据protobuf格式，转化为字节数组
 byte[] byteArray  = response.toByteArray();

// 反序列化,二进制数据
try {
    ResponseOuterClass.Response newResponse = ResponseOuterClass.Response.parseFrom(byteArray);
    System.out.println(newResponse.getData());
    System.out.println(newResponse.getStatus());
} catch (Exception e) {
 }
```