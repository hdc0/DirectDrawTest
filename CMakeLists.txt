cmake_minimum_required(VERSION 3.7.1)
project("DirectDrawTest" CXX)

add_executable(DirectDrawTest DirectDrawTest.cpp)
target_compile_definitions(DirectDrawTest PRIVATE -DUNICODE -D_UNICODE)
target_link_libraries(DirectDrawTest ddraw.lib dxguid.lib)
