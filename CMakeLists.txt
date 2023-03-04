# 要求并设置cmake的最低版本，版本不符合要求不允许编译
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
# 设置项目名
set(PROJECT_NAME cmake_study)
# 在这里直接指定项目为c++项目，节约查找tool chain的时间
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)
# 设置c++标准等级和编译后输出路径
set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
# 导出执行命令到json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# 强制化c++标准，当标准不符合要求时强制终止编译而不是采用更旧的标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# 设置默认的编译等级
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
# 可选：设置opencv的库路径
set(OpenCV_DIR "/home/cheakf/Downloads/opencv-4.6.0/build")
# 指定头文件在对应的文件夹中寻找
include_directories(include)
# 搜索src下源文件存入DIR_SRCS变量
FILE (GLOB M_SRCS "src/*.cpp")
# 找到所有声明，保存到变量里
FILE (GLOB M_INCLUDES "include/*.h")
# 找到需要的依赖
find_package(OpenCV REQUIRED)
# 导入头文件
include_directories(${OpenCV_INCLUDE_DIRS})
# 生成目标可执行文件
add_executable(${PROJECT_NAME} ${M_SRCS} ${M_INCLUDES})
# 链接动态库
target_link_libraries(${PROJECT_NAME} PRIVATE pthread ${OpenCV_LIBS})
