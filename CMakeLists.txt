cmake_minimum_required(VERSION 3.14)
project(DX12_tutorial)

# C++17 사용
set(CMAKE_CXX_STANDARD 17)

# 유니 코드 설정
add_definitions(-DUNICODE -D_UNICODE)

# 모든 소스 파일 추가 (src/*.cpp)
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# 실행 파일 생성
add_executable(DX12_tutorial ${SOURCES})

# include 디렉토리 설정
target_include_directories(DX12_tutorial PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Windows SDK 라이브러리 링크
target_link_libraries(DX12_tutorial
    d3d12
    dxgi
    d3dcompiler
    dxguid
)

# 윈도우 GUI 앱으로 빌드 (콘솔 창 숨기기)
set_target_properties(DX12_tutorial PROPERTIES
    WIN32_EXECUTABLE ON
)
