# [（二）ProtoBuf定义消息](https://www.cnblogs.com/infodriven/p/16246584.html)

消息（message），在protobuf中指的就是我们定义的数据结构。

## 一、语法

```makefile
syntax = "proto3";

message 消息名 {
    消息体
}
```

syntax关键词定义使用的是proto3语法版本，如果没有指定默认使用的是proto2。
message关键词，标记开始定义一个消息，消息体，用于定义各种字段类型。

```undefined
提示： protobuf消息定义的语法结构，跟我们平时接触的各种语言的类定义，非常相似。
```

例子：

```go
syntax = "proto3";

message SearchRequest {
  string query = 1;
  int32 page_number = 2;
  int32 result_per_page = 3;
}
```

定义了一个SearchRequest消息，这个消息有3个字段，query是字符串类型，page_number和result_per_page是int32类型。

```undefined
提示：我们通常将protobuf消息定义保存在.proto为后缀的文件中。
```

## 二、字段类型

支持多种数据类型，例如：string、int32、double、float等等，下一章节会详细介绍

## 三、分配标识号

通过前面的例子，在消息定义中，每个字段后面都有一个唯一的数字，这个就是标识号。
这些标识号是用来在消息的二进制格式中识别各个字段的，一旦开始使用就不能够再改变，每个消息内唯一即可，不同的消息定义可以拥有相同的标识号。

```css
注意：[1,15]之内的标识号在编码的时候会占用一个字节。[16,2047]之内的标识号则占用2个字节。所以应该为那些频繁出现的消息元素保留 [1,15]之内的标识号。切记：要为将来有可能添加的、频繁出现的字段预留一些标识号。
```

**保留标识号（Reserved）**
如果你想保留一些标识号，留给以后用，可以使用下面语法：

```fsharp
message Foo {
  reserved 2, 15, 9 to 11; // 保留2，15，9到11这些标识号
}
```

如果使用了这些保留的标识号，protocol buffer编译器会输出警告信息。

## 四、注解

往.proto文件添加注释，支持C/C++/java风格的双斜杠（//） 语法格式。
例子：

```go
// 定义SearchRequest消息
message SearchRequest {
  string query = 1;
  int32 page_number = 2;  // 页码
  int32 result_per_page = 3;  // 分页大小
}
```

## 五、为消息定义包

我们也可以为消息定义包。
例子：

```go
package foo.bar;
message Open { ... }
```

定义了一个包：foo.bar

## 六、选项

下面是一些常用的选项：

- java_package # 单独为java定义包名字。
- java_outer_classname # 单独为java定义，protobuf编译器生成的类名。

1. 将消息编译成各种语言版本的类库
   编译器命令格式：

```css
protoc [OPTION] PROTO_FILES
```

OPTION是命令的选项, PROTO_FILES是我们要编译的proto消息定义文件，支持多个。
常用的OPTION选项：

```ini
  --cpp_out=OUT_DIR           指定代码生成目录，生成 C++ 代码
  --csharp_out=OUT_DIR        指定代码生成目录，生成 C# 代码
  --java_out=OUT_DIR          指定代码生成目录，生成 java 代码
  --js_out=OUT_DIR            指定代码生成目录，生成 javascript 代码
  --objc_out=OUT_DIR          指定代码生成目录，生成 Objective C 代码
  --php_out=OUT_DIR           指定代码生成目录，生成 php 代码
  --python_out=OUT_DIR        指定代码生成目录，生成 python 代码
  --ruby_out=OUT_DIR          指定代码生成目录，生成 ruby 代码
```

例子:

```lua
protoc --java_out=. demo.proto
```

在当前目录导出java版本的代码，编译demo.proto消息。
有些语言需要单独安装插件才能编译proto，例如golang
安装go语言的protoc编译器插件

```go
go get -u github.com/golang/protobuf/protoc-gen-go
```

注意: 安装go语言插件后，需要将 $GOPATH/bin 路径加入到PATH环境变量中。
编译成go语言版本

```lua
protoc --go_out=. helloworld.proto
```

分类: [Protobuf](https://www.cnblogs.com/infodriven/category/2151382.html)