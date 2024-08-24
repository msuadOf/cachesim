cmake_minimum_required(VERSION 3.10)  # 必须
set(CMAKE_CXX_STANDARD 14)	# C++14

project(app)  #工程名

include_directories("/usr/local/include/") # 头文件目录
include_directories("./include/") # 头文件目录
include_directories("./src/local-include/") # 头文件目录

link_directories("/usr/local/lib/") # 链接库目录

aux_source_directory(. SRCS) # 源文件
aux_source_directory(./src SRCS)

set(CMAKE_C_FLAGS "-O1") # 设置C工程的 CFLAGS
set(CMAKE_CXX_FLAGS "-O0 -Werror") # 设置C++ 工程的 CXX_FLAGS

add_executable(${PROJECT_NAME} ${SRCS}) # 生成可执行文件，这里程序名即为功能名

target_link_libraries(${PROJECT_NAME} pthread) # 链接库

# 下面使用install作为项目打包使用
set(CMAKE_INSTALL_PREFIX ./dist)  # 自定义安装目录，打包使用
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin) # 打包二进制文件

set(CONFIGS ${PROJECT_SOURCE_DIR}/hello.cf) 
install(FILES ${CONFIGS} DESTINATION config) # 打包配置文件

# 添加自定义目标 'run'
add_custom_target(run
  COMMENT "Running ${PROJECT_NAME}"
  COMMAND ${PROJECT_NAME}
  DEPENDS ${PROJECT_NAME}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMAND echo  "\n"
)