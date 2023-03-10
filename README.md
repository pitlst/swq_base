# swq_base

## 项目简介

本项目用于编写一些常用的脚手架库，像json文件的解析一类，方便使用和学习

## 项目结构

```shell
swq_base
├── build
├── doc
├── 3rdparty
├── include
├── src
├── tools
├── scripts
├── test
├── LICENSE
├── CMakeLists.txt
├── build.sh
├── .gitignore
├── readme.md
└── sample
```

- **build :** 用于存放build时cmake产生的中间文件，其包含子目录release和debug。
- **doc :** 用于存放项目的相关文档。
- **3rdparty :** 用于存放第三方库，每个第三库以单独目录的形式组织在3rdparty目录下。其中每个第三方目录下又有 `include` 和 `lib` 分别存放第三方库的头文件和库文件。
- **include :** 用于存放每个模块以及整个工程对外的头文件。具体格式如下文。
- **src :** 存放源码文件，以及内部头文件。具体格式如下文。
- **tools :** 包含一些支持项目构建的工具，如编译器等，一般情况下使用软链接。
- **scripts :** 包含一些脚本文件，如使用Jenkins进行自动化构建时所需要的脚本文件，以及一些用于预处理的脚本文件。
- **asset :** 用于一些用到的非代码文件的存放
- **test :** 分模块存放测试代码。
- **LICENSE :** 版权信息说明。
- **CMakeLists.txt :** cmake文件。
- **build.sh :** build脚本文件。
- **.gitignore :** 指明git忽略规则。
- **readme.md :** 存放工程说明文件。
- **sample :** 存放示例代码。

目前已经完成的是高精度浮点数，json解析，xml解析三个部分

正在编写的是自己的string和ini解析。

本项目尽量做到全源代码引用和不依赖第三方库。

本项目仅做过简单测试，详细单元测试没有覆盖。