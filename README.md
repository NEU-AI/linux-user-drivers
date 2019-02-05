调用的代码参考main.cpp

可以放在QSplashScreen之前执行

# 编译方法
修改pro文件，在里面加选项，

```
unix: LIBS += -L$$OUT_PWD/libusd/ -lusd
#代表存放libusd.a文件的位置
#$$OUT_PWD宏等于编译输出的目录

INCLUDEPATH += $$PWD/libusd
#头文件的位置
#$$PWD等于工程所在目录
```
