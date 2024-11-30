# /root/

# Set the minimum required cmake version
cmake_minimum_required(VERSION 3.29)


project(roo-engine)


# Define the C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


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


# Include personal utility functions
include(scripts/cmake/utils.cmake)


# Add the subdirectories to the project
add_subdirectory(roo-engine)
add_subdirectory(App)
