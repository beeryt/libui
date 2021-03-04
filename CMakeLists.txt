cmake_minimum_required(VERSION 3.3)
project(libui)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

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

if(NOT(MSVC))
target_link_libraries(ui PRIVATE gcov)
endif()

add_subdirectory(tests)

