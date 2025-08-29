cmake_minimum_required(VERSION 3.10)
project(TicTacToe CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Wno-sign-compare)
endif()

# Build only the files that must be compiled (the others are likely #included)
add_executable(tictactoe
  main.cpp
  PvCPU.cpp
  coin.cpp      
  arcade.cpp 
)

# Optional: tweak Easy mode probability without editing code
set(PVCU_EASY_SMART_P "0.10" CACHE STRING "Probability (0..1) Easy takes win/block")
target_compile_definitions(tictactoe PRIVATE PVCU_EASY_SMART_P=${PVCU_EASY_SMART_P})

# Optional extra executables if you need them (only if you compile them alone)
# add_executable(pvcpu_test PvCPU_sanity.cpp PvCPU.cpp)
# add_executable(pvai_demo pvai_demo.cpp PvCPU.cpp)

# Valgrind
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)             
add_compile_options(-g -O0 -fno-inline)  

