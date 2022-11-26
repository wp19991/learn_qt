cmake_minimum_required(VERSION 3.19)
project(learn_qt)

set(CMAKE_CXX_STANDARD 14)
# 添加c++额外参数
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

# 导入的头文件
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src/Headers
)

file(GLOB DIR "src/*.cpp" "src/Headers/*.h" "src/Forms/*.ui" "src/res/*.qrc")
add_executable(${PROJECT_NAME}
        WIN32 # 不要程序有黑色的命令行出现
        ${DIR})

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

