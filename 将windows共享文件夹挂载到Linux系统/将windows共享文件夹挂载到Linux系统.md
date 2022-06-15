## 将windows共享文件夹挂载到Linux系统



2021-04-26 14:31



大家工作中有没有遇到windows系统的文件需要放到Linux系统中进行访问或者修改的情况呢？

通常情况下可以将文件直接上传到Linux系统进行操作，但是如果文件数量比较多的情况下，直接上传是很不方便的。而通过文件共享，在局域网内是可以很轻松的让Linux系统也能够访问并修改Windows系统中的文件。

说到文件共享，没接触过的可能不知道该怎么实现。Windows的文件共享在确保局域网内两个主机之间网络互通的情况下，需要以下几个步骤

设置共享账户添加共享文件夹配置文件夹权限客户端访问共享文件夹**设置共享账户**

很多同学为了图方便，共享账户都是直接使用的管理员账户来充当。但是这样是很不安全的，管理员账号的权限太大了，而且由于设置共享时是需要账户密码的，直接使用管理员账户等于是暴露了管理员的账户和密码（当然如果只是个人使用那就无所谓了）。所以，出于安全考虑，我们可以单独设置一个共享账户组和账户。

Windows系统中按下win+R，输入lusrmgr.msc打开本地用户和组配置窗口

![img](MarkDownImages/%E5%B0%86windows%E5%85%B1%E4%BA%AB%E6%96%87%E4%BB%B6%E5%A4%B9%E6%8C%82%E8%BD%BD%E5%88%B0Linux%E7%B3%BB%E7%BB%9F.assets/faf2b2119313b07e9822e83013f7f92b97dd8c17.png)

新建cifss账户组

![img](MarkDownImages/%E5%B0%86windows%E5%85%B1%E4%BA%AB%E6%96%87%E4%BB%B6%E5%A4%B9%E6%8C%82%E8%BD%BD%E5%88%B0Linux%E7%B3%BB%E7%BB%9F.assets/d31b0ef41bd5ad6eabfb83bfa7eb51d3b6fd3c09.png)

新建cifs账户

![img](MarkDownImages/%E5%B0%86windows%E5%85%B1%E4%BA%AB%E6%96%87%E4%BB%B6%E5%A4%B9%E6%8C%82%E8%BD%BD%E5%88%B0Linux%E7%B3%BB%E7%BB%9F.assets/9345d688d43f8794f9a291dbcd3b66fc1ad53a8a.png)

修改用户组为cifss，默认新建用户是属于Users组的，Users账户组是有登录系统的权限的，而我们只是要共享文件夹，并不希望这个新账户能登录系统，所以这里要改为我们新建的cifss组。

除了这个方法外，也可以执行gpedit.msc打开组策略，然后依次找到计算机配置—Windows设置—安全设置—本地策略—用户权限分配—拒绝本地登录，添加cifs账户即可。

![img](MarkDownImages/%E5%B0%86windows%E5%85%B1%E4%BA%AB%E6%96%87%E4%BB%B6%E5%A4%B9%E6%8C%82%E8%BD%BD%E5%88%B0Linux%E7%B3%BB%E7%BB%9F.assets/8c1001e93901213ff0c7d6fb74c75ed92e2e95cd.png)

为cifs账户设置密码

![img](MarkDownImages/%E5%B0%86windows%E5%85%B1%E4%BA%AB%E6%96%87%E4%BB%B6%E5%A4%B9%E6%8C%82%E8%BD%BD%E5%88%B0Linux%E7%B3%BB%E7%BB%9F.assets/10dfa9ec8a1363275b27947eb6afc8e409fac759.png)

**添加共享文件夹**

选中文件夹，右键选择属性

![img](MarkDownImages/%E5%B0%86windows%E5%85%B1%E4%BA%AB%E6%96%87%E4%BB%B6%E5%A4%B9%E6%8C%82%E8%BD%BD%E5%88%B0Linux%E7%B3%BB%E7%BB%9F.assets/0824ab18972bd407cf73b9a35ba9f6590eb309e4.png)

在共享页面选择高级共享

