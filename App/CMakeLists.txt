# /root/App/


# Create the executable target
# TODO: Glob this?
#add_executable(App ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
add_executable(App)


# Include the roo-engine headers
target_include_directories(App PUBLIC ${CMAKE_SOURCE_DIR}/roo-engine/src)


# Link with roo-engine
target_link_libraries(App PRIVATE roo-engine)


# Add source files recursively
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)


# Add sources to the executable
target_sources(App PRIVATE ${APP_SOURCES})


# Set the output directory for the executable
set_target_properties(App PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/App
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/App
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/App
)


# Call the create_source_groups function to mirror the 
# source folder structure as source_groups (filters) in Visual Studio
create_source_groups(${CMAKE_CURRENT_SOURCE_DIR}/src "src" ${APP_SOURCES})
