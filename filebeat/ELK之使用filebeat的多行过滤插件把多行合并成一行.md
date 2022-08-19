# ELK之使用filebeat的多行过滤插件把多行合并成一行

 原创

[minseo](https://blog.51cto.com/u_13045706)2021-09-10 13:51:45博主文章分类：[ELKStack](https://blog.51cto.com/u_13045706/category6)©著作权

***文章标签\*[正则表达式](https://blog.51cto.com/topic/regular-expression.html)[显示不全](https://blog.51cto.com/topic/xianshibuquan.html)[java](https://blog.51cto.com/topic/java.html)[运行日志](https://blog.51cto.com/topic/yunxingrizhi.html)[重启](https://blog.51cto.com/topic/chongqi.html)*****文章分类\*[IT职场](https://blog.51cto.com/nav/career)[其它](https://blog.51cto.com/nav/other)*****阅读数\**\*965\****

　　java运行日志一般有多行，格式类似如下

![ELK之使用filebeat的多行过滤插件把多行合并成一行_正则表达式](MarkDownImages/ELK%E4%B9%8B%E4%BD%BF%E7%94%A8filebeat%E7%9A%84%E5%A4%9A%E8%A1%8C%E8%BF%87%E6%BB%A4%E6%8F%92%E4%BB%B6%E6%8A%8A%E5%A4%9A%E8%A1%8C%E5%90%88%E5%B9%B6%E6%88%90%E4%B8%80%E8%A1%8C.assets/watermark,size_16,text_QDUxQ1RP5Y2a5a6i,color_FFFFFF,t_30,g_se,x_10,y_10,shadow_20,type_ZmFuZ3poZW5naGVpdGk=.png)

　　格式为：日期 + 日志级别 + 日志信息 有些日志是多行的，需要使用filebeat多行插件把多行合并成一行

　　未使用多行插件的日志格式

![ELK之使用filebeat的多行过滤插件把多行合并成一行_重启_02](MarkDownImages/ELK%E4%B9%8B%E4%BD%BF%E7%94%A8filebeat%E7%9A%84%E5%A4%9A%E8%A1%8C%E8%BF%87%E6%BB%A4%E6%8F%92%E4%BB%B6%E6%8A%8A%E5%A4%9A%E8%A1%8C%E5%90%88%E5%B9%B6%E6%88%90%E4%B8%80%E8%A1%8C.assets/watermark,size_16,text_QDUxQ1RP5Y2a5a6i,color_FFFFFF,t_30,g_se,x_10,y_10,shadow_20,type_ZmFuZ3poZW5naGVpdGk=-16609249195111.png)

　　修改filebeat配置文件/etc/filebeat/filebeat.yml 在原来基础上面添加多行合并配置

```python
  multiline:
      pattern: '^\d{4}-\d{1,2}-\d{1,2}\s\d{1,2}:\d{1,2}:\d{1,2}'
      negate: true
      match: after
1.2.3.4.
```

![ELK之使用filebeat的多行过滤插件把多行合并成一行_显示不全_03](MarkDownImages/ELK%E4%B9%8B%E4%BD%BF%E7%94%A8filebeat%E7%9A%84%E5%A4%9A%E8%A1%8C%E8%BF%87%E6%BB%A4%E6%8F%92%E4%BB%B6%E6%8A%8A%E5%A4%9A%E8%A1%8C%E5%90%88%E5%B9%B6%E6%88%90%E4%B8%80%E8%A1%8C.assets/watermark,size_16,text_QDUxQ1RP5Y2a5a6i,color_FFFFFF,t_30,g_se,x_10,y_10,shadow_20,type_ZmFuZ3poZW5naGVpdGk=-16609249195122.png)

- pattern：正则表达式，匹配日志格式
- negate：默认为false，暗示匹配pattern的行归并到上一行；true暗示不匹配pattern的行归并到上一行
- match：after暗示归并到上一行的末端，before暗示归并到上一行的行首

　　重启filebeat

```python
systemctl restart filebeat
1.
```

　　收集的日志格式为（多行已经合并）

![ELK之使用filebeat的多行过滤插件把多行合并成一行_正则表达式_04](MarkDownImages/ELK%E4%B9%8B%E4%BD%BF%E7%94%A8filebeat%E7%9A%84%E5%A4%9A%E8%A1%8C%E8%BF%87%E6%BB%A4%E6%8F%92%E4%BB%B6%E6%8A%8A%E5%A4%9A%E8%A1%8C%E5%90%88%E5%B9%B6%E6%88%90%E4%B8%80%E8%A1%8C.assets/watermark,size_16,text_QDUxQ1RP5Y2a5a6i,color_FFFFFF,t_30,g_se,x_10,y_10,shadow_20,type_ZmFuZ3poZW5naGVpdGk=-16609249195133.png)

　　如果在页面显示不全可以单击此处

![ELK之使用filebeat的多行过滤插件把多行合并成一行_显示不全_05](MarkDownImages/ELK%E4%B9%8B%E4%BD%BF%E7%94%A8filebeat%E7%9A%84%E5%A4%9A%E8%A1%8C%E8%BF%87%E6%BB%A4%E6%8F%92%E4%BB%B6%E6%8A%8A%E5%A4%9A%E8%A1%8C%E5%90%88%E5%B9%B6%E6%88%90%E4%B8%80%E8%A1%8C.assets/watermark,size_16,text_QDUxQ1RP5Y2a5a6i,color_FFFFFF,t_30,g_se,x_10,y_10,shadow_20,type_ZmFuZ3poZW5naGVpdGk=-16609249195134.png)

 