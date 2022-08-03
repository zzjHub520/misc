# [（六）ProtoBuf消息嵌套](https://www.cnblogs.com/infodriven/p/16246639.html)

我们在各种语言开发中类的定义是可以互相嵌套的，也可以使用其他类作为自己的成员属性类型。
在protobuf中同样支持消息嵌套，可以在一个消息中嵌套另外一个消息，字段类型可以是另外一个消息类型。

## 一、引用其他消息类型的用法

```java
// 定义Result消息
message Result {
  string url = 1;
  string title = 2;
  repeated string snippets = 3; // 字符串数组类型
}

// 定义SearchResponse消息
message SearchResponse {
  // 引用上面定义的Result消息类型，作为results字段的类型
  repeated Result results = 1; // repeated关键词标记，说明results字段是一个数组
}
```

## 二、消息嵌套

类似类嵌套一样，消息也可以嵌套。
例子:

```java
message SearchResponse {
  // 嵌套消息定义
  message Result {
    string url = 1;
    string title = 2;
    repeated string snippets = 3;
  }
  // 引用嵌套的消息定义
  repeated Result results = 1;
}
```

## 三、import导入其他proto文件定义的消息

我们在开发一个项目的时候通常有很多消息定义，都写在一个proto文件，不方便维护，通常会将消息定义写在不同的proto文件中，在需要的时候可以通过import导入其他proto文件定义的消息。
例子:
保存文件: result.proto

```csharp
syntax = "proto3";
// Result消息定义
message Result {
  string url = 1;
  string title = 2;
  repeated string snippets = 3; // 字符串数组类型
}
```

保存文件: search_response.proto

```java
syntax = "proto3";
// 导入Result消息定义
import "result.proto";

// 定义SearchResponse消息
message SearchResponse {
  // 使用导入的Result消息
  repeated Result results = 1; 
}
```

分类: [Protobuf](https://www.cnblogs.com/infodriven/category/2151382.html)