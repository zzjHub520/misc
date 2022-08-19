# [ELK学习笔记之filebeat合并多行日志示例](https://www.cnblogs.com/JetpropelledSnake/p/11418218.html)

**阅读目录**

- [0x00 概述](https://www.cnblogs.com/JetpropelledSnake/p/11418218.html#_label0)
- [0x01 Java堆栈日志](https://www.cnblogs.com/JetpropelledSnake/p/11418218.html#_label1)
- [0x02 C风格的日志](https://www.cnblogs.com/JetpropelledSnake/p/11418218.html#_label2)
- [0x03 时间戳](https://www.cnblogs.com/JetpropelledSnake/p/11418218.html#_label3)
- [0x04 应用程序事件](https://www.cnblogs.com/JetpropelledSnake/p/11418218.html#_label4)
- [参考1](https://www.cnblogs.com/JetpropelledSnake/p/11418218.html#_label5)
- [参考2](https://www.cnblogs.com/JetpropelledSnake/p/11418218.html#_label6)

## 0x00 概述

本节中的示例包括以下内容：

- 将Java堆栈跟踪日志组合成一个事件
- 将C风格的日志组合成一个事件
- 结合时间戳处理多行事件

同理，你可以把如下的正则应用在容器的yaml文件内。

 

## 0x01 Java堆栈日志

### Java示例一：

Java堆栈跟踪由多行组成，每一行在初始行之后以空格开头，如本例中所述:

```log
Exception in thread "main" java.lang.NullPointerException
        at com.example.myproject.Book.getTitle(Book.java:16)
        at com.example.myproject.Author.getBookTitles(Author.java:25)
        at com.example.myproject.Bootstrap.main(Bootstrap.java:14)
```

要将这些行整合到Filebeat中的单个事件中，请使用以下多行配置：

```
multiline.pattern: '^[[:space:]]'
multiline.negate: false
multiline.match: after
```

此配置将以空格开头的所有行合并到上一行。

 

### Java示例二：

下面是一个Java堆栈跟踪日志，稍微复杂的例子：

[![复制代码](MarkDownImages/ELK%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0%E4%B9%8Bfilebeat%E5%90%88%E5%B9%B6%E5%A4%9A%E8%A1%8C%E6%97%A5%E5%BF%97%E7%A4%BA%E4%BE%8Bpretty.assets/copycode.gif)](javascript:void(0);)

```
Exception in thread "main" java.lang.IllegalStateException: A book has a null property
       at com.example.myproject.Author.getBookIds(Author.java:38)
       at com.example.myproject.Bootstrap.main(Bootstrap.java:14)
Caused by: java.lang.NullPointerException
       at com.example.myproject.Book.getId(Book.java:22)
       at com.example.myproject.Author.getBookIds(Author.java:35)
       ... 1 more
```

[![复制代码](MarkDownImages/ELK%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0%E4%B9%8Bfilebeat%E5%90%88%E5%B9%B6%E5%A4%9A%E8%A1%8C%E6%97%A5%E5%BF%97%E7%A4%BA%E4%BE%8Bpretty.assets/copycode.gif)](javascript:void(0);)

要将这些行整合到Filebeat中的单个事件中，请使用以下多行配置：

```
multiline.pattern: '^[[:space:]]+(at|\.{3})\b|^Caused by:'
multiline.negate: false
multiline.match: after
```

此配置解释如下：

- 将以空格开头的所有行合并到上一行
- 并把以Caused by开头的也追加到上一行

 

## 0x02 C风格的日志

一些编程语言在一行末尾使用反斜杠(\)字符，表示该行仍在继续，如本例中所示:

```
printf ("%10.10ld  \t %10.10ld \t %s\
  %f", w, x, y, z );
```

要将这些行整合到Filebeat中的单个事件中，请使用以下多行配置：

```
multiline.pattern: '\\$'
multiline.negate: false
multiline.match: before
```

此配置将以\字符结尾的任何行与后面的行合并。

 

## 0x03 时间戳

来自Elasticsearch等服务的活动日志通常以时间戳开始，然后是关于特定活动的信息，如下例所示：

```
[2019-08-24 11:49:14,389][INFO ][env                      ] [Letha] using [1] data paths, mounts [[/
(/dev/disk1)]], net usable_space [34.5gb], net total_space [118.9gb], types [hfs]
```

要将这些行整合到Filebeat中的单个事件中，请使用以下多行配置：

```
multiline.pattern: '^\[[0-9]{4}-[0-9]{2}-[0-9]{2}'
multiline.negate: true
multiline.match: after
# 此配置使用negate: true和match: after设置来指定任何不符合指定模式的行都属于上一行。
```

 

## 0x04 应用程序事件

有时您的应用程序日志包含以自定义标记开始和结束的事件，如以下示例：

```
[2019-08-24 11:49:14,389] Start new event
[2019-08-24 11:49:14,395] Content of processing something
[2019-08-24 11:49:14,399] End event
```

要在Filebeat中将其整合为单个事件，请使用以下多行配置：

```
multiline.pattern: 'Start new event'
multiline.negate: true
multiline.match: after
multiline.flush_pattern: 'End event'
```

此配置把指定字符串开头，指定字符串结尾的多行合并为一个事件。

 

0x05 拓展知识

filebeat和logstash的合并方式几乎无区别

[![复制代码](MarkDownImages/ELK%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0%E4%B9%8Bfilebeat%E5%90%88%E5%B9%B6%E5%A4%9A%E8%A1%8C%E6%97%A5%E5%BF%97%E7%A4%BA%E4%BE%8Bpretty.assets/copycode.gif)](javascript:void(0);)

```
input {
    file {
        path => "/var/*.log"
        codec => multiline {
            pattern => "^\[\d{2}-"
            negate => true
            what => "previous"
        }
    }
}
# what确定合并属于上一个事件还是下一个事件，可以为next和previous
# 而filebeat对应的是multiline.match: after和before
```

[![复制代码](MarkDownImages/ELK%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0%E4%B9%8Bfilebeat%E5%90%88%E5%B9%B6%E5%A4%9A%E8%A1%8C%E6%97%A5%E5%BF%97%E7%A4%BA%E4%BE%8Bpretty.assets/copycode.gif)](javascript:void(0);)

这是一个传承的关系：

因为logstash是jvm跑的，资源消耗比较大，所以后来作者又用golang写了一个功能较少但是资源消耗也小的轻量级的logstash-forwarder。不过作者只是一个人，加入elastic以后，因为elastic本身还收购了另一个开源项目packetbeat，而这个项目专门就是用golang的，有整个团队，所以elastic干脆把logstash-forwarder的开发工作也合并到同一个golang团队来搞，于是新的项目就叫filebeat了。

 