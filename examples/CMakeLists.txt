cmake_minimum_required(VERSION 3.10.2)

project("examples")

# External libraries
add_library( skyway-linux-core STATIC IMPORTED )
set_target_properties( skyway-linux-core
        PROPERTIES
        IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/libskyway-linux-core.a)

add_library( skyway-linux-room STATIC IMPORTED )
set_target_properties( skyway-linux-room
        PROPERTIES
        IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/libskyway-linux-room.a)

# List of definitions
set( SKYWAY_LINUX_DEFINITIONS
        WEBRTC_LINUX=1 
        WEBRTC_POSIX=1)

# List of libs
set( SKYWAY_LINUX_LIBS
        skyway-linux-room
        skyway-linux-core
        pthread
        atomic 
        avcodec 
        X11 
        glib-2.0 
        gio-2.0
        gobject-2.0
        dl)

# List of includes
set( SKYWAY_LINUX_INCLUDES 
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/external/libmediasoupclient/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/external/libmediasoupclient/deps/libsdptransform/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/external/libwebrtc
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/external/libskyway/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/external/libwebrtc/third_party/abseil-cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/external/libwebrtc/third_party/boringssl/src/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/external/boost
        ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_subdirectory("quickstart")
