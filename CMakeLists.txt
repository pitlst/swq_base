#------------------初始部分------------------
# 要求并设置cmake的最低版本，版本不符合要求不允许编译
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
# 设置项目名
set(PROJECT_NAME swq_base)
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
    set(CMAKE_BUILD_TYPE "Debug")
endif()
# 可选：设置opencv的库路径
# set(OpenCV_DIR "/home/cheakf/Downloads/opencv-4.6.0/build")
# 指定头文件在对应的文件夹中寻找
include_directories(include)


#------------------编译部分------------------
# 搜索src下源文件存入DIR_SRCS变量
FILE (GLOB M_SRCS "src/*.cpp")
# 找到所有声明，保存到变量里
FILE (GLOB M_INCLUDES "include/*.h")
# 找到需要的依赖
find_package(OpenCV REQUIRED)
find_package(PythonInterp REQUIRED)

# 导入头文件
include_directories(${OpenCV_INCLUDE_DIRS})
# 生成目标可执行文件
add_executable(test_json ${PROJECT_SOURCE_DIR}/test/test_json.cpp ${PROJECT_SOURCE_DIR}/include/swq_json.h ${PROJECT_SOURCE_DIR}/include/swq_utils.h)
add_executable(test_xml ${PROJECT_SOURCE_DIR}/test/test_xml.cpp ${PROJECT_SOURCE_DIR}/include/swq_xml.h ${PROJECT_SOURCE_DIR}/include/swq_utils.h)
add_executable(test_ini ${PROJECT_SOURCE_DIR}/test/test_ini.cpp ${PROJECT_SOURCE_DIR}/include/swq_ini.h ${PROJECT_SOURCE_DIR}/include/swq_utils.h)
add_executable(test_string ${PROJECT_SOURCE_DIR}/test/test_string.cpp ${PROJECT_SOURCE_DIR}/include/swq_string.h ${PROJECT_SOURCE_DIR}/include/swq_utils.h)
add_executable(test_high_num ${PROJECT_SOURCE_DIR}/test/test_high_num.cpp ${PROJECT_SOURCE_DIR}/include/swq_high_num.h)
# 链接动态库
# target_link_libraries(test_json PRIVATE pthread ${OpenCV_LIBS})
# target_link_libraries(test_xml PRIVATE pthread ${OpenCV_LIBS})
# target_link_libraries(test_ini PRIVATE pthread ${OpenCV_LIBS})
# target_link_libraries(test_string PRIVATE pthread ${OpenCV_LIBS})
# target_link_libraries(test_high_num PRIVATE pthread ${OpenCV_LIBS})
# 开启测试
enable_testing()
# 为对应的目标运行脚本生成测试用文件
add_custom_target(run_json
    COMMAND  echo "The json file required for the test starts to be generated."
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/script/generation_json.py ${CMAKE_CURRENT_SOURCE_DIR}
)
add_dependencies(test_json run_json)
add_custom_target(run_xml
    COMMAND  echo "The xml file required for the test starts to be generated."
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/script/generation_xml.py ${CMAKE_CURRENT_SOURCE_DIR}
)
add_dependencies(test_xml run_xml)

#------------------测试部分------------------
add_test(NAME test_json COMMAND test_json)
add_test(NAME test_xml COMMAND test_xml)
add_test(NAME test_ini COMMAND test_ini)
add_test(NAME test_string COMMAND test_string)
add_test(NAME test_high_num COMMAND test_high_num)


