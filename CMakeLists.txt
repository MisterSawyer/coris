cmake_minimum_required(VERSION 3.20)

project(coris CXX)

add_executable(${PROJECT_NAME}
    src/main.cpp

    src/coris.cpp
)
set(PUBLIC_HEADERS_LIST
    include/coris.h
)
target_include_directories(${PROJECT_NAME} PUBLIC include)

set_property(TARGET "${PROJECT_NAME}" PROPERTY CXX_STANDARD 23)
set_target_properties("${PROJECT_NAME}" PROPERTIES CXX_STANDARD 23)
set_target_properties("${PROJECT_NAME}" PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS_LIST}")
set_target_properties("${PROJECT_NAME}" PROPERTIES DEBUG_POSTFIX "_DEBUG")

if(DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(
        STATUS
        "CMAKE_INSTALL_PREFIX is not set\n"
        "Default value: ${CMAKE_INSTALL_PREFIX}\n"
        "Will set it to ${CMAKE_SOURCE_DIR}/install"
    )
    set(CMAKE_INSTALL_PREFIX
        "${CMAKE_SOURCE_DIR}/install"
        CACHE PATH "Where the library will be installed to" FORCE
    )
else()
    message(
        STATUS
        "CMAKE_INSTALL_PREFIX was already set\n"
        "Current value: ${CMAKE_INSTALL_PREFIX}"
    )
endif()

install(TARGETS "${PROJECT_NAME}" EXPORT "${PROJECT_NAME}Targets"
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}                             # bin
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}                             # lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}                             # lib
    #PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}   # include/coris
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}                        # include
)
