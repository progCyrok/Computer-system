cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
project(computers)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES app_structure/main_window/main.cpp
        app_structure/main_window/events.h
        autorization/autorization_objects.h
        app_structure/main_window/main_objects.h
        app_structure/main_window/work_with_json.h
        app_structure/other_func/creating_computer.h
        app_structure/add_new_computer/monitor_create.h
        app_structure/add_new_computer/create_objects.h
        app_structure/main_window/main_monitor.h
)


add_executable(Start ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${SFML_INCLUDE_DIRS})
include_directories(/opt/homebrew/Cellar/mesa/23.3.2/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch arm64")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -arch arm64")
# Указываем флагов для линковки
target_link_options(Start PUBLIC -Wl,-search_paths_first -Wl,-headerpad_max_install_names)
target_link_libraries(Start PRIVATE sfml-graphics sfml-audio ${OPENGL_gl_LIBRARY} ${OPENGL_LIBRARIES} -L/opt/homebrew/Cellar/sfml/2.6.1/include/SFML/)