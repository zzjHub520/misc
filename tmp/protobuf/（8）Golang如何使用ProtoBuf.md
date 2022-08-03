# [（八）Golang如何使用ProtoBuf](https://www.cnblogs.com/infodriven/p/16246666.html)

本节介绍，在go语言中，如何是用protobuf对数据进行序列化和反序列化。

## 一、先参考protobuf快速入门章节安装protoc编译器

protoc快速入门

## 二、安装protoc-gen-go

安装针对go语言的编译器插件。

```go
go get -u github.com/golang/protobuf/protoc-gen-go
```

安装好了之后, 在$GOPATH/bin下面会找到protoc-gen-go，编译器插件，将$GOPATH/bin路径添加到PATH环境变量中。

## 三、安装protobuf包

使用protobuf需要先安装对应的包。

```bash
go get -u github.com/golang/protobuf
```

## 四、定义proto消息

例子：
文件名：score_server/score_info.proto

```go
syntax = "proto3";
option go_pacakge="./;score_server"
//option go_package="path;name"
//path表示生成go文件的存放地址，会自动生成目录。name表示生成的go文件所属包名。

package score_server;


// 基本的积分消息
message base_score_info_t{
    int32       win_count = 1;                  // 玩家胜局局数
    int32       lose_count = 2;                 // 玩家负局局数
    int32       exception_count = 3;            // 玩家异常局局数
    int32       kill_count = 4;                 // 总人头数
    int32       death_count = 5;                // 总死亡数
    int32       assist_count = 6;               // 总总助攻数
    int64       rating = 7;                     // 评价积分
}
```

## 五、编译proto文件，生成go代码

```mipsasm
cd score_server
protoc --go_out=. score_info.proto
```

## 六、测试代码

```go
package main

import (
	"fmt"
        // 导入protobuf依赖包
	"github.com/golang/protobuf/proto"
       // 导入我们刚才生成的go代码所在的包，注意你们自己的项目路径，可能跟本例子不一样
	"demo/score_server" 
)

func main() {
        // 初始化消息
	score_info := &score_server.BaseScoreInfoT{}
	score_info.WinCount = 10
	score_info.LoseCount = 1
	score_info.ExceptionCount = 2
	score_info.KillCount = 2
	score_info.DeathCount = 1
	score_info.AssistCount = 3
	score_info.Rating = 120

	// 以字符串的形式打印消息
	fmt.Println(score_info.String())

	// encode, 转换成二进制数据
	data, err := proto.Marshal(score_info)
	if err != nil {
		panic(err)
	}

	// decode, 将二进制数据转换成struct对象
	new_score_info := score_server.BaseScoreInfoT{}
	err = proto.Unmarshal(data, &new_score_info)
	if err != nil {
		panic(err)
	}

	// 以字符串的形式打印消息
	fmt.Println(new_score_info.String())
}
```

分类: [Protobuf](https://www.cnblogs.com/infodriven/category/2151382.html)