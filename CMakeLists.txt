cmake_minimum_required(VERSION 3.14)

project (annotations_meta)
set(CMAKE_BUILD_TYPE Release)

EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
MESSAGE("Detected ${ARCHITECTURE} architecture")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(gst_detectionmetas SHARED gstdetectionsmeta.cpp)
add_library(gst_trackedmetas SHARED gsttrackedmeta.cpp)

# Gstreamer linkage
include(${CMAKE_ROOT}/Modules/FindPkgConfig.cmake)

# Set CMAKE_C_FLAGS variable with info from pkg-util
execute_process(COMMAND pkg-config --cflags gstreamer-1.0
                OUTPUT_VARIABLE CMAKE_C_FLAGS)
string(REPLACE "\n" "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
message("CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")

# Set CMAKE_EXE_LINKER_FLAGS variable with info from pkg-util

execute_process(COMMAND pkg-config --libs gstreamer-1.0
                OUTPUT_VARIABLE CMAKE_EXE_LINKER_FLAGS)
string(REPLACE "\n" "" CMAKE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})
message("CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")

set_target_properties(gst_detectionmetas
                      PROPERTIES COMPILE_FLAGS ${CMAKE_C_FLAGS}
                                 LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})
set_target_properties(gst_trackedmetas
                      PROPERTIES COMPILE_FLAGS ${CMAKE_C_FLAGS}
                                 LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})

install(TARGETS gst_detectionmetas gst_trackedmetas LIBRARY DESTINATION "/usr/local/lib/" CONFIGURATIONS Release Debug)
install(FILES gsttrackedmeta.h gstdetectionsmeta.h DESTINATION "/usr/include/gstreamer-1.0/gst" CONFIGURATIONS Release Debug)