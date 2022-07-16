## 问题：如何在任何目录下通过鼠标右键新建 Typora 文件？

### 共有 6 步：

 

\1. 打开注册表：

![img](MarkDownImages/%E5%8F%B3%E9%94%AE%E8%8F%9C%E5%8D%95%E8%B0%83%E5%87%BAmarkdown.assets/1231521-20200321125757340-1267166762.png)

 

 

 

\2. 定位 HKEY_CLASSES_ROOT\Directory\Background\shell 目录，建议手动从根目录下一级级查找，系统查找注册表很慢。

![img](MarkDownImages/%E5%8F%B3%E9%94%AE%E8%8F%9C%E5%8D%95%E8%B0%83%E5%87%BAmarkdown.assets/1231521-20200321130243652-1331097503.png)

![img](MarkDownImages/%E5%8F%B3%E9%94%AE%E8%8F%9C%E5%8D%95%E8%B0%83%E5%87%BAmarkdown.assets/1231521-20200321125853583-297056415.png)

 

 

\3. 在 shell 上右键新建 “项”，取名为 Typora

![img](MarkDownImages/%E5%8F%B3%E9%94%AE%E8%8F%9C%E5%8D%95%E8%B0%83%E5%87%BAmarkdown.assets/1231521-20200321130516963-2005396345.png)

 

 

 

\4. 双击 Typora 右边窗口的默认文件，填写 Typora 字符串，表示鼠标右键时显示的文件名称。

![img](MarkDownImages/%E5%8F%B3%E9%94%AE%E8%8F%9C%E5%8D%95%E8%B0%83%E5%87%BAmarkdown.assets/1231521-20200321131247458-1540711534.png)

 

 

\5. 鼠标右键 Typora 文件夹选择新建字符串值，命名为 icon ，表示添加图标，双击 icon 文件填写 Typora.exe 文件安装路径，

  我的路径为： D:\Program Files (x86)\开发者工具\Typora\Typora.exe

![img](MarkDownImages/%E5%8F%B3%E9%94%AE%E8%8F%9C%E5%8D%95%E8%B0%83%E5%87%BAmarkdown.assets/1231521-20200321131617597-1731163840.png)

结果如图：

 

 

 ![img](MarkDownImages/%E5%8F%B3%E9%94%AE%E8%8F%9C%E5%8D%95%E8%B0%83%E5%87%BAmarkdown.assets/1231521-20200321131815619-1118243286.png)

 

 

 

\6. 在 Typora 目录上右键选择新建项，命名为 command， 双击右边窗口的默认文件，填写文件路径

　　注意路径格式不同于 icon 中的路径。注意：路径中的双引号不能少，表示字符串。

![img](MarkDownImages/%E5%8F%B3%E9%94%AE%E8%8F%9C%E5%8D%95%E8%B0%83%E5%87%BAmarkdown.assets/1231521-20200321132221590-256902230.png)

 

 ![img](MarkDownImages/%E5%8F%B3%E9%94%AE%E8%8F%9C%E5%8D%95%E8%B0%83%E5%87%BAmarkdown.assets/1231521-20200321132246093-852205145.png)

 

 

到此，大功告成！！！