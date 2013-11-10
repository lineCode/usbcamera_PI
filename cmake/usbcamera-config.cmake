# component_temp CMake config file
#
# This file sets the following variables:
# component_temp_FOUND - Always TRUE.
# component_temp_INCLUDE_DIRS - Directories containing the component_temp include files.
# component_temp_IDL_DIRS - Directories containing the component_temp IDL files.
# component_temp_LIBRARIES - Libraries needed to use component_temp.
# component_temp_DEFINITIONS - Compiler flags for component_temp.
# component_temp_VERSION - The version of component_temp found.
# component_temp_VERSION_MAJOR - The major version of component_temp found.
# component_temp_VERSION_MINOR - The minor version of component_temp found.
# component_temp_VERSION_REVISION - The revision version of component_temp found.
# component_temp_VERSION_CANDIDATE - The candidate version of component_temp found.

message(STATUS "Found component_temp-1.0.0")
set(component_temp_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(component_temp_INCLUDE_DIRS
#    "/usr/local/include/usbcamera-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(component_temp_IDL_DIRS
#    "/usr/local/include/usbcamera-1/idl")
set(component_temp_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(component_temp_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(component_temp_LIBRARIES
        "/usr/local/components/lib/libusbcamera.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(component_temp_LIBRARIES
        "/usr/local/components/lib/libusbcamera.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(component_temp_DEFINITIONS ${<dependency>_DEFINITIONS})

set(component_temp_VERSION 1.0.0)
set(component_temp_VERSION_MAJOR 1)
set(component_temp_VERSION_MINOR 0)
set(component_temp_VERSION_REVISION 0)
set(component_temp_VERSION_CANDIDATE )

