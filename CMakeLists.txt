cmake_minimum_required (VERSION 2.8)

set(PROJECT_NAME "sdl2-opencv")

project(${PROJECT_NAME})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

execute_process(COMMAND
    ${CMAKE_COMMAND} -E remove_directory ${EXECUTABLE_OUTPUT_PATH}
)

set(SDL_LIBS
    "${CMAKE_SOURCE_DIR}/vendor/sdl2/lib/x86/SDL2.lib"
    "${CMAKE_SOURCE_DIR}/vendor/sdl2/lib/x86/SDL2main.lib"
)

find_package(OpenCV REQUIRED)

include_directories(
    vendor/sdl2/include
)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS}
    ${SDL_LIBS}
)

set(COPY_DLL
    "${CMAKE_SOURCE_DIR}/vendor/sdl2/lib/x86/SDL2.dll"
)

foreach(filepath ${COPY_DLL})
    get_filename_component(filename ${filepath} NAME)

    add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${filepath}" "${EXECUTABLE_OUTPUT_PATH}/$<CONFIGURATION>/${filename}"
    )
endforeach()

set(COPY_DLL
    "opencv_core310d.dll"
    "opencv_highgui310d.dll"
    "opencv_imgcodecs310d.dll"
    "opencv_imgproc310d.dll"
    "opencv_videoio310d.dll"
)

foreach(filename ${COPY_DLL})
    add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${OpenCV_DIR}/bin/$<CONFIGURATION>/${filename}" "${EXECUTABLE_OUTPUT_PATH}/$<CONFIGURATION>/${filename}"
    )
endforeach()
