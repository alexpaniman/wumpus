add_executable(wumpus wumpus.cpp)

target_include_directories(wumpus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(wumpus PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})

target_link_libraries(wumpus gl)
