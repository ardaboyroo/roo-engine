# /root/roo-engine/


# Create the library target
add_library(roo-engine)


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


# Call the create_source_groups function to mirror the 
# source folder structure as source_groups (filters) in Visual Studio
create_source_groups(${CMAKE_CURRENT_SOURCE_DIR}/src "src" ${ROO_ENGINE_SOURCES})
