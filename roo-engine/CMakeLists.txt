# /root/roo-engine/


# Create the library target
add_library(roo-engine SHARED)


# Include directories for the engine's headers
target_include_directories(roo-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


# When building a shared library on windows the symbol information 
# will be build into a .lib file which then can be included
# however this needs to be turned on first
set_target_properties(roo-engine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)


# Add source files recursively
file(GLOB_RECURSE ROO_ENGINE_SOURCES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)


# Add sources to the library
target_sources(roo-engine PRIVATE ${ROO_ENGINE_SOURCES})


# Set the output directory for the library
set_target_properties(roo-engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Engine
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Engine
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Engine
)


# Include the FetchContent functions
include(FetchContent)


# Fetch third party libraries
# Fetch spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.15.0
)

# Fetch GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.3.8
)

# Fetch GLAD
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        v0.1.36
)

# Fetch ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.5
)


# Disable unnecessary features for GLFW
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

# Disable unnecessary features for GLAD
set(GLAD_INSTALL OFF)
set(GLAD_UNIFIED OFF)


# Fetch and build the libraries
FetchContent_MakeAvailable(spdlog)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glad)
FetchContent_MakeAvailable(imgui)


# Since ImGui doesn't support cmake we have to do it manually.
# Add ImGui sources as its own target
add_library(imgui STATIC 
    ${imgui_SOURCE_DIR}/imgui.h
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imstb_rectpack.h
    ${imgui_SOURCE_DIR}/imstb_textedit.h
    ${imgui_SOURCE_DIR}/imstb_truetype.h
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_internal.h
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
)


# Include ImGui directories
target_include_directories(imgui PUBLIC 
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${glfw_SOURCE_DIR}/include      # include glfw include directories since imgui depends on it
)


# Statically link the libraries into roo-engine without exposing it to other targets
target_link_libraries(roo-engine PRIVATE spdlog)
target_link_libraries(roo-engine PRIVATE glfw)
target_link_libraries(roo-engine PRIVATE glad)
target_link_libraries(roo-engine PRIVATE imgui)


# Assign the third party libraries to the vendor filter
assign_to_vendor_folder(spdlog)
assign_to_vendor_folder(glfw)
assign_to_vendor_folder(update_mappings)
assign_to_vendor_folder(glad)
assign_to_vendor_folder(glad-generate-files)
assign_to_vendor_folder(imgui)


# Call the create_source_groups function to mirror the 
# source folder structure as source_groups (filters) in Visual Studio
create_source_groups(${CMAKE_CURRENT_SOURCE_DIR}/src "src" ${ROO_ENGINE_SOURCES})


# Use precompiled headers for roo-engine
target_precompile_headers(roo-engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.hpp)


# Copy the roo-engine DLL to the App binary directory
add_custom_command(TARGET roo-engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:roo-engine>       # The DLL built by roo-engine
        ${CMAKE_BINARY_DIR}/bin/App/$<CONFIG>/$<TARGET_FILE_NAME:roo-engine>    # Destination directory
)
