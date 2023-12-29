cmake_minimum_required(VERSION 3.26)
project(
    robosim
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

## Find dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
# find_package(imgui REQUIRED)  # 注释掉这一行
find_package(GLEW REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

set(SOURCES
    src/core/Application.cpp
    src/core/DhParam.cpp
    src/core/InverseKinematics.cpp
    src/core/JointedLink.cpp
    src/core/PidController.cpp
    src/core/Robot.cpp
    src/Main.cpp
    src/meshes/BoxMesh.cpp
    src/meshes/CylinderMesh.cpp
    src/meshes/JointedLinkMesh.cpp
    src/meshes/Mesh.cpp
    src/meshes/SphereMesh.cpp
    src/rendering/Camera.cpp 
)

set(IMGUI_SOURCES
    ${PROJECT_SOURCE_DIR}/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_demo.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/imgui
    ${PROJECT_SOURCE_DIR}/imgui/backends
    ${PROJECT_SOURCE_DIR}/lib/ImGuizmo
)

add_library(ImGuizmo lib/ImGuizmo/ImGuizmo.cpp)
target_link_libraries(
    ImGuizmo 
    PRIVATE
        # imgui::imgui
        # imgui::imgui_impl_glfw
        # imgui::imgui_impl_opengl3
        glfw
        GLEW::GLEW
)

add_executable(robosim ${SOURCES} ${IMGUI_SOURCES})

target_link_libraries(
    robosim
    PRIVATE
        OpenGL::GL
        dl
        glfw
        GLEW::GLEW
        # imgui::imgui
        # imgui::imgui_impl_glfw
        # imgui::imgui_impl_opengl3
        Eigen3::Eigen
        ImGuizmo
)

set_target_properties(robosim PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
