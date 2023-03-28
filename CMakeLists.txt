set(LIB_NAME app-version)

add_library(${LIB_NAME} INTERFACE)

target_sources(
    ${LIB_NAME}
    INTERFACE
        src/averVersion.h
        src/averVersion.c
        # ${CMAKE_CURRENT_BINARY_DIR}/averUserVersion.h
)

target_include_directories(
    ${LIB_NAME}
    INTERFACE
        src
        ${CMAKE_CURRENT_BINARY_DIR}
)

check_python_packages( ${CMAKE_CURRENT_SOURCE_DIR}/tools )

function(generate_app_version input_target)
    add_custom_command(
        OUTPUT  
            ${CMAKE_CURRENT_BINARY_DIR}/averUserVersion.h
        COMMAND 
            ${Python3_EXECUTABLE} ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/tools/genVersion.py
        COMMENT
            "Generate Version: "
    )

    add_custom_target(
        ${input_target}User
        ALL
        DEPENDS
            ${CMAKE_CURRENT_BINARY_DIR}/averUserVersion.h
    )

    add_dependencies(${input_target} ${input_target}User)
endfunction(generate_app_version traget)

generate_app_version(${LIB_NAME})

