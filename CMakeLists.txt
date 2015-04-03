#cmake ver req
cmake_minimum_required(VERSION 2.8.3)

if(NOT CMAKE_BUILD_TYPE )
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Select if you want to build Debug or Release" FORCE )
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  #for static libs 
 
set(project_name plantguns)
project(${project_name})

#Set source files.
set(source_files
    src/main.cpp
    src/plantguns.cpp
    src/entity.cpp
    src/player.cpp
    src/lodepng.cpp
    src/level.cpp
    src/directionresolver.cpp
    src/plant.cpp
    src/pickup.cpp
)

set(header_files
    src/plantguns.hpp
    src/entity.hpp
    src/player.hpp
    src/lodepng.hpp
    src/texturemaker.hpp
    src/level.hpp
    src/directionresolver.hpp
    src/plant.hpp
    src/pickup.hpp
)

#C++11 required
if(NOT MSVC)
    set(CPP_11_FLAG -std=c++11)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPP_11_FLAG}")

find_package(Featherkit COMPONENTS sdl2 ui rendering structure REQUIRED)
if(FEATHERKIT_FOUND)
    include_directories(${FEATHERKIT_INCLUDE_DIRS})
endif()

find_package(GLM REQUIRED)
if(GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIR})
endif()

#build
add_executable(${project_name} ${header_files} ${source_files})
target_link_libraries(${project_name} ${FEATHERKIT_LIBRARIES})
