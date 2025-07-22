# Configure and setup libraries
message(STATUS "Configuring Libraries...")

# -----------------------------------------------------------------------------------------------------------------

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# Threading
find_package(Threads REQUIRED)

# Fetch GLAD
CPMAddPackage(
        NAME glad
        GITHUB_REPOSITORY Dav1dde/glad
        VERSION 0.1.34
        OPTIONS "GLAD_GENERATOR c;GLAD_PROFILE core;GLAD_API gl=4.6"
)

# GLFW3
CPMAddPackage(
        NAME glfw
        GITHUB_REPOSITORY glfw/glfw
        GIT_TAG 3.4
        OPTIONS
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BUILD_DOCS OFF"
)

# GLM
CPMAddPackage(
        NAME glm
        GITHUB_REPOSITORY g-truc/glm
        VERSION 1.0.1
)

# ImGui
CPMAddPackage(
        NAME imgui
        GITHUB_REPOSITORY ocornut/imgui
        VERSION 1.92.1
)

# spdlog
CPMAddPackage(
        NAME spdlog
        GITHUB_REPOSITORY gabime/spdlog
        VERSION 1.15.3
)

# stb
CPMAddPackage(
        NAME stb
        GITHUB_REPOSITORY nothings/stb
        GIT_TAG master
)

# Create interface library for STB
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})

# -----------------------------------------------------------------------------------------------------------------

# Check if target exists before configuring
if(TARGET ${PROJECT_NAME})
    target_include_directories(${PROJECT_NAME} PRIVATE
            ${glad_SOURCE_DIR}
            ${glfw_SOURCE_DIR}/include
            ${glm_SOURCE_DIR}
            ${imgui_SOURCE_DIR}
            ${imgui_SOURCE_DIR}/backends
    )

    target_sources(${PROJECT_NAME} PRIVATE
            ${imgui_SOURCE_DIR}/imgui.cpp
            ${imgui_SOURCE_DIR}/imgui_demo.cpp
            ${imgui_SOURCE_DIR}/imgui_draw.cpp
            ${imgui_SOURCE_DIR}/imgui_tables.cpp
            ${imgui_SOURCE_DIR}/imgui_widgets.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    )

    # Link libraries
    target_link_libraries(${PROJECT_NAME} PRIVATE
            ${CMAKE_DL_LIBS}
            OpenGL::GL
            glad
            glfw
            Threads::Threads
            spdlog::spdlog
            stb
    )
else()
    message(FATAL_ERROR "Target ${PROJECT_NAME} does not exist. Make sure to define your target before including this script.")
endif()

# -----------------------------------------------------------------------------------------------------------------