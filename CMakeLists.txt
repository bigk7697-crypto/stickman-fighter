cmake_minimum_required(VERSION 3.16)
project(StickmanFighter VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouver les packages
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# GLAD (généré manuellement)
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# Fichiers source
file(GLOB_RECURSE SOURCES 
    src/*.cpp
    src/*.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    src
    external/glad/include
)

target_link_libraries(${PROJECT_NAME} 
    glfw
    glm::glm
    glad
    opengl32
)

# Copier les DLL si nécessaire (Windows)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:glfw>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
