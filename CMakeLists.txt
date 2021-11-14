cmake_minimum_required(VERSION 3.20)
project(HKUST_DDM_MSDM5002_final)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

include_directories(src/mcst)

add_executable(HKUST_DDM_MSDM5002_final
        src/mcst/hello.cpp
        src/mcst/mcst.hpp
        src/mcst/node.hpp
        src/mcst/test.cpp src/mcst/LogUtils.h src/mcst/GameUtils.hpp src/mcst/exceptions/NoMostVisitedNodeException.hpp src/mcst/exceptions/NullPointerExceptions.hpp src/mcst/exceptions/CustomBaseException.hpp)
