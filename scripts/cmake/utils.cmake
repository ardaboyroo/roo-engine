# Utility functions

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


# Function to assign third party libraries to 
# the Vendor filter in Visual Studio
function(assign_to_vendor_folder target)
    set_target_properties(${target} PROPERTIES FOLDER "Vendor")
endfunction()
