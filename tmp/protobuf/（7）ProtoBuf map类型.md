# [（七）ProtoBuf map类型](https://www.cnblogs.com/infodriven/p/16246646.html)

protocol buffers支持map类型定义。

## 一、map语法

```cpp
map<key_type, value_type> map_field = N;
```

key_type可以是任何整数或字符串类型（除浮点类型和字节之外的任何标量类型）。请注意，枚举不是有效的key_type。
value_type 可以是除另一个映射之外的任何类型。

## 二、map的例子

```go
syntax = "proto3";
message Product
{
    string name = 1; // 商品名
    // 定义一个k/v类型，key是string类型，value也是string类型
    map<string, string> attrs = 2; // 商品属性，键值对
}
```

Map 字段不能使用repeated关键字修饰。

分类: [Protobuf](https://www.cnblogs.com/infodriven/category/2151382.html)