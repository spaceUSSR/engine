cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME engine)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/window.cpp
    src/window.h

#shader program files

    src/Renderer/ShaderProgram.h
    src/Renderer/ShaderProgram.cpp

    src/Renderer/texture.cpp
    src/Renderer/texture.h

#events file
    src/events.h
    src/events.cpp
    src/mouseevents.h
    src/keyboardevent.h

    src/camera.h
    src/camera.cpp
    )


# Lingk glfw library
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# Lingk glad library
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

# Lingk stb_image library
add_subdirectory(external/stb_image)
target_link_libraries(${PROJECT_NAME} stb_image)


# Lingk glm library
add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)

# Link assimp library
#add_subdirectory(external/assimp-5.0.1)
#target_link_libraries(${PROJECT_NAME} assimp)

# Copy output file
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
