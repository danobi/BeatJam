cmake_minimum_required (VERSION 2.6)
project (BeatJam)

add_subdirectory(../../../../Dev_tools/oxygine-framework-with-sdl/oxygine-framework/ oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

add_executable(BeatJam ../src/beat.cpp ../src/beatborder.cpp ../src/beatstage.cpp ../src/entry_point.cpp ../src/example.cpp ../src/keyboard_listener.cpp ../src/pianobar.cpp ../src/pianokey.cpp  ../src/beat.h ../src/beatborder.h ../src/beatjam_constants.h ../src/beatstage.h ../src/example.h ../src/keyboard_listener.h ../src/pianobar.h ../src/pianokey.h )

target_link_libraries(BeatJam ${OXYGINE_CORE_LIBS})