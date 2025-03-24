cmake_minimum_required(VERSION 3.14)
project(MyDX12App)

set(CMAKE_CXX_STANDARD 17)

add_executable(MyDX12App
    src/main.cpp
)

target_include_directories(MyDX12App PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(MyDX12App
    d3d12 dxgi d3dcompiler dxguid
)
