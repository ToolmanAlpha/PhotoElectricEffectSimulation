cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME Photo_Electric_Effect_Simulation)

project(${PROJECT_NAME})

# if (NOT CMAKE_BUILD_TYPE)
#     set(CMAKE_BUILD_TYPE Debug)
# endif()

find_package(SFML 2 REQUIRED COMPONENTS graphics system window)

if(WIN32)
    set(WIN32_GUI WIN32)
endif()


file (GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${WIN32_GUI} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "include")
set(SFML_LIBS sfml-graphics sfml-window sfml-system)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBS})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})