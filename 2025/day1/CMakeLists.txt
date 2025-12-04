add_executable(day1 
    src/main.cpp
    src/dial.cpp
)

target_include_directories(day1 PUBLIC
                            "${CMAKE_CURRENT_SOURCE_DIR}/include"
                           )

file(CREATE_LINK "${CMAKE_CURRENT_SOURCE_DIR}/input" "${CMAKE_CURRENT_BINARY_DIR}/input" SYMBOLIC)