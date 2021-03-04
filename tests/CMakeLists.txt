cmake_minimum_required(VERSION 3.3)

include(AddGoogleTest)

if(NOT(MSVC))
set(GCOV_OPTIONS -fprofile-arcs -ftest-coverage)
endif()

target_compile_options(ui PRIVATE ${GCOV_OPTIONS})
target_link_options(ui PRIVATE ${GCOV_OPTIONS})

add_executable(uitest
helper.cpp
  canvas.cpp
  canvas_draw.cpp
  node.cpp
  text.cpp
  playback.cpp
  slider.cpp
  duration.cpp
  sprite.cpp
  basebutton.cpp
  button.cpp
  texturebutton.cpp
  bitmap.cpp
)
target_link_libraries(uitest PUBLIC ui gtest)

add_gtest(uitest)

