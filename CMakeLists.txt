cmake_minimum_required(VERSION 3.20)
project(HKUST_DDM_MSDM5002_final)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

include_directories(src/mcst)

add_executable(HKUST_DDM_MSDM5002_final
        src/mcst/hello.cpp
        src/mcst/includes/mcst.hpp
        src/mcst/includes/node.hpp
        src/mcst/test.cpp src/mcst/includes/LogUtils.h src/mcst/includes/GameUtils.hpp src/mcst/exceptions/NoMostVisitedNodeException.hpp src/mcst/exceptions/NullPointerExceptions.hpp src/mcst/exceptions/CustomBaseException.hpp src/mcst/mcst_helper.cpp)
