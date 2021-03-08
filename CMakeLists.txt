cmake_minimum_required(VERSION 3.3)
project(libui)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if(WIN32)
  # find SDL2
  set(SDL2_DIR "C:/Users/CBeery/Downloads/SDL2/SDL2-2.0.14")
endif()

find_package(SDL2 REQUIRED)

if(WIN32)
  # manually set SDL2_image
  set(SDL2_IMAGE_INCLUDE_DIRS "C:/Users/CBeery/Downloads/SDL2/SDL2_image-2.0.5/include;${SDL2_INCLUDE_DIRS}")
  set(SDL2_IMAGE_LIBRARIES "C:/Users/CBeery/Downloads/SDL2/SDL2_image-2.0.5/lib/x64/SDL2_image.lib")
else()
  find_package(SDL2_image REQUIRED)
endif()


add_library(gfx ../external/Adafruit/Adafruit-GFX/Adafruit_GFX.cpp)
target_include_directories(gfx PUBLIC ../external/Adafruit/Adafruit-GFX)

add_library(ui
  src/node.cpp
  src/canvas.cpp
  src/slider.cpp
  src/text.cpp
  src/duration.cpp
  src/playback.cpp
  src/sprite.cpp
  src/basebutton.cpp
  src/button.cpp
  src/texturebutton.cpp
  src/bitmap.cpp
  )
target_include_directories(ui PUBLIC include)
target_link_libraries(ui PUBLIC gfx)

add_library(mp3 mp3/mp3.cpp mp3/sdl.cpp)
target_include_directories(mp3 PUBLIC mp3 ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(mp3 PUBLIC ui ${SDL2_IMAGE_LIBRARIES})

if(WIN32)
  set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/Debug")
else()
  set(OUTPUT_DIR "${CMAKE_BINARY_DIR}")
endif()
add_custom_command(
  TARGET mp3 POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "${PROJECT_SOURCE_DIR}/mp3/play.png"
  "${PROJECT_SOURCE_DIR}/mp3/pause.png"
  "${PROJECT_SOURCE_DIR}/mp3/prev.png"
  "${PROJECT_SOURCE_DIR}/mp3/next.png"
  "${OUTPUT_DIR}"
  VERBATIM)
message("Image files will be copied to ${OUTPUT_DIR}")

if(NOT(MSVC))
  target_link_libraries(ui PRIVATE gcov)
endif()

add_subdirectory(tests)

