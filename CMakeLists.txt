cmake_minimum_required(VERSION 3.0.0)
project(DGD VERSION 0.1.0)

# set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR})

if(APPLE)
  message(STATUS "Building on Apple")
  set(GUI_TYPE MACOSX_BUNDLE)
  find_package(SDL2 REQUIRED)
  include_directories(include /usr/local/include/SDL2)
endif(APPLE)
if(MSVC)
  message(STATUS "Building on MSVC")
  set(GUI_TYPE WIN32)
  if(NOT DEFINED ENV{SDL2_INCLUDE})
    message(FATAL_ERROR "not defined environment variable:SDL2_INCLUDE")
  endif()
  include_directories(include $ENV{SDL2_INCLUDE})
endif(MSVC)
if(MINGW)
  message(STATUS "Building on MinGW")
  set(GUI_TYPE WIN32)
  if(NOT DEFINED ENV{SDL2_INCLUDE})
    message(FATAL_ERROR "not defined environment variable:SDL2_INCLUDE")
  endif()
  include_directories(include $ENV{SDL2_INCLUDE})
endif(MINGW)
if(UNIX AND NOT APPLE)
  message(STATUS "Building on Unix")
  find_package(SDL2 REQUIRED)
  include_directories(include ${SDL2_INCLUDE_DIRS})
endif()

link_directories(lib)
find_library(SDL2_LIB SDL2)
find_library(SDL2_IMAGE_LIB SDL2_image)
find_library(SDL2_TTF_LIB SDL2_ttf)
find_library(SDL2_MIXER_LIB SDL2_mixer)
mark_as_advanced(SDL2_LIB SDL2_IMAGE_LIB SDL2_TTF_LIB SDL2_MIXER_LIB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_THREAD_SAFE")
set(SOURCES main.cpp src/display.cpp src/errors.cpp)
set(HEADER_FILES include/display.h include/errors.h)

add_subdirectory(3rd-party/spdlog)
find_package(spdlog REQUIRED)

add_subdirectory(3rd-party/libconfig/lib)
include_directories(3rd-party/libconfig/lib)
find_package(libconfig REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB})
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIB})
target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIB})
target_link_libraries(${PROJECT_NAME} ${SDL2_MIXER_LIB})
target_link_libraries(${PROJECT_NAME} spdlog config++)
# target_include_directories(${PROJECT_NAME} ${LIBCONFIG_INCLUDE_DIRS})

if(MINGW)
  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different
      "${PROJECT_SOURCE_DIR}/lib/SDL2.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif(MINGW)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
