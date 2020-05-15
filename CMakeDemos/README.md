# Modern CMake Demo

## 开始

### 本例子的CMake最低版本要求3.15.

Modern CMake的最低版本要求是3.0.0.

### 生成vs配置命令
```bat
cd CMakeDemos
cmake -S . -B build -G"Visual Studio 15 2017" -T v140 -A x64
```

## 文档结构
| 目录                | 释义              |
| --------------------| ---------------- |
| `cmake`             | cmake脚本        |
| `external`          | 第三方库目录      |
| `libs`              | 自定义库目录      |
| `Samples`           | 例子程序apps     |
| `CMakeLists.txt`    | 根目录cmake文件  |

### libs
- core  普通c++库
- utils Qt库

### Samples
- Demo 普通app，调用core库
- QWebSocket 普通Qt应用程序
- QDemo Qt应用程序，调用utils库

## 实现功能
- 基本c++源码布局管理，针对vs(个人平时最常用)
- 自动提取源文件
- 库自动导出符号
- 自定义库支持find_package
- vs runtime自动部署
- Qt自动moc
- Qt依赖自动部署
- 自动添加库和应用程序版本号

## TODO Lists
- 1.Qt库(utils)自动导出后，依赖编译出错，需要解决
- 2.cmake install