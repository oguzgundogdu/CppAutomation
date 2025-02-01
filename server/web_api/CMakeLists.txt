cmake_minimum_required(VERSION 3.10)
project(web_api VERSION 0.1.0 LANGUAGES C CXX)
include_directories(/opt/homebrew/Cellar/openssl@3/3.4.0/include)
include_directories(/opt/homebrew/Cellar/boost/1.87.0/include)
include_directories(/opt/homebrew/Cellar/cpprestsdk/2.10.19_1/include)
include_directories(/opt/homebrew/Cellar/libpq/17.2/include)
include_directories(/opt/homebrew/Cellar/drogon/1.9.9/include)
include_directories(/opt/homebrew/Cellar/jsoncpp/1.9.6/include)

set(CMAKE_CXX_STANDARD 20) # veya 20
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(web_api main.cpp)
target_link_libraries(web_api /opt/homebrew/Cellar/libpq/17.2/lib/libpq.dylib /opt/homebrew/Cellar/drogon/1.9.9/lib/libdrogon.1.9.9.dylib /opt/homebrew/Cellar/jsoncpp/1.9.6/lib/libjsoncpp.26.dylib /opt/homebrew/Cellar/drogon/1.9.9/lib/libtrantor.1.5.22.dylib)