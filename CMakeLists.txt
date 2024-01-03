cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

project(origami VERSION 0.0)
add_library(origami STATIC)


# for glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("vendor/glfw")
add_subdirectory("vendor/glm")
add_subdirectory("vendor/glad")

find_package(spdlog REQUIRED)

file(GLOB_RECURSE sources src/*.cpp)
target_sources(origami PRIVATE ${sources})

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm
  )

# TODO: conditionally link platform-specific libs (-lGL -lX11 -lpthread -lXrandr -lXi -ldl)
target_link_libraries(origami spdlog::spdlog glfw glm glad)

IF (UNIX) 
  add_compile_definitions(PLATFORM_NIX)
# ELSEIF (APPLE)
#   add_compile_definitions(PLATFORM_APPLE)
# ELSEIF (WIN32)
#   add_compile_definitions(PLATFORM_WIN32)
ELSE ()
  message(FATAL_ERROR "Unsupported platform")
ENDIF ()
