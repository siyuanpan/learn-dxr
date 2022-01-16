add_executable(03-AccelerationStructure WIN32 AccelerationStructure.cpp AccelerationStructure.h)

target_link_libraries(03-AccelerationStructure PRIVATE DXRCommon d3d12.lib dxgi.lib)
target_include_directories(03-AccelerationStructure PRIVATE ${CMAKE_SOURCE_DIR}/src/common)