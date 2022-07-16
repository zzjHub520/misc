# [Typora添加右键新建Markdown文件](https://www.cnblogs.com/zhoujiayingvana/p/12357812.html)

## 前言

某一天，当我更新了最新版的typora之后，忽然发现，原来设置的右键`新建`里面`新建.md文件`没了？！

按照网上给注册表`.md`项里面添加`ShellNew`项和`Nullfile`值的方法竟然也不行！？

阅教程无数，终于在知乎上面看到了一个方法并且成功了...感谢知乎！

[来源](https://www.zhihu.com/question/267616299/answer/998709318)

## 方法

新建一个`txt`文本文件，写入：

```csharp
Windows Registry Editor Version 5.00

[HKEY_CLASSES_ROOT\.md]
@="Typora.md"
"Content Type"="text/markdown"
"PerceivedType"="text"

[HKEY_CLASSES_ROOT\.md\ShellNew]
"NullFile"=""
```

然后修改`.txt`后缀为`.reg` 的注册表文件。

然后双击运行。

## 几点说明

这个方法要先安装`Typora`。如果不安装`Typora`，只是导入上述注册表，在很久以前是可以生效的，但自从某次`Windows`更新之后就失效了，之后的 Windows 要求`[HKEY__ROOT\.md]`项的`@ 值 xxx`必须对应于注册表项`[HKEY_CLASSES_ROOT\xxx]`，这里填写`Typora.md`，是因为`Typora `已经为我们生成了`[HKEY_CLASSES_ROOT\Typora.md]`，可以不用再重入导入，这个项的`@ 值`代表右键新建该类型的名称显示。如果是自定义其他的类型，则必须导入一遍，比如要添加`.py`类型，一个最简的注册表如下:

```csharp
Windows Registry Editor Version 5.00

[HKEY_CLASSES_ROOT\.py]
@="PythonFile"

[HKEY_CLASSES_ROOT\.py\ShellNew]
"NullFile"=""

[HKEY_CLASSES_ROOT\PythonFile]
@="Python 脚本"
```

## 可能遇到的问题

右键新建markdown文件以后，可能会发现文件有几十MB那么大。

解决方法：`win+R`打开“运行”输入`regedit`打开注册表，打开路径`\HKEY_CLASSES_ROOT\.md\ShellNew`

删除多余的文件（尤其是有一个什么Markdown File），只保留如下的两项。然后关闭注册表，即可修复bug

![img](MarkDownImages/Typora%E6%B7%BB%E5%8A%A0%E5%8F%B3%E9%94%AE%E6%96%B0%E5%BB%BAMarkdown%E6%96%87%E4%BB%B6.assets/1604093-20200225234950391-1983577441.png)

