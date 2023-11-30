# - vars
set(SOURCE_FILES window.cpp)

# - find packages
find_package(SDL2 REQUIRED)

# - add lib
add_library(Window ${SOURCE_FILES})

# - link libs
target_link_libraries(Window PUBLIC SDL2::SDL2)
