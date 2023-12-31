cmake_minimum_required(VERSION 3.14)
project(main)

set(CMAKE_VERBOSE_MAKEFILE ON)

# Allegro 5
include(FetchContent)
FetchContent_Declare(
        allegro5
        GIT_REPOSITORY https://github.com/liballeg/allegro5.git
        GIT_TAG        5.2.8.0
)
FetchContent_GetProperties(allegro5)
FetchContent_Populate(allegro5)

# Allegro 4
include(FetchContent)
FetchContent_Declare(
        allegro4
        GIT_REPOSITORY https://github.com/humbertodias/Allegro-Legacy
        GIT_BRANCH        master
)
FetchContent_GetProperties(allegro4)
if(NOT allegro4_POPULATED)
    FetchContent_Populate(allegro4)
    if (MSVC)
        set(SHARED ON)
    else()
        set(SHARED OFF)
    endif()
    set(MAGIC_MAIN ON)
    set(STRICT_WARN OFF)
    add_subdirectory(${allegro4_SOURCE_DIR} ${allegro4_BINARY_DIR})
endif()

# main code
add_executable(${PROJECT_NAME} main-win.cpp)

# include
message("
allegro5_SOURCE_DIR: ${allegro5_SOURCE_DIR}/include allegro5_BINARY_DIR: ${allegro5_BINARY_DIR}/include
allegro4_SOURCE_DIR: ${allegro4_SOURCE_DIR}/include allegro4_BINARY_DIR: ${allegro4_BINARY_DIR}/include
")

target_include_directories(${PROJECT_NAME} PUBLIC 
${allegro5_SOURCE_DIR}/include ${allegro5_BINARY_DIR}/include
${allegro4_SOURCE_DIR}/include ${allegro4_BINARY_DIR}/include
)

# Link with dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE allegro -L${allegro4_BINARY_DIR}/lib)

# These include files are typically copied into the correct places via allegro's install
# target, but we do it manually.
file(COPY ${allegro5_SOURCE_DIR}/misc/Allegro5_iOS/allegro5/platform/alplatf.h DESTINATION ${allegro4_SOURCE_DIR}/include/allegro5/platform)
# Addons
file(COPY ${allegro5_SOURCE_DIR}/addons/audio/allegro5/allegro_audio.h DESTINATION ${allegro4_SOURCE_DIR}/include/allegro5)
file(COPY ${allegro5_SOURCE_DIR}/addons/font/allegro5/allegro_font.h DESTINATION ${allegro4_SOURCE_DIR}/include/allegro5)
file(COPY ${allegro5_SOURCE_DIR}/addons/primitives/allegro5/allegro_primitives.h DESTINATION ${allegro4_SOURCE_DIR}/include/allegro5)
file(COPY ${allegro5_SOURCE_DIR}/addons/image/allegro5/allegro_image.h DESTINATION ${allegro4_SOURCE_DIR}/include/allegro5)
file(COPY ${allegro5_SOURCE_DIR}/addons/acodec/allegro5/allegro_acodec.h DESTINATION ${allegro4_SOURCE_DIR}/include/allegro5)
