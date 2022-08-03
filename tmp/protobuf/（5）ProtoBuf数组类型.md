# [（五）ProtoBuf数组类型](https://www.cnblogs.com/infodriven/p/16246632.html)

在protobuf消息中定义数组类型，是通过在字段前面增加repeated关键词实现，标记当前字段是一个数组。

## 一、整数数组的例子：

```go
message Msg {
  // 只要使用repeated标记类型定义，就表示数组类型。
  repeated int32 arrays = 1;
}
```

## 二、字符串数组

```cmake
message Msg {
  repeated string names = 1;
}
```

分类: [Protobuf](https://www.cnblogs.com/infodriven/category/2151382.html)