cmake_minimum_required(VERSION 3.25)
project(lifetime_exercise_generator LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)

add_executable(lifetime_exercise)
target_sources(lifetime_exercise
  PRIVATE
  main.cpp
)
target_include_directories(lifetime_exercise
  PRIVATE
  .
)