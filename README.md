# 学习 qt c++

## 0.项目目录

> 为了目录结构的清晰，需要重构一下项目目录

- Sources文件夹用于保存所有的qt源文件，在Sources下
    - Forms存放UI文件
    - Headers存放.h头文件
    - Resources存放.qrc以及资源文件
    - cpp文件直接放在Sources目录下
        - 将cpp里面导入ui的前面加上`Forms/`
        - 第一次会报错，但是编译后就可以正常运行了
        - 例如`#include "Forms/ui_MainWindow.h"`
- lib目录存放第三方库.dll文件和.a文件
- include目录存放第三方库的头文件

![项目目录](./docs/project_directory.png)

## 1.环境配置

> 需要知道qt的mingw73_64安装路径
> 例如：`C:/Qt/Qt5.14.2/5.14.2/mingw73_64`

0. 添加环境变量到qt的mingw73_64安装路径
1. 将clion的编译(锤子旁边的属性里面work路径改为qt的mingw73_64安装路径)

2. cmake需要自己添加下面的内容

```cmake
# 下面是qt的mingw73_64安装路径
set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.14.2/5.14.2/mingw73_64")
# 下面是添加额外参数
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
# 下面是导入的c++文件
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/Sources/Headers
)
# 下面一般clion会自动添加
# 其中resources.qrc需要自己添加
add_executable(${PROJECT_NAME}
        WIN32 # 不要运行程序时候出现黑色的命令行
        Sources/main.cpp
        Sources/mainwindow.cpp
        Sources/Headers/mainwindow.h
        Sources/Forms/mainwindow.ui
        Sources/Resources/resources.qrc
        )
```

3. cmake修改下面的内容
    - 若提示`Error copying file`，则修改下面的内容
    - 因为在windows下安装的qt的mingw73_64里面没有debug的dll文件
    - 也可能是clion没有更新，可以先看一下能不能正常运行

```cmake
set(DEBUG_SUFFIX "d")
#改为
set(DEBUG_SUFFIX "")
```

4. 点击运行即可运行程序

## 2.发布

```bash
# 将编译后的单独的exe文件复制到新的路径下
# 命令行输入
windeployqt xxx.exe
# 压缩后就可以发布
```