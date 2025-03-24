cmake_minimum_required(VERSION 3.14)
project(DX12_tutorial)

set(CMAKE_CXX_STANDARD 17)

add_executable(DX12_tutorial
    src/main.cpp
)

target_include_directories(DX12_tutorial PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(DX12_tutorial
    d3d12 dxgi d3dcompiler dxguid
)

set_target_properties(DX12_tutorial PROPERTIES
    WIN32_EXECUTABLE ON
)
