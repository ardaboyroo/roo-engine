# /root/

# Set the minimum required cmake version
cmake_minimum_required(VERSION 3.15)


project(roo-engine)


# Define the C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set the default library compilation to shared (dll/so)
set(BUILD_SHARED_LIBS ON)


# Set the configuration types to Debug and Release only
# By default RelWithDebInfo and MinSizeRel are also added
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)


# Enables use of folders for targets and hides the ALL_BUILD and ZERO_CHECK projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# Set the Visual Studio startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT App)


# Enable MultiProcess compile if supported
if(MSVC)
    add_compile_options(/MP)
endif()


# Function to create source groups (filters) dynamically for Visual Studio
function(create_source_groups base_path root_filter)
    file(TO_CMAKE_PATH ${base_path} normalized_base_path)
    foreach(source_file ${ARGN})
        file(RELATIVE_PATH relative_path "${base_path}" "${source_file}")
        get_filename_component(source_dir "${relative_path}" DIRECTORY)
        string(REPLACE "/" "\\" source_group_name "${source_dir}")
        if (source_group_name)
            # Add the root filter prefix
            source_group("${root_filter}\\${source_group_name}" FILES "${source_file}")
        else()
            # Files at the base path go directly under the root filter
            source_group("${root_filter}" FILES "${source_file}")
        endif()
    endforeach()
endfunction()


# Add the subdirectories to the project
add_subdirectory(roo-engine)
add_subdirectory(App)
