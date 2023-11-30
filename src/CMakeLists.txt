# - vars
set(INCLUDE_DIRS window)

# - add subdirs
add_subdirectory(window)

# - add lib
add_library(Engine null.cpp)

# - include dirs
target_include_directories(Engine PUBLIC ${INCLUDE_DIRS})

# - link libs
target_link_libraries(
  Engine
  PUBLIC Window
)

