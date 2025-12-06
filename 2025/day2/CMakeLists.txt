add_executable(day2 
    src/main.cpp
)

target_include_directories(day2 PRIVATE
                            "${CMAKE_CURRENT_SOURCE_DIR}/include"
                           )

file(CREATE_LINK "${CMAKE_CURRENT_SOURCE_DIR}/input" "${CMAKE_CURRENT_BINARY_DIR}/input" SYMBOLIC)