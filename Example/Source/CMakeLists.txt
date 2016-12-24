add_definitions(-DUNICODE -D_UNICODE)

add_executable(Example Example.cpp)

target_link_libraries(Example Log)