cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(graphics)

file(GLOB SOURCE_FILES src/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES})

add_subdirectory(vendor/glew)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/spdlog)

configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

target_precompile_headers(${PROJECT_NAME} PUBLIC include/Core.h)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glew/include
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image
)

target_link_libraries(${PROJECT_NAME} glfw libglew_static spdlog)