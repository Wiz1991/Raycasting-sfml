cmake_minimum_required(VERSION 3.1)
project(Raycast VERSION 0.1.0)


find_package(SFML REQUIRED COMPONENTS network window graphics system)

add_subdirectory(include)
add_subdirectory(src)

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(Raycast sfml-graphics sfml-audio)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
