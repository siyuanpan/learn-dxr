add_executable(02-initDXR WIN32 InitDXR.cpp InitDXR.h)

target_link_libraries(02-initDXR PRIVATE DXRCommon d3d12.lib dxgi.lib)
target_include_directories(02-initDXR PRIVATE ${CMAKE_SOURCE_DIR}/src/common)