![img](MarkDownImages/%E5%B0%86windows%E5%85%B1%E4%BA%AB%E6%96%87%E4%BB%B6%E5%A4%B9%E6%8C%82%E8%BD%BD%E5%88%B0Linux%E7%B3%BB%E7%BB%9F.assets/4a36acaf2edda3cc4ec4324f1ec95109213f9261.png)

勾选共享此文件夹，并设置权限

![img](MarkDownImages/%E5%B0%86windows%E5%85%B1%E4%BA%AB%E6%96%87%E4%BB%B6%E5%A4%B9%E6%8C%82%E8%BD%BD%E5%88%B0Linux%E7%B3%BB%E7%BB%9F.assets/203fb80e7bec54e756e5b658a618f3584fc26a17.png)

**配置文件夹权限**

要想让客户端能够正常访问共享文件，除了设置共享权限，还需要对文件夹添加对应用户的权限。

文件夹属性选择依次选择安全—编辑

![img](MarkDownImages/%E5%B0%86windows%E5%85%B1%E4%BA%AB%E6%96%87%E4%BB%B6%E5%A4%B9%E6%8C%82%E8%BD%BD%E5%88%B0Linux%E7%B3%BB%E7%BB%9F.assets/4d086e061d950a7b6a8e496c15f10ad1f3d3c983.png)

点击添加，输入要添加权限的用户或用户组，单击确定

![img](MarkDownImages/%E5%B0%86windows%E5%85%B1%E4%BA%AB%E6%96%87%E4%BB%B6%E5%A4%B9%E6%8C%82%E8%BD%BD%E5%88%B0Linux%E7%B3%BB%E7%BB%9F.assets/ac6eddc451da81cba0100f3d4d46b81e08243170.png)

选中新添加的用户或用户组，勾选相应的权限，单击应用—确定即可。

![img](MarkDownImages/%E5%B0%86windows%E5%85%B1%E4%BA%AB%E6%96%87%E4%BB%B6%E5%A4%B9%E6%8C%82%E8%BD%BD%E5%88%B0Linux%E7%B3%BB%E7%BB%9F.assets/0823dd54564e925884f3013ea9a2b950cebf4ec7.png)

**客户端访问共享文件夹**

Windows系统直接使用\\IP

的方式访问即可。

![img](MarkDownImages/%E5%B0%86windows%E5%85%B1%E4%BA%AB%E6%96%87%E4%BB%B6%E5%A4%B9%E6%8C%82%E8%BD%BD%E5%88%B0Linux%E7%B3%BB%E7%BB%9F.assets/0bd162d9f2d3572c1cd83ad695330b2f62d0c3ae.png)

![img](MarkDownImages/%E5%B0%86windows%E5%85%B1%E4%BA%AB%E6%96%87%E4%BB%B6%E5%A4%B9%E6%8C%82%E8%BD%BD%E5%88%B0Linux%E7%B3%BB%E7%BB%9F.assets/9922720e0cf3d7caf3ac38ceed3fd6016a63a9dc.png)

Linux系统，需要使用mount命令对共享文件加进行挂载

首先创建一个/share目录为挂载点

\# mkdir /share

然后使用mount命令通过以下格式进行挂载，挂载时需要添加前面设置的用户名和密码信息

\# mount -t cifs -o username=cifs,password=1 //1.0.1.1/repo /share/

接下来使用df -h命令查看挂载状态，可以看到/share目录挂载了一个5T容量的共享设备

![img](MarkDownImages/%E5%B0%86windows%E5%85%B1%E4%BA%AB%E6%96%87%E4%BB%B6%E5%A4%B9%E6%8C%82%E8%BD%BD%E5%88%B0Linux%E7%B3%BB%E7%BB%9F.assets/35a85edf8db1cb13d6987ba2fb743e4693584bb2.png)

进入对应的目录，使用ls命令已经可以正常查看到目录中的内容

![img](MarkDownImages/%E5%B0%86windows%E5%85%B1%E4%BA%AB%E6%96%87%E4%BB%B6%E5%A4%B9%E6%8C%82%E8%BD%BD%E5%88%B0Linux%E7%B3%BB%E7%BB%9F.assets/0b55b319ebc4b745241f8f7deedc761f8b8215fd.png)

Windows文件夹共享就介绍到这里，有疑问的可以文章下面留言。