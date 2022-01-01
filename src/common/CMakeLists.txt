find_package(glm CONFIG REQUIRED)

add_library(DXRCommon Framework.cpp Framework.h dxcapi.use.h)

target_link_libraries(DXRCommon PUBLIC glm::glm)