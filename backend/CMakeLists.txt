add_executable(ravenwood
    main.cpp
    src/Game.cpp
    src/Ghost.cpp
    src/Player.cpp
    src/Room.cpp
    src/item.cpp
    src/puzzle.cpp
)
target_include_directories(ravenwood PRIVATE include)
target_link_libraries(ravenwood PRIVATE nlohmann_json::nlohmann_json httplib::httplib)
target_compile_definitions(ravenwood PRIVATE
    RAVENWOOD_FRONTEND_DIR="${CMAKE_SOURCE_DIR}/frontend"
)
if(MSVC)
    target_compile_options(ravenwood PRIVATE /W4)
else()
    target_compile_options(ravenwood PRIVATE -Wall -Wextra -Wpedantic)
endif()
