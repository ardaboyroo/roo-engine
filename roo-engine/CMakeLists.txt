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
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.15.0
)


# Fetch and build the libraries
FetchContent_MakeAvailable(spdlog)


# Statically link spdlog into roo-engine without exposing it to other targets
target_link_libraries(roo-engine PRIVATE spdlog::spdlog)


# Assign spdlog to the vendor filter
assign_to_vendor_folder(spdlog)


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
