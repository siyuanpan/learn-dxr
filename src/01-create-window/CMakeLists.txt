add_executable(01-create-window WIN32 CreateWindow.cpp CreateWindow.h)

target_link_libraries(01-create-window PRIVATE DXRCommon)
target_include_directories(01-create-window PRIVATE ${CMAKE_SOURCE_DIR}/src/common